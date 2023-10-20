#include "investor/data-reader.h"
#include "investor/strategies.h"
#include "investor/transactions.h"

using namespace std;

namespace investor {

    long double computeHODL(const MarketData &firstDay, const MarketData &lastDay,
                            long double initialCashAmount) {
        long double stockAmount = 0;
        long double cashAmount = initialCashAmount;

        long double openValue = firstDay.open;
        long double closeValue = lastDay.close;

        buy(openValue, stockAmount, cashAmount);
        sell(closeValue, stockAmount, cashAmount);
        return cashAmount;
    }
}  // namespace investor