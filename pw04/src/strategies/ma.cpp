#include <cassert>
#include <vector>

#include "investor/data-reader.h"
#include "investor/strategies-utils.h"
#include "investor/strategies.h"
#include "investor/transactions.h"

using namespace std;

namespace investor {

    /**
     * Returns the moving average for the given timeframes (days) since the first day.
     * Calculates the average in reverse order, so the index given will be the last and it
     * will backtrack though the given time frames.
     * @param marketDataTable The market data we are processing
     * @param lastDayIndex The last day index for the calculation
     * @param timeFrame The amount of days we should compute
     * @return The moving average for the amount of days
     */
    long double calculateStaticMovingAverage(const vector<MarketData> &marketDataTable,
                                             size_t lastDayIndex, unsigned timeFrame) {
        long double sumOfClosingPrices = 0.l;
        unsigned count = 0;
        for (size_t i = lastDayIndex; i > (lastDayIndex - timeFrame); i--) {
            sumOfClosingPrices += marketDataTable[i].close;
            ++count;
        }

        return sumOfClosingPrices / timeFrame;
    }

    long double computeMA(const vector<MarketData> &marketDataTable, size_t firstDayIndex,
                          size_t lastDayIndex, long double initialCashAmount,
                          unsigned strategyTimeFrame) {
        assert(marketDataTable.size() > lastDayIndex);
        assert(firstDayIndex < lastDayIndex);
        assert(strategyTimeFrame > 0);

        long double cashAmount = initialCashAmount;
        long double stockVolume = 0;
        long double currentMovingAverage
            = calculateStaticMovingAverage(marketDataTable, firstDayIndex - 1, strategyTimeFrame);

        for (size_t i = firstDayIndex; i <= lastDayIndex; i++) {
            MarketData dayData = marketDataTable[i];
            long double stopOrderStockPrice
                = getStockPriceIfTriggeredStopOrder(dayData, currentMovingAverage, stockVolume);

            if (stopOrderStockPrice >= 0) {
                executeStopOrder(stopOrderStockPrice, stockVolume, cashAmount);
            }

            currentMovingAverage
                = calculateStaticMovingAverage(marketDataTable, i, strategyTimeFrame);
        }

        if (stockVolume > 0) {
            sell(marketDataTable[lastDayIndex].close, stockVolume, cashAmount);
        }

        assert(stockVolume <= 0);
        return cashAmount;
    }

}  // namespace investor