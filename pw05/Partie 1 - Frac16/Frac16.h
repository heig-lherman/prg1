#ifndef PRG1_LABOS_2021_FRAC16_H
#define PRG1_LABOS_2021_FRAC16_H

#include <ostream>

class Frac16 {
public:
    using type = unsigned short;

    explicit Frac16(type numerator = 0, type denominator = 1);

    // Type conversions

    explicit operator double() const;

    // Unary operators

    Frac16 operator-() const;

    // Operations

    Frac16 &operator+=(const Frac16 &rhs);
    inline Frac16 operator+(const Frac16 &rhs) const { return Frac16(*this) += rhs; }

    Frac16 &operator-=(const Frac16 &rhs);
    inline Frac16 operator-(const Frac16 &rhs) const { return Frac16(*this) -= rhs; };

    Frac16 &operator*=(const Frac16 &rhs);
    inline Frac16 operator*(const Frac16 &rhs) const { return Frac16(*this) *= rhs; };

    Frac16 &operator/=(const Frac16 &rhs);
    inline Frac16 operator/(const Frac16 &rhs) const { return Frac16(*this) /= rhs; };

    // Comparisons

    bool operator==(const Frac16 &rhs) const;
    inline bool operator!=(const Frac16 &rhs) const { return !(operator==(rhs)); }

    bool operator<(const Frac16 &rhs) const;
    inline bool operator>(const Frac16 &rhs) const { return rhs < *this; }
    inline bool operator<=(const Frac16 &rhs) const { return !(operator>(rhs)); }
    inline bool operator>=(const Frac16 &rhs) const { return !(operator<(rhs)); }

    // Increment / Decrement

    Frac16& operator++();
    Frac16 operator++(int) &; // NOLINT(cert-dcl21-cpp)

    Frac16& operator--();
    Frac16 operator--(int) &; // NOLINT(cert-dcl21-cpp)

    // Display

    friend std::ostream &operator<<(std::ostream &os, const Frac16 &frac);

private:
    bool isNegative;
    type numerator, denominator;

    /**
     * Computes the greatest common divisor between the two given input numbers
     * @param n1 First number
     * @param n2 Second number
     * @return The GCD of the two numbers
     */
    static unsigned long long getGreatestCommonDivisor(unsigned long long n1, unsigned long long n2);

    /**
     * Simplifies two numbers representing a numerator and denominator of some fraction.
     * It first computes the GCD and divides the two numbers with it to simplify the fraction.
     * If any of the two numbers cannot fit for Frac16, they are both truncated equally to get
     * the 16 most significant bits.
     * @param numerator A numerator from a calculation
     * @param denominator A denominator from a calculation
     */
    static void simplifyFractionArguments(unsigned long long &numerator, unsigned long long &denominator);

    /**
     * Divides the numerator and denominator by the GCD of the two.
     */
    void simplify();
};

#endif //PRG1_LABOS_2021_FRAC16_H
