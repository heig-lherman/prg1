#include "longmath.h"
#include <cassert>

using namespace std;

namespace longMath {

    /// Return the maximum of the two given sizes
    /// \param firstInputSize The first input size to compare
    /// \param secondInputSize The second input size to compare
    /// \return A copy of the maximum value of the two inputs
    constexpr size_t getBiggestInput(const size_t firstInputSize, const size_t secondInputSize) {
        return firstInputSize > secondInputSize ? firstInputSize : secondInputSize;
    }

    /// Return the sum of the two given digits
    /// \param firstDigit The first digit to add
    /// \param secondDigit The second digit to add
    /// \return The sum of the two digits, could be more than a single digit (up to 9 + 9 -> 18)
    constexpr DigitType addTwoDigits(const DigitType firstDigit, const DigitType secondDigit) {
        return firstDigit + secondDigit;
    }

    /// Return whether the input number is single digits or not.
    /// If the number has two digits, we keep only the last digit (mod 10).
    /// \param number The input number to check, expected to be less or equal to 18
    /// \return Whether the input number has a carry or not
    bool hasCarry(DigitType &number) {
        assert(number <= 18);
        if (number > (DigitType) 9) {
            number %= 10;
            return true;
        }
        return false;
    }

    void add(
            const DigitType firstInput[], size_t firstInputSize,
            const DigitType secondInput[], size_t secondInputSize,
            DigitType result[], size_t &resultSize, size_t maxCapacity
    ) {
        resultSize = 0;
        bool carry = false;
        size_t maxInputSize = getBiggestInput(firstInputSize, secondInputSize);

        for (size_t i = 0; i < maxInputSize; ++i) {
            DigitType firstInputDigit = (i < firstInputSize ? firstInput[i] : (DigitType) 0);
            DigitType secondInputDigit = (i < secondInputSize ? secondInput[i] : (DigitType) 0);

            DigitType tmp = addTwoDigits(firstInputDigit, secondInputDigit);
            if (carry) {
                tmp = addTwoDigits(tmp, (DigitType) 1);
            }
            carry = hasCarry(tmp);
            result[i] = tmp;
        }
        resultSize = maxInputSize;

        if (carry && resultSize < maxCapacity) {
            result[maxInputSize] = (DigitType) 1;
            ++resultSize;
        } else {
            trimOverflow(result, resultSize);
        }
    }
}