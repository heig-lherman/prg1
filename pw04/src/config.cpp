#include "investor/config.h"

#include <algorithm>

using namespace std;

investor::Config config;

namespace investor {

    bool isStrategyInFilter(Strategy strategy) {
        auto &filter = config.strategyFilter;
        return find(filter.begin(), filter.end(), strategy) != filter.end();
    }

    vector<Strategy> getStrategiesToCompute() {
        if (config.strategyFilter.empty()) {
            return {DEFAULT_STRATEGIES.begin(), DEFAULT_STRATEGIES.end()};
        }

        vector<Strategy> res;
        copy_if(DEFAULT_STRATEGIES.begin(), DEFAULT_STRATEGIES.end(), back_inserter(res),
                isStrategyInFilter);
        return res;
    }

    vector<unsigned> getDynamicTimeFramesToCompute() {
        if (config.dynamicTimeFrames.empty()) {
            return {DEFAULT_DYNAMIC_TIME_FRAMES.begin(), DEFAULT_DYNAMIC_TIME_FRAMES.end()};
        }

        return config.dynamicTimeFrames;
    }

    vector<double> getPercentilesToDisplay() {
        if (config.percentiles.empty()) {
            return {DEFAULT_PERCENTILES.begin(), DEFAULT_PERCENTILES.end()};
        }

        return config.percentiles;
    }
}  // namespace investor
