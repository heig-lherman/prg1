#ifndef INVESTOR_TRANSACTIONS_H
#define INVESTOR_TRANSACTIONS_H

namespace investor {

    /**
     * Sells the stock at the given price
     * @param price The stock price
     * @param stockAmount The amount to sell
     * @param cashAmount Where to store the resulting cash
     */
    void sell(long double price, long double &stockAmount, long double &cashAmount);

    /**
     * Purchases all the possible stock with the given cash
     * @param price The stock price
     * @param stockAmount Where to store the resulting stock
     * @param cashAmount The cash available to purchase
     */
    void buy(long double price, long double &stockAmount, long double &cashAmount);

}  // namespace investor

#endif  // INVESTOR_TRANSACTIONS_H
