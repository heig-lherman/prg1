#include <iostream>
#include <vector>

#include "investor/strategies.h"

using namespace std;

namespace investor {

    long double computeStrategy(Strategy strategy, const vector<MarketData> &marketDataTable,
                                size_t firstDayIndex, size_t lastDayIndex,
                                long double initialCashAmount, unsigned strategyTimeFrame) {
        switch (strategy) {
            case Strategy::HODL:
                return computeHODL(marketDataTable[firstDayIndex], marketDataTable[lastDayIndex],
                                   initialCashAmount);
            case Strategy::MA:
                return computeMA(marketDataTable, firstDayIndex, lastDayIndex, initialCashAmount,
                                 strategyTimeFrame);
            case Strategy::EMA:
                return computeEMA(marketDataTable, firstDayIndex, lastDayIndex, initialCashAmount,
                                  strategyTimeFrame);
            default:
                cerr << "Unexpected strategy" << endl;
                return 0.l;
        }
    }

}  // namespace investor
