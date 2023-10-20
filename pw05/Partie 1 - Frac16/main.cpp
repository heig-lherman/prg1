#include <iostream>
#include <functional>

#include "Frac16.h"

using namespace std;

template<typename Op>
void testOperator(Frac16 a, Frac16 b, Op op, string_view opString) {
    auto da = double(a);
    auto db = double(b);
    auto c = op(a, b);
    auto dc = op(da, db);
    cout << a << opString << b << " = "
         << c << " = " << double(c) << " = "
         << dc << " = " << da << opString << db << endl;
}

template<typename Op>
void testCompare(Frac16 a, Frac16 b, Op op, string_view opString) {
    if (op(a, b))
        cout << a << opString << b << endl;
}

void test(Frac16 a, Frac16 b) {
    testOperator(a, b, plus<>(), " + ");
    testOperator(a, b, minus<>(), " - ");
    testOperator(a, b, multiplies<>(), " * ");
    testOperator(a, b, divides<>(), " / ");

    testCompare(a, b, equal_to<>(), " == ");
    testCompare(a, b, not_equal_to<>(), " != ");
    testCompare(a, b, less<>(), " < ");
    testCompare(a, b, greater<>(), " > ");
    testCompare(a, b, less_equal<>(), " <= ");
    testCompare(a, b, greater_equal<>(), " >= ");

    cout << "++a : " << ++a << " , a++ : " << a++ << " , a-- : " << a-- << " , --a : " << --a << endl;
    cout << "++b : " << ++b << " , b++ : " << b++ << " , b-- : " << b-- << " , --b : " << --b << endl;
    cout << endl;
}

int main() {
    test(Frac16(3, 4), Frac16(5, 6));
    test(Frac16(3, 4), Frac16(5));
    test(-Frac16(3, 4), Frac16(5, 6));
    test(Frac16(3, 4), -Frac16(5, 6));
    test(Frac16(9, 12), Frac16(3, 4));
    test(Frac16(0), Frac16(5, 6));
    test(Frac16(3, 4), Frac16(0));
    test(Frac16(0), Frac16(0));
    test(Frac16(257, 258), Frac16(259, 260));
}