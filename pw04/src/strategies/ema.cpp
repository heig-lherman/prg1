#include <cassert>
#include <cmath>
#include <vector>

#include "investor/data-reader.h"
#include "investor/strategies-utils.h"
#include "investor/strategies.h"
#include "investor/transactions.h"

using namespace std;

namespace investor {

    constexpr double SMOOTHING_VALUE = 2.;

    /**
     * Calculates the running exponential average based on the previous
     * day's moving average.
     * @param dayData Current day data
     * @param previousEma Previous day moving average
     * @param smoothingFactor The smoothing factor to use
     * @return The current day's moving average
     */
    long double calculateRunningAverage(const MarketData &dayData, long double previousEma,
                                        double smoothingFactor) {
        return dayData.close * smoothingFactor + previousEma * (1 - smoothingFactor);
    }

    /**
     * Calculates the initial moving average for the first day of investment.
     * The time frame should at a minimum be the first day index - 1;
     * @param marketDataTable The market data
     * @param firstDayIndex The first day of computation
     * @param strategyTimeFrame The amount of days we use for the average
     * @return The initial (and first day) moving average
     */
    long double calculateInitialMovingAverage(const vector<MarketData> &marketDataTable,
                                              size_t dayIndex, unsigned strategyTimeFrame) {
        assert(strategyTimeFrame >= 1);
        double smoothingFactor = SMOOTHING_VALUE / (strategyTimeFrame + 1);

        if (strategyTimeFrame == 1) {
            return marketDataTable[dayIndex].close;
        }

        long double previousEma
            = calculateInitialMovingAverage(marketDataTable, dayIndex - 1, strategyTimeFrame - 1);
        return calculateRunningAverage(marketDataTable[dayIndex], previousEma, smoothingFactor);
    }

    long double computeEMA(const vector<MarketData> &marketDataTable, size_t firstDayIndex,
                           size_t lastDayIndex, long double initialCashAmount,
                           unsigned strategyTimeFrame) {
        assert(marketDataTable.size() > lastDayIndex);
        assert(firstDayIndex < lastDayIndex);
        assert(strategyTimeFrame > 0);

        const double smoothingFactor = SMOOTHING_VALUE / (strategyTimeFrame + 1);

        long double cashAmount = initialCashAmount;
        long double stockVolume = 0;
        long double currentMovingAverage
            = calculateInitialMovingAverage(marketDataTable, firstDayIndex - 1, strategyTimeFrame);

        for (size_t i = firstDayIndex; i <= lastDayIndex; i++) {
            MarketData dayData = marketDataTable[i];
            long double stopOrderStockPrice
                = getStockPriceIfTriggeredStopOrder(dayData, currentMovingAverage, stockVolume);

            if (stopOrderStockPrice > 0) {
                executeStopOrder(stopOrderStockPrice, stockVolume, cashAmount);
            }

            currentMovingAverage
                = calculateRunningAverage(dayData, currentMovingAverage, smoothingFactor);
        }

        if (stockVolume > 0) {
            sell(marketDataTable[lastDayIndex].close, stockVolume, cashAmount);
        }

        assert(stockVolume <= 0);
        return cashAmount;
    }

}  // namespace investor
