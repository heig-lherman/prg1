#ifndef PRG1_LABOS_2021_FRAC2_H
#define PRG1_LABOS_2021_FRAC2_H

#include "FracTypeChooser.h"

#include <cassert>
#include <limits>
#include <ostream>
#include <type_traits>

template<typename T> class Frac;
template<typename T> std::ostream &operator<<(std::ostream &os, const Frac<T> &frac);

template<typename T>
class Frac {
public:
    static_assert(
            sizeof(T) <= 4 && std::is_unsigned<T>::value && std::is_integral<T>::value,
            "T should fit within 32 bits (4 bytes) and should be an unsigned integer"
    );

    // Default constructor

    explicit Frac(T numerator = 0, T denominator = 1) {
        assert(denominator);
        this->numerator = numerator;
        this->denominator = denominator;
        isNegative = false;
        simplify();
    }

    // Copy constructor

    template<typename U>
    Frac(const Frac<U> &frac) { // NOLINT(google-explicit-constructor, cppcoreguidelines-pro-type-member-init)
        initValues(frac);
    }

    // Assignment

    template<typename U>
    Frac<T> &operator=(const Frac<U> &rhs) {
        // not a self-assignment
        if (this != &rhs) {
            initValues(rhs);
        }

        return *this;
    }

    // Type conversions

    explicit operator double() const;

    // Unary operators

    Frac<T> operator-() const;

    // Operations

    template<typename U> Frac<T> &operator+=(const Frac<U> &rhs);
    template<typename U> inline Frac<LargerType<T, U>> operator+(const Frac<U> &rhs) const { return Frac<LargerType<T, U>>(*this) += rhs; }

    template<typename U> Frac<T> &operator-=(const Frac<U> &rhs);
    template<typename U> inline Frac<LargerType<T, U>> operator-(const Frac<U> &rhs) const { return Frac<LargerType<T, U>>(*this) -= rhs; }

    template<typename U> Frac<T> &operator*=(const Frac<U> &rhs);
    template<typename U> inline Frac<LargerType<T, U>> operator*(const Frac<U> &rhs) const { return Frac<LargerType<T, U>>(*this) *= rhs; }

    template<typename U> Frac<T> &operator/=(const Frac<U> &rhs);
    template<typename U> inline Frac<LargerType<T, U>> operator/(const Frac<U> &rhs) const { return Frac<LargerType<T, U>>(*this) /= rhs; }

    // Comparisons

    template<typename U> bool operator==(const Frac<U> &rhs) const;
    template<typename U> inline bool operator!=(const Frac<U> &rhs) const { return !(operator==(rhs)); }

    template<typename U> bool operator<(const Frac<U> &rhs) const;
    template<typename U> inline bool operator>(const Frac<U> &rhs) const { return rhs < *this; }
    template<typename U> inline bool operator<=(const Frac<U> &rhs) const { return !(operator>(rhs)); }
    template<typename U> inline bool operator>=(const Frac<U> &rhs) const { return !(operator<(rhs)); }

    // Increment / Decrement

    Frac<T> &operator++();
    Frac<T> operator++(int) &; // NOLINT(cert-dcl21-cpp)

    Frac<T> &operator--();
    Frac<T> operator--(int) &; // NOLINT(cert-dcl21-cpp)

    // Display

    friend std::ostream &operator<< <>(std::ostream &os, const Frac<T> &frac);

private:
    bool isNegative;
    T numerator, denominator;

    template<typename U>
    friend class Frac;

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

    /**
     * Assigns the data to this fraction from a different fraction.
     * @tparam U Type of the other fraction (will be cast to T)
     * @param other The other action to assign from
     */
    template<typename U>
    void initValues(const Frac<U> &other);
};

#include "FracImpl.h"

#endif //PRG1_LABOS_2021_FRAC2_H