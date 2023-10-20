#include "investor/transactions.h"

#include <cassert>

#include "investor/config.h"

extern investor::Config config;

namespace investor {

    long double calculateFees(long double transactionAmount) {
        assert(transactionAmount > 0);
        return config.fixedTransactionFee + config.variableTransactionFee * transactionAmount;
    }

    void sell(long double price, long double &stockAmount, long double &cashAmount) {
        assert(stockAmount > 0 && price > 0);
        long double transactionAmount = stockAmount * price;
        cashAmount += transactionAmount - calculateFees(transactionAmount);
        stockAmount = 0;
    }

    void buy(long double price, long double &stockAmount, long double &cashAmount) {
        assert(stockAmount == 0 && price > 0);
        long double stockPurchasable
            = ((cashAmount - config.fixedTransactionFee) * (1 - config.variableTransactionFee))
              / price;
        if (stockPurchasable > 0) {
            cashAmount = 0;
            stockAmount += stockPurchasable;
        }
    }
}  // namespace investor