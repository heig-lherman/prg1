#include "investor/percentiles.h"

#include <doctest/doctest.h>

#include <vector>

TEST_CASE("Percentile Calculation") {
    std::vector<long double> orderedValues = {3, 6, 7, 8, 8, 10, 13, 15, 16, 20};

    SUBCASE("0 percentile") { CHECK(investor::getPercentileValue(orderedValues, 0.) == 3); }

    SUBCASE("10 percentile") { CHECK(investor::getPercentileValue(orderedValues, 0.1) == 3); }

    SUBCASE("25 percentile") { CHECK(investor::getPercentileValue(orderedValues, 0.25) == 7); }

    SUBCASE("50 percentile") { CHECK(investor::getPercentileValue(orderedValues, 0.5) == 8); }

    SUBCASE("75 percentile") { CHECK(investor::getPercentileValue(orderedValues, 0.75) == 13); }

    SUBCASE("90 percentile") { CHECK(investor::getPercentileValue(orderedValues, 0.9) == 16); }

    SUBCASE("100 percentile") { CHECK(investor::getPercentileValue(orderedValues, 1) == 20); }
}
