#ifndef INVESTOR_CONFIG_H
#define INVESTOR_CONFIG_H

#include <array>
#include <vector>

#include "investor/strategies.h"

namespace investor {

    constexpr std::array<Strategy, 3> DEFAULT_STRATEGIES
        = {Strategy::HODL, Strategy::MA, Strategy::EMA};
    constexpr std::array<unsigned, 5> DEFAULT_DYNAMIC_TIME_FRAMES = {10, 20, 50, 100, 200};
    constexpr std::array<double, 3> DEFAULT_PERCENTILES = {0.1, 0.5, 0.9};

    /**
     * Main configuration with its default values to specify how the calculations
     * should be made.
     */
    struct Config {
        long double initialAmount = 100000;
        unsigned investmentPeriod = 1250;
        unsigned fixedTransactionFee = 10;
        double variableTransactionFee = 0.0002;

        std::vector<Strategy> strategyFilter{};
        std::vector<unsigned> dynamicTimeFrames{};
        std::vector<double> percentiles{};
    };

    std::vector<Strategy> getStrategiesToCompute();

    std::vector<unsigned> getDynamicTimeFramesToCompute();

    std::vector<double> getPercentilesToDisplay();

}  // namespace investor

#endif  // INVESTOR_CONFIG_H
