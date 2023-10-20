#include "investor/percentiles.h"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iomanip>
#include <sstream>

using namespace std;

namespace investor {

    long double getPercentileValue(const vector<long double> &values, double percentile) {
        assert(percentile >= 0 && percentile <= 1);
        vector<long double> orderedValues = values;
        sort(orderedValues.begin(), orderedValues.end());
        auto rank = (size_t)floor(percentile * (double)(orderedValues.size() - 1));
        return orderedValues[rank];
    }

    long double getROI(long double cashAmount, long double initialCashAmount) {
        return 1 + (cashAmount - initialCashAmount) / initialCashAmount;
    }

    void outputPercentilesAsCSV(ostream &outputStream, const string &strategyName,
                                const vector<long double> &percentileValues,
                                long double initialCashAmount) {
        assert(!percentileValues.empty());
        outputStream << setw(8) << strategyName;
        for (long double value : percentileValues) {
            outputStream << setw(2) << ", " << setw(16) << fixed << setprecision(6)
                         << getROI(value, initialCashAmount);
        }
        outputStream << endl;
    }

    string prettyPrintPercentileNames(const vector<double> &percentages) {
        stringstream res;
        for (double p : percentages) {
            res << ", " << fixed << setprecision(0) << p * 100 << "-th percentile";
        }
        return res.str();
    }

}  // namespace investor