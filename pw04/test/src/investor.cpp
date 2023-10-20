#include <doctest/doctest.h>

#include <string>
#include <vector>

#include "investor/version.h"

TEST_CASE("Investor version") {
    static_assert(std::string_view(INVESTOR_VERSION) == std::string_view("1.0"));
    CHECK(std::string(INVESTOR_VERSION) == std::string("1.0"));
}
