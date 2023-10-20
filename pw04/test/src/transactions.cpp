#include "investor/transactions.h"

#include <doctest/doctest.h>

TEST_CASE("Sell") {
    long double price;
    long double stockAmount;
    long double cashAmount;

    SUBCASE("No initial cash amount") {
        price = 4620.34;
        stockAmount = 10;
        cashAmount = 0;
        investor::sell(price, stockAmount, cashAmount);

        CHECK(stockAmount == 0);
        CHECK(cashAmount == doctest::Approx(46184.16));
    }

    SUBCASE("Initial cash amount") {
        price = 4620.34;
        stockAmount = 23;
        cashAmount = 2654;
        investor::sell(price, stockAmount, cashAmount);

        CHECK(stockAmount == 0);
        CHECK(cashAmount == doctest::Approx(108890.57));
    }
}

TEST_CASE("Buy") {
    long double price;
    long double stockAmount;
    long double cashAmount;

    SUBCASE("Enough money to buy") {
        price = 4620.34;
        stockAmount = 0;
        cashAmount = 100000;
        investor::buy(price, stockAmount, cashAmount);

        CHECK(stockAmount == doctest::Approx(21.63694));
        CHECK(cashAmount == 0.0);
    }

    SUBCASE("Not enough money to buy whole") {
        price = 4620.34;
        stockAmount = 0;
        cashAmount = 2943.45;
        investor::buy(price, stockAmount, cashAmount);

        CHECK(stockAmount == doctest::Approx(0.63477));
        CHECK(cashAmount == 0.0);
    }
}