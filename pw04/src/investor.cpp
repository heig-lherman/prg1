#include "investor/investor.h"

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>

#include "investor/config.h"
#include "investor/data-reader.h"
#include "investor/percentiles.h"
#include "investor/strategies-utils.h"
#include "investor/strategies.h"

using namespace std;

extern investor::Config config;

namespace investor {

    void computePercentilesAndDisplay(Strategy strategy, unsigned timeFrame, ostream &outputStream,
                                      const vector<double> &percentiles,
                                      const vector<long double> &results) {
        vector<long double> percentileValues;
        transform(percentiles.begin(), percentiles.end(), back_inserter(percentileValues),
                  [results](double percentile) { return getPercentileValue(results, percentile); });
        string strategyName = getStrategyName(strategy, timeFrame);
        outputPercentilesAsCSV(outputStream, strategyName, percentileValues, config.initialAmount);
    }

    void processStrategyForAllTimePeriods(ostream &outputStream, Strategy strategy,
                                          const vector<MarketData> &marketData,
                                          const vector<double> &percentiles, unsigned maxTimeFrame,
                                          unsigned timeFrame = 0) {
        vector<long double> res;

        for (size_t i = maxTimeFrame; i < (marketData.size() + 1 - config.investmentPeriod); i++) {
            size_t lastDayIndex = i + config.investmentPeriod - 1;
            assert(lastDayIndex < marketData.size());
            res.push_back(computeStrategy(strategy, marketData, i, lastDayIndex,
                                          config.initialAmount, timeFrame));
        }

        computePercentilesAndDisplay(strategy, timeFrame, outputStream, percentiles, res);
    }

    void computeAll(ostream &outputStream, const vector<Strategy> &strategies,
                    const vector<unsigned> &timeFrames, const vector<MarketData> &marketData,
                    const vector<double> &percentiles) {
        for (Strategy strategy : strategies) {
            auto maxTimeFrameIt = max_element(timeFrames.begin(), timeFrames.end());

            if (!hasTimeFrames(strategy)) {
                processStrategyForAllTimePeriods(outputStream, strategy, marketData, percentiles,
                                                 *maxTimeFrameIt);
                continue;
            }

            for (unsigned timeFrame : timeFrames) {
                processStrategyForAllTimePeriods(outputStream, strategy, marketData, percentiles,
                                                 *maxTimeFrameIt, timeFrame);
            }
        }
    }

    void process(istream &inputStream, ostream &outputStream) {
        if (!inputStream.good() || !outputStream.good()) {
            cerr << "There is an error with one of the provided streams for processing, cancelling "
                    "the operation."
                 << endl;
            return;
        }

        vector<MarketData> marketData = investor::read(inputStream, true);
        vector<Strategy> strategies = getStrategiesToCompute();

        outputStream << "Strategy" << prettyPrintPercentileNames(getPercentilesToDisplay()) << endl;
        computeAll(outputStream, getStrategiesToCompute(), getDynamicTimeFramesToCompute(),
                   marketData, getPercentilesToDisplay());
    }

    ifstream openInputStream(const string &inputFilePath) {
        ifstream inputFile(inputFilePath);
        if (!inputFile.good()) {
            cerr << "EFILEMISS - File " << inputFilePath << " could not be found." << endl;
        }

        return inputFile;
    }

    ofstream openOutputStream(const string &outputFilePath) {
        ofstream outputFile(outputFilePath);
        if (!outputFile.good()) {
            cerr << "EFILEMISS - File " << outputFilePath << " could not be found." << endl;
        }

        return outputFile;
    }

    void process(const string &inputFilePath, const string &outputFilePath) {
        ifstream inFile = openInputStream(inputFilePath);
        ofstream outFile = openOutputStream(outputFilePath);
        process(inFile, outFile);
        inFile.close();
        outFile.close();
    }

    void process(const string &inputFilePath, ostream &outputStream) {
        ifstream inFile = openInputStream(inputFilePath);
        process(inFile, outputStream);
        inFile.close();
    }

    void process(istream &inputStream, const string &outputFilePath) {
        ofstream outFile = openOutputStream(outputFilePath);
        process(inputStream, outFile);
        outFile.close();
    }

}  // namespace investor
