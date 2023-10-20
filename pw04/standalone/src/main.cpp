#include <cxxopts.hpp>
#include <iostream>

#include "investor/config.h"
#include "investor/investor.h"
#include "investor/version.h"

using namespace std;

extern investor::Config config;

void processStrategyFilter(const vector<string> &filter) {
    for (const string &strategy : filter) {
        if (strategy == "HODL") {
            config.strategyFilter.push_back(investor::Strategy::HODL);
            continue;
        }
        if (strategy == "MA") {
            config.strategyFilter.push_back(investor::Strategy::MA);
            continue;
        }
        if (strategy == "EMA") {
            config.strategyFilter.push_back(investor::Strategy::EMA);
            continue;
        }
    }
}

auto main(int argc, char **argv) -> int {
    cxxopts::Options options(*argv,
                             "A program to compute investment strategies on real-world data.");

    string inputFilePath;
    bool useCin;
    string outputFile;
    vector<string> strategyFilter;
    // clang-format off
    options.add_options()
            ("h,help", "Show help")
            ("v,version", "Prints the current version")
            ("i,input", "Input file", cxxopts::value(inputFilePath)->default_value("./gspc.csv"))
            ("0,stream", "Use input from stdin", cxxopts::value(useCin)->default_value("false"))
            ("o,output-file", "Specify where to ouput the results, defaults to stdout if not defined", cxxopts::value(outputFile)->default_value(""))
            ("initial-amount", "Initial wallet amount (defaults to 100000)", cxxopts::value(config.initialAmount)->default_value("100000"))
            ("investment-period", "Amount of days between stock purchase and sale (defaults to 1250)", cxxopts::value(config.investmentPeriod)->default_value("1250"))
            ("fixed-fee", "Fixed transaction fee for purchasing and selling stocks (defaults to 10)", cxxopts::value(config.fixedTransactionFee)->default_value("10"))
            ("variable-fee", "Variable fee (percentage of transaction) applied when purchasing and selling (defaults to 0.02%)", cxxopts::value(config.variableTransactionFee)->default_value("0.0002"))
            ("s,strategy", "Strategies to compute (available: HODL, MA, EMA; defaults to all)", cxxopts::value(strategyFilter)->default_value("HODL,MA,EMA"))
            ("t,time-frame", "Time frames to evaluate for dynamic strategies (defaults to 10, 20, 50, 100, 200)", cxxopts::value(config.dynamicTimeFrames)->default_value("10,20,50,100,200"))
            ("p,percentile", "Percentiles to compute for showing the results (defaults to 10%, 50%, 90%)", cxxopts::value(config.percentiles)->default_value("0.1,0.5,0.9"));
    // clang-format on

    auto result = options.parse(argc, argv);

    if (result["help"].as<bool>()) {
        cout << options.help() << endl;
        return EXIT_SUCCESS;
    }

    if (result["version"].as<bool>()) {
        cout << "Investor version " << INVESTOR_VERSION << endl;
        return EXIT_SUCCESS;
    }

    if (!strategyFilter.empty()) {
        processStrategyFilter(strategyFilter);
    }

    if (!useCin && !outputFile.empty()) {
        investor::process(inputFilePath, outputFile);
    } else if (!useCin && outputFile.empty()) {
        investor::process(inputFilePath, cout);
    } else if (useCin && !outputFile.empty()) {
        investor::process(cin, outputFile);
    } else {
        investor::process(cin, cout);
    }

    return EXIT_SUCCESS;
}
