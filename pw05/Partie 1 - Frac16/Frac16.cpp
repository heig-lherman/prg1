#include "Frac16.h"

#include <cassert>
#include <limits>

Frac16::Frac16(Frac16::type numerator, Frac16::type denominator) {
    assert(denominator != 0);
    this->numerator = numerator;
    this->denominator = denominator;
    isNegative = false;
    simplify();
}

// Type conversions

Frac16::operator double() const {
    double fractionResult = double(numerator) / denominator;
    return isNegative ? (-fractionResult) : fractionResult;
}

// Internal methods

unsigned long long Frac16::getGreatestCommonDivisor(unsigned long long n1, unsigned long long n2) {
    if (n1 == n2) {
        if (n1 == 0) {
            return 1;
        }

        return n1;
    }

    if (n1 < n2) {
        std::swap(n1, n2);
    }

    while (n2) {
        unsigned long long tmp;
        tmp = n2;
        n2 = n1 % n2;
        n1 = tmp;
    }

    return n1;
}

void Frac16::simplifyFractionArguments(unsigned long long &numerator, unsigned long long &denominator) {
    unsigned long long pgcd = getGreatestCommonDivisor(numerator, denominator);
    numerator /= pgcd;
    denominator /= pgcd;

    unsigned max = std::numeric_limits<Frac16::type>::max();
    while (numerator > max || denominator > max) {
        numerator >>= 1;
        denominator >>= 1;
    }
}

void Frac16::simplify() {
    unsigned long long numeratorValue = numerator;
    unsigned long long denominatorValue = denominator;

    simplifyFractionArguments(numeratorValue, denominatorValue);

    numerator = (Frac16::type) numeratorValue;
    denominator = (Frac16::type) denominatorValue;
}

// Unary operations (sign conversion)

Frac16 Frac16::operator-() const {
    Frac16 res(numerator, denominator);
    res.isNegative = !isNegative;
    return res;
}

// Arithmetic operations (compound assignments and binary arithmetic operators)

Frac16 &Frac16::operator+=(const Frac16 &rhs) {
    // x + -y = x - y
    if (!isNegative && rhs.isNegative) {
        *this -= -rhs;
        return *this;
    }

    // -x + y = y - x
    if (isNegative && !rhs.isNegative) {
        isNegative = false;
        *this = rhs - *this;
        return *this;
    }

    unsigned long long resultDenominator = ((unsigned long long) denominator * rhs.denominator)
                                           / getGreatestCommonDivisor(denominator, rhs.denominator);
    unsigned long long resultNumerator = numerator * (resultDenominator / denominator)
                                         + rhs.numerator * (resultDenominator / rhs.denominator);

    simplifyFractionArguments(resultNumerator, resultDenominator);

    numerator = (Frac16::type) resultNumerator;
    denominator = (Frac16::type) resultDenominator;

    simplify();

    return *this;
}

Frac16 &Frac16::operator-=(const Frac16 &rhs) {
    // -x - y = - (x + y)
    if (isNegative && !rhs.isNegative) {
        isNegative = false;
        *this += rhs;
        isNegative = true;
        return *this;
    }

    // -x - -y = -x + y
    // x - -y = x + y
    if (rhs.isNegative) { ;
        *this += -rhs;
        return *this;
    }

    unsigned long long resultNumerator;
    unsigned long long resultDenominator = ((unsigned long long) denominator * rhs.denominator)
                                           / getGreatestCommonDivisor(denominator, rhs.denominator);

    if (*this >= rhs) {
        resultNumerator = numerator * (resultDenominator / denominator)
                          - rhs.numerator * (resultDenominator / rhs.denominator);
    } else {
        isNegative = true;
        resultNumerator = rhs.numerator * (resultDenominator / rhs.denominator)
                          - numerator * (resultDenominator / denominator);
    }

    simplifyFractionArguments(resultNumerator, resultDenominator);

    numerator = (Frac16::type) resultNumerator;
    denominator = (Frac16::type) resultDenominator;

    simplify();

    return *this;
}

Frac16 &Frac16::operator*=(const Frac16 &rhs) {
    isNegative = (rhs.isNegative && !isNegative) || (!rhs.isNegative && isNegative);

    unsigned long long resultNumerator = numerator * rhs.numerator;
    unsigned long long resultDenominator = denominator * rhs.denominator;

    simplifyFractionArguments(resultNumerator, resultDenominator);

    numerator = (Frac16::type) resultNumerator;
    denominator = (Frac16::type) resultDenominator;

    simplify();

    return *this;
}

Frac16 &Frac16::operator/=(const Frac16 &rhs) {
    Frac16 rhsInvert = rhs;
    std::swap(rhsInvert.numerator, rhsInvert.denominator);
    return *this *= rhsInvert;
}

// Equality

bool Frac16::operator==(const Frac16 &rhs) const {
    return (isNegative == rhs.isNegative)
           && (numerator == rhs.numerator)
           && (denominator == rhs.denominator);
}

// Comparison

bool Frac16::operator<(const Frac16 &rhs) const {
    if (isNegative && !rhs.isNegative) {
        return true;
    }

    if (!isNegative && rhs.isNegative) {
        return false;
    }

    if (denominator == rhs.denominator) {
        return isNegative == (numerator >= rhs.numerator);
    }

    return isNegative == ((numerator * rhs.denominator) >= (rhs.numerator * denominator));
}

// Increment / Decrement

Frac16 &Frac16::operator++() {
    operator+=(Frac16(1));
    return *this;
}

Frac16 Frac16::operator++(int) &{ // NOLINT(cert-dcl21-cpp)
    Frac16 old = *this;
    operator++();
    return old;
}

Frac16 &Frac16::operator--() {
    operator-=(Frac16(1));
    return *this;
}

Frac16 Frac16::operator--(int) &{ // NOLINT(cert-dcl21-cpp)
    Frac16 old = *this;
    operator--();
    return old;
}

// Display operator

std::ostream &operator<<(std::ostream &os, const Frac16 &frac) {
    if (frac.numerator == 0 && frac.denominator == 0) {
        os << "nan";
        return os;
    }

    if (frac.denominator == 0) {
        os << "inf";
        return os;
    }

    if (frac.isNegative) {
        os << "-";
    }

    if (frac.denominator == 1) {
        os << frac.numerator;
        return os;
    }

    os << frac.numerator << "/" << frac.denominator;
    return os;
}
