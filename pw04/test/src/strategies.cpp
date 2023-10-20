#include "investor/strategies.h"

#include <doctest/doctest.h>

#include <vector>

#include "investor/data-reader.h"

namespace investor {
    long double calculateRunningAverage(const MarketData &dayData, long double previousEma,
                                        double smoothingFactor);
    long double calculateInitialMovingAverage(const std::vector<MarketData> &marketDataTable,
                                              size_t dayIndex, unsigned strategyTimeFrame);
}  // namespace investor

TEST_CASE("EMA indicator calculation") {
    unsigned timeFrames = 4;
    long double stopIndicator = 4653.93;
    double smoothing = 2. / (1 + timeFrames);

    investor::MarketData day1Data = {"05.11.21", 4697.53, 4699.26, 4718.50, 4681.32, 3491150000};
    investor::MarketData day2Data = {"08.11.21", 4701.70, 4701.48, 4714.92, 4694.39, 3465720000};

    CHECK(investor::calculateRunningAverage(day1Data, stopIndicator, smoothing)
          == doctest::Approx(4671.37));
    stopIndicator = 4671.37;
    CHECK(investor::calculateRunningAverage(day2Data, stopIndicator, smoothing)
          == doctest::Approx(4683.50));
}

TEST_CASE("First EMA Calculation") {
    std::vector<investor::MarketData> marketData
        = {{"01.11.21", 4613.67, 4610.62, 4620.34, 4595.06, 2924000000},
           {"02.11.21", 4630.65, 4613.34, 4635.15, 4613.34, 3309690000},
           {"03.11.21", 4660.57, 4630.65, 4663.46, 4621.19, 3339440000},
           {"04.11.21", 4680.06, 4662.93, 4683.00, 4662.59, 3332940000},
           {"05.11.21", 4697.53, 4699.26, 4718.50, 4681.32, 3491150000}};

    SUBCASE("time frame = 1") {
        long double firstEMA = investor::calculateInitialMovingAverage(marketData, 4, 1);
        CHECK(firstEMA == doctest::Approx(4697.53));
    }

    SUBCASE("time frame = 2") {
        long double firstEMA = investor::calculateInitialMovingAverage(marketData, 4, 2);
        CHECK(firstEMA == doctest::Approx(4691.71));
    }

    SUBCASE("time frame = 4") {
        long double firstEMA = investor::calculateInitialMovingAverage(marketData, 4, 4);
        CHECK(firstEMA == doctest::Approx(4678.2099));
    }
}
