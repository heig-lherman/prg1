#ifndef INVESTOR_STRATEGIES_H
#define INVESTOR_STRATEGIES_H

#include "investor/data-reader.h"

namespace investor {

    enum class Strategy { HODL, MA, EMA };

    /**
     * Computes the given strategy with the parameters provided
     * @param strategy The strategy to compute
     * @param marketDataTable The market data
     * @param firstDayIndex The first day of investment
     * @param lastDayIndex The last day of investment
     * @param initialCashAmount The initial cash amount
     * @param strategyTimeFrame The number of days to compute moving averages, not required for HODL
     * @return The final cash amount after the investment period is over
     */
    long double computeStrategy(Strategy strategy, const std::vector<MarketData> &marketDataTable,
                                size_t firstDayIndex, size_t lastDayIndex,
                                long double initialCashAmount, unsigned strategyTimeFrame = 0);

    // Methods below are considered internal, mostly used for testing purposes.
    // They are still part of the API we expose and are not restricted by any means,
    // but often the computeStrategy method above will do the work.

    long double computeHODL(const MarketData &firstDay, const MarketData &lastDay,
                            long double initialCashAmount);

    long double computeMA(const std::vector<MarketData> &marketDataTable, size_t firstDayIndex,
                          size_t lastDayIndex, long double initialCashAmount,
                          unsigned strategyTimeFrame);

    long double computeEMA(const std::vector<MarketData> &marketDataTable, size_t firstDayIndex,
                           size_t lastDayIndex, long double initialCashAmount,
                           unsigned strategyTimeFrame);

}  // namespace investor

#endif  // INVESTOR_STRATEGIES_H
