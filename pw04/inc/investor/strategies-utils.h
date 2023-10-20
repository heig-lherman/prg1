#ifndef INVESTOR_STRATEGIES_UTILS_H
#define INVESTOR_STRATEGIES_UTILS_H

#include <string_view>

#include "investor/strategies.h"

namespace investor {

    /**
     * @param strategy The strategy to check
     * @return whether the given strategy requires time frames for computation on previous data or
     * not
     */
    bool hasTimeFrames(Strategy strategy);

    /**
     * @param strategy The strategy to name
     * @param strategyTimeFrame The strategy time frames (not required for HODL)
     * @return A string name of the strategy for output formatting
     */
    std::string getStrategyName(Strategy strategy, unsigned strategyTimeFrame = 0);

    /**
     * Returns the stock price at which the stock will be purchased or sold,
     * if the stop order should be triggered.
     *
     * A special case is for when the stop order should be omitted (i.e. we
     * are invested or cashed out, and the moving average is above the open
     * price and not within the low and high for the current day. In this
     * situation the method will return a price that is less than 0.
     * @param dayData The current day data
     * @param movingAverage The moving average for the previous days
     * @param investedStockVolume The currently invested stock volume (if greater than 0
     *                            we are considered invested).
     * @return The stock price for the stop order, less than 0 if no
     *         purchase or sale is necessary.
     */
    long double getStockPriceIfTriggeredStopOrder(const MarketData &dayData,
                                                  long double movingAverage,
                                                  long double investedStockVolume);

    /**
     * Executes the stop order, where it will either purchase or sell all possible stock
     * @param stopOrderStockPrice The price at which the stop order was triggered
     * @param stockVolume The current stock volume to be edited
     * @param cashAmount The current cash amount to be edited
     */
    void executeStopOrder(long double stopOrderStockPrice, long double &stockVolume,
                          long double &cashAmount);
}  // namespace investor

#endif  // INVESTOR_STRATEGIES_UTILS_H
