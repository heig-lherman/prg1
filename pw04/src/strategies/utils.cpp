#include <cassert>

#include "investor/strategies-utils.h"
#include "investor/transactions.h"

using namespace std;

namespace investor {

    bool hasTimeFrames(Strategy strategy) { return strategy != Strategy::HODL; }

    std::string getStrategyName(Strategy strategy, unsigned int strategyTimeFrame) {
        switch (strategy) {
            case Strategy::HODL:
                return "HODL";
            case Strategy::MA:
                return "MA" + to_string(strategyTimeFrame);
            case Strategy::EMA:
                return "EMA" + to_string(strategyTimeFrame);
            default:
                return "UNKNOWN";
        }
    }

    bool isMovingAverageWithinDayPrices(const MarketData &dayData, long double movingAverage) {
        return (movingAverage >= dayData.low && movingAverage <= dayData.high);
    }

    long double getStockPriceIfTriggeredStopOrder(const MarketData &dayData,
                                                  long double movingAverage,
                                                  long double investedStockVolume) {
        bool isInvested = investedStockVolume > 0;

        // If we are invested and the average is higher than the open price, we sell at that price
        // - or -
        // If we are not invested and the average is less than the open price, we purchase at that
        // price
        if ((isInvested && movingAverage >= dayData.open)
            || (!isInvested && movingAverage <= dayData.open)) {
            return dayData.open;
        }

        // If the average is within bounds, we purchase or sell at that amount
        if (isMovingAverageWithinDayPrices(dayData, movingAverage)) {
            return movingAverage;
        }

        // No purchase or sale should be made, return less than 0;
        return -1;
    }

    void executeStopOrder(long double stopOrderStockPrice, long double &stockVolume,
                          long double &cashAmount) {
        assert(stopOrderStockPrice >= 0);
        if (stockVolume > 0) {
            sell(stopOrderStockPrice, stockVolume, cashAmount);
        } else {
            buy(stopOrderStockPrice, stockVolume, cashAmount);
        }
    }
}  // namespace investor
