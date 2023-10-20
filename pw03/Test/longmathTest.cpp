#include "catch.hpp"
#include "../longmath.h"

#include <string>
#include <limits>

using namespace std;
using namespace longMath;

TEST_CASE("1: to_string", "LongMath") {

   SECTION("Single digit") {
      DigitType d[10] = {7};
      REQUIRE(to_string(d, 1) == "7");
   }

   SECTION("Small number") {
      DigitType d[10] = {2, 3, 4};
      REQUIRE(to_string(d, 3) == "432");
   }

   SECTION("Zero") {
      DigitType d[10] = {};
      REQUIRE(to_string(d, 0) == "0");
   }

   SECTION("Large number") {
      DigitType d[20] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 9, 8, 7, 6, 5, 4, 3, 4, 5};
      REQUIRE(to_string(d, 19) == "5434567890987654321");
   }
}

TEST_CASE("2: from_string", "LongMath") {

   SECTION("Single digit") {
      DigitType r[10]; size_t size;

      REQUIRE(from_string("7", r, size, 10));
      REQUIRE(size == 1);
      REQUIRE(r[0] == 7);
   }

   SECTION("Number") {
      const DigitType d[10] = {2, 3, 4};
      DigitType r[10]; size_t size;

      REQUIRE(from_string("432", r, size, 10));
      REQUIRE(size == 3);
      for (size_t i = 0; i < 3; ++i)
         REQUIRE(d[i] == r[i]);
   }

   SECTION("Zero") {
      DigitType r[10]; size_t size;

      REQUIRE(from_string("0", r, size, 10));
      REQUIRE(size == 0);
      REQUIRE(from_string("000", r, size, 10));
      REQUIRE(size == 0);
   }

   string const licit_strings[] = {"    432"s, "  432  ", "432 abc", "\t432", " 432\t234", " 00432"};
   for (string const& s: licit_strings) {
      SECTION("licit leading and trailing : " + s) {
         const DigitType d[10] = {2, 3, 4};
         DigitType r[10]; size_t size;

         REQUIRE(from_string(s, r, size, 10));
         REQUIRE(size == 3);
         for (size_t i = 0; i < 3; ++i)
            REQUIRE(d[i] == r[i]);
      }
   }

   string const illicit_strings[] = {"hello"s, "43a2", "43abc", "123456787654561234565432345"};
   for (string const& s: illicit_strings) {
      SECTION("illicit leading and trailing : " + s) {
         DigitType r[10]; size_t size;
         REQUIRE_FALSE(from_string(s, r, size, 10));
      }
   }
}

TEST_CASE("3: add", "LongMath") {
   SECTION("sans report") {
      DigitType a[10] = {4, 3, 2, 1};
      DigitType b[10] = {3, 4, 5, 4, 3};
      DigitType c[10];
      size_t na = 4, nb = 5, nc;
      add(a, na, b, nb, c, nc, 10);
      REQUIRE(to_string(c, nc) == "35777");
      REQUIRE(nc == 5);
   }

   SECTION("avec report simple") {
      DigitType a[10] = {4, 3, 2, 1};
      DigitType b[10] = {7, 6, 5, 4, 3};
      DigitType c[10];
      size_t na = 4, nb = 5, nc;
      add(a, na, b, nb, c, nc, 10);
      REQUIRE(to_string(c, nc) == "35801");
      REQUIRE(nc == 5);
   }

   SECTION("avec report significatif") {
      DigitType a[10] = {4, 3, 2, 1, 8};
      DigitType b[10] = {7, 6, 5, 4, 3};
      DigitType c[10];
      size_t na = 5, nb = 5, nc;
      add(a, na, b, nb, c, nc, 10);
      REQUIRE(to_string(c, nc) == "115801");
      REQUIRE(nc == 6);
   }

   SECTION("overflow simple") {
      DigitType a[10] = {0, 9, 8, 7, 6, 5, 4, 3, 2, 8};
      DigitType b[10] = {0, 1, 2, 5, 3, 6, 5, 4, 3, 9};
      DigitType c[10];
      size_t na = 10, nb = 10, nc;
      add(a, na, b, nb, c, nc, 10);
      REQUIRE(to_string(c, nc) == "7580203100"); // modulo 10^10
      REQUIRE(nc == 10);
   }

   SECTION("overflow raccourcissant") {
      DigitType a[10] = {3, 3, 3, 3, 2, 2, 3, 4, 5, 6};
      DigitType b[10] = {2, 1, 0, 9, 8, 7, 6, 5, 4, 3};
      DigitType c[10];
      size_t na = 10, nb = 10, nc;
      add(a, na, b, nb, c, nc, 10);
      REQUIRE(to_string(c, nc) == "12345"); // modulo 10^10
      REQUIRE(nc == 5);
   }

    SECTION("Sums of 0") {
        DigitType a[10] = {0, 0, 0};
        DigitType b[10] = {0, 0, 0, 0, 0};
        DigitType c[10];
        size_t na = 3, nb = 5, nc;
        add(a, na, b, nb, c, nc, 10);
        REQUIRE(to_string(c, nc) == "0");
        REQUIRE(nc == 1);
    }
}

TEST_CASE("4: multiply", "LongMath") {
   SECTION("sans report") {
      DigitType a[10] = {2, 3, 2, 1};
      DigitType b[10] = {3};
      DigitType c[10];
      size_t na = 4, nb = 1, nc;
      multiply(a, na, b, nb, c, nc, 10);
      REQUIRE(to_string(c, nc) == "3696");
      REQUIRE(nc == 4);
   }

   SECTION("avec report") {
      DigitType a[10] = {4, 3, 2, 1};
      DigitType b[10] = {7, 6, 5, 4, 3};
      DigitType c[10];
      size_t na = 4, nb = 5, nc;
      multiply(a, na, b, nb, c, nc, 10);
      REQUIRE(to_string(c, nc) == "42655678");
      REQUIRE(nc == 8);
   }

   SECTION("overflow") {
      DigitType a[10] = {0, 9, 8, 7, 6, 5, 4, 3, 2, 8};
      DigitType b[10] = {0, 1, 2, 5, 3, 6, 5, 4, 3, 9};
      DigitType c[10];
      size_t na = 10, nb = 10, nc;
      multiply(a, na, b, nb, c, nc, 10);
      REQUIRE(to_string(c, nc) == "1919406900"); // modulo 10^10
      REQUIRE(nc == 10);
   }

   SECTION("overflow with decreasing size") {
      DigitType a[10] = {5, 4, 3, 2, 1};
      DigitType b[10] = {2, 6, 5, 0, 2, 7, 9};
      DigitType c[10];
      size_t na = 5, nb = 7, nc;
      multiply(a, na, b, nb, c, nc, 10);
      REQUIRE(to_string(c, nc) == "337890"); // modulo 10^10
      REQUIRE(nc == 6);
   }
}