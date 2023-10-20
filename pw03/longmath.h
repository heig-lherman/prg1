#ifndef PRG1_D21_LONGMATH_H
#define PRG1_D21_LONGMATH_H

#include <string>

namespace longMath {
    using DigitType = unsigned char;

    std::string to_string(DigitType const tab[], size_t n);

    /// Converts a given number into an array of digits, with the least significant digit assigned
    /// as the last value, and the most significant digit as the first value. (1234 -> {4, 3, 2, 1})
    /// \param inputNum The given number
    /// \param result A reference to the array where the result should be stored
    /// \param resultSize A reference to a variable where the total amount of digits parsed will be saved
    /// \param maxCapacity A reference to the maximum capacity of the given array, if the inputNum overflows it will return false
    /// \return Whether the input number has been parsed successfully or not
    bool from_string(const std::string &inputNum, DigitType result[], size_t &resultSize, size_t maxCapacity);

    /// Add two arrays of digits together
    /// \param firstInput The first array for the operation
    /// \param firstInputSize The size of the first array
    /// \param secondInput The second array for the operation
    /// \param secondInputSize The size of the second array
    /// \param result An array where the result will be saved
    /// \param resultSize The size of the final result
    /// \param maxCapacity The max capacity for the result array
    void add(
            const DigitType firstInput[], size_t firstInputSize,
            const DigitType secondInput[], size_t secondInputSize,
            DigitType result[], size_t &resultSize, size_t maxCapacity
    );

    /// Multiply two arrays of digits together
    /// \param firstInput The first array for the operation
    /// \param firstInputSize The size of the first array
    /// \param secondInput The second array for the operation
    /// \param secondInputSize The size of the second array
    /// \param result An array where the result will be saved
    /// \param resultSize The size of the final result
    /// \param maxCapacity The max capacity for the result array
    void multiply(
            const DigitType firstInput[], size_t firstInputSize,
            const DigitType secondInput[], size_t secondInputSize,
            DigitType result[], size_t &resultSize, size_t maxCapacity
    );

    /// Delete all the '0' found at the end of an array of digits
    /// \param result The array to trim
    /// \param resultSize The size of the array
    void trimOverflow(const DigitType result[], size_t &resultSize);
}

#endif //PRG1_D21_LONGMATH_H
