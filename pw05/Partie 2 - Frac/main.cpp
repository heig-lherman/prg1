#include "Frac.h"
#include <iostream>
#include <vector>
#include <functional>
#include <cmath>
#include <iomanip>

using namespace std;

template<typename Op, typename T>
void testOperator(Frac<T> a, Frac<T> b, Op op, string_view opString) {
   auto da = double(a);
   auto db = double(b);
   auto c = op(a,b);
   auto dc = op(da,db);
   cout << a << opString << b << " = "
   << c <<  " = " << double(c) << " = " << dc << " = " << da << opString << db << endl;
}

template<typename Op, typename T>
void testCompare(Frac<T> a, Frac<T> b, Op op, string_view opString) {
   if(op(a,b))
      cout << a << opString << b << endl;
}

template<typename T>
void test(Frac<T> a, Frac<T> b) {
   testOperator(a,b,plus<>()," + ");
   testOperator(a,b,minus<>()," - ");
   testOperator(a,b,multiplies<>()," * ");
   testOperator(a,b,divides<>()," / ");

   testCompare(a,b,equal_to<>()," == ");
   testCompare(a,b,not_equal_to<>()," != ");
   testCompare(a,b,less<>()," < ");
   testCompare(a,b,greater<>()," > ");
   testCompare(a,b,less_equal<>()," <= ");
   testCompare(a,b,greater_equal<>()," >= ");

   cout << "++a : " << ++a << " , a++ : " << a++ << " , a-- : " << a-- << " , --a : " << --a << endl;
   cout << "++b : " << ++b << " , b++ : " << b++ << " , b-- : " << b-- << " , --b : " << --b << endl;
   cout << endl;
}

template<typename T>
void test_all() {
   test(Frac<T>(3, 4), Frac<T>(5, 6));
   test(Frac<T>(3, 4), Frac<T>(5));
   test(-Frac<T>(3, 4), Frac<T>(5, 6));
   test(Frac<T>(3, 4), -Frac<T>(5, 6));
   test(Frac<T>(9, 12), Frac<T>(3, 4));
   test(Frac<T>(0), Frac<T>(5, 6));
   test(Frac<T>(3, 4), Frac<T>(0));
   test(Frac<T>(), Frac<T>());
   T val = std::numeric_limits<T>::max() / 2;
   test(Frac<T>(T(val+1), T(val+2)), Frac<T>(T(val+3),T(val+4)));
}

int main() {
   cout << "Frac<unsigned char>\n";
   test_all<unsigned char>();
   cout << "\nFrac<unsigned short>\n";
   test_all<unsigned short>();
   cout << setprecision(12);
   cout << "\nFrac<unsigned int>\n";
   test_all<unsigned int>();
}