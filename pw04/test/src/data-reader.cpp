#include "investor/data-reader.h"

#include <doctest/doctest.h>

#include <sstream>
#include <vector>

using namespace std;

TEST_CASE("Data reader") {
    stringstream input;
    input << "date,close,open,high,low,volume\n"
          << "09.11.21,4685.25,4707.25, 4708.53,4670.87,3110230000\n"
          << " 08.11.21  ,4701.70,4701.48,4714.92, 4694.39 ,3465720000\n";

    vector<investor::MarketData> result = investor::read(input, false);

    CHECK(result.size() == 2);
    CHECK(result[0].date == "09.11.21");
    CHECK(result[0].high == doctest::Approx(4708.53));
    CHECK(result[1].date == "08.11.21");
    CHECK(result[1].close == doctest::Approx(4701.70));
    CHECK(result[1].open == doctest::Approx(4701.48));
    CHECK(result[1].high == doctest::Approx(4714.96));
    CHECK(result[1].low == doctest::Approx(4694.39));
    CHECK(result[1].volume == 3465720000);
}

TEST_CASE("Data reader reverse order") {
    stringstream input;
    input << "date,close,open,high,low,volume\n"
          << "09.11.21,4685.25,4707.25,4708.53,4670.87,3110230000\n"
          << "08.11.21,4701.70,4701.48,4714.92,4694.39,3465720000\n";

    vector<investor::MarketData> result = investor::read(input, true);

    CHECK(result.size() == 2);
    CHECK(result[0].date == "08.11.21");
    CHECK(result[1].date == "09.11.21");
}

TEST_CASE("Data reader with closed days") {
    stringstream input;
    input << "date,close,open,high,low,volume\n"
          << "09.11.21,4685.25,4707.25,4708.53,4670.87,3110230000\n"
          << "08.11.21,4701.70,4701.48,4714.92,4694.39,3465720000\n"
          << "07.11.21,*,*,*,*,*\n"
          << "06.11.21,*,*,*,*,*\n"
          << "05.11.21,4697.53,4699.26,4718.50,4681.32,3491150000";

    vector<investor::MarketData> result = investor::read(input, false);

    CHECK(result.size() == 3);
    CHECK(result[0].date == "09.11.21");
    CHECK(result[1].date == "08.11.21");
    CHECK(result[2].date == "05.11.21");
}
