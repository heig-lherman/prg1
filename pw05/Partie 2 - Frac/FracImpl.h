#ifndef PRG1_D21_L5_FRACTIONS_FRACIMPL_H
#define PRG1_D21_L5_FRACTIONS_FRACIMPL_H

// type conversions

template<typename T>
Frac<T>::operator double() const {
    double fractionResult = double(numerator) / denominator;
    return isNegative ? (-fractionResult) : fractionResult;
}

// Internal methods

template<typename T>
unsigned long long Frac<T>::getGreatestCommonDivisor(unsigned long long n1, unsigned long long n2) {
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

template<typename T>
void Frac<T>::simplifyFractionArguments(unsigned long long &numerator, unsigned long long &denominator) {
    unsigned long long pgcd = getGreatestCommonDivisor(numerator, denominator);
    numerator /= pgcd;
    denominator /= pgcd;

    unsigned long long max = std::numeric_limits<T>::max();
    while (numerator > max || denominator > max) {
        // divide by two using bit shift
        numerator >>= 1;
        denominator >>= 1;
    }
}

template<typename T>
void Frac<T>::simplify() {
    unsigned long long numeratorValue = numerator;
    unsigned long long denominatorValue = denominator;

    simplifyFractionArguments(numeratorValue, denominatorValue);

    numerator = (T) numeratorValue;
    denominator = (T) denominatorValue;
}

// Unary operations (sign conversion)

template<typename T>
Frac<T> Frac<T>::operator-() const {
    Frac res(numerator, denominator);
    res.isNegative = !isNegative;
    return res;
}

// Arithmetic operations (compound assignments and binary arithmetic operators)
template<typename T>
Frac<T> &Frac<T>::operator+=(const Frac<T> &rhs) {
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

    numerator = (T) resultNumerator;
    denominator = (T) resultDenominator;

    simplify();

    return *this;
}


template<typename T>
Frac<T> &Frac<T>::operator-=(const Frac<T> &rhs) {
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

    numerator = (T) resultNumerator;
    denominator = (T) resultDenominator;

    simplify();

    return *this;
}

template<typename T>
Frac<T> &Frac<T>::operator*=(const Frac<T> &rhs) {
    isNegative = (rhs.isNegative && !isNegative) || (!rhs.isNegative && isNegative);

    unsigned long long resultNumerator = (unsigned long long) numerator * rhs.numerator;
    unsigned long long resultDenominator = (unsigned long long) denominator * rhs.denominator;

    simplifyFractionArguments(resultNumerator, resultDenominator);

    numerator = (T) resultNumerator;
    denominator = (T) resultDenominator;

    simplify();

    return *this;
}

template<typename T>
Frac<T> &Frac<T>::operator/=(const Frac<T> &rhs) {
    Frac rhsInvert = rhs;
    std::swap(rhsInvert.numerator, rhsInvert.denominator);
    return *this *= rhsInvert;
}

// Equality

template<typename T>
bool Frac<T>::operator==(const Frac<T> &rhs) const {
    return (isNegative == rhs.isNegative)
           && (numerator == rhs.numerator)
           && (denominator == rhs.denominator);
}

// Comparison

template<typename T>
bool Frac<T>::operator<(const Frac<T> &rhs) const {
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

template<typename T>
Frac<T> &Frac<T>::operator++() {
    operator+=(Frac(1));
    return *this;
}

template<typename T>
Frac<T> Frac<T>::operator++(int) &{ // NOLINT(cert-dcl21-cpp)
    Frac old = *this;
    operator++();
    return old;
}

template<typename T>
Frac<T> &Frac<T>::operator--() {
    operator-=(Frac(1));
    return *this;
}

template<typename T>
Frac<T> Frac<T>::operator--(int) &{ // NOLINT(cert-dcl21-cpp)
    Frac old = *this;
    operator--();
    return old;
}

// Display operator

template<typename T>
std::ostream &operator<<(std::ostream &os, const Frac<T> &frac) {
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
        os << +frac.numerator;
        return os;
    }

    os << +frac.numerator << "/" << +frac.denominator;
    return os;
}

#endif //PRG1_D21_L5_FRACTIONS_FRACIMPL_H
