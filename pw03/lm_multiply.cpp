#include "longmath.h"
#include <cassert>

using namespace std;

namespace longMath {

    /// Extracts the carry digits from the multiplication
    /// \param number Result of the multiplication
    /// \return Anything preceding the smallest digit (123 -> returns 12, number = 3)
    DigitType extractCarry(DigitType &number) {
        DigitType carry = 0;
        if (number > 9) {
            carry = number / 10;
            number %= 10;
        }
        return carry;
    }

    /// Multiplies two digits together and returns the result as DigitType
    /// \param firstDigit The first digit to multiply
    /// \param secondDigit The second digit to multiply
    /// \return The result of the multiplication, although it could be more than a digit (up to 9 * 9 -> 81)
    constexpr DigitType multiplyTwoDigits(const DigitType firstDigit, const DigitType secondDigit) {
        return firstDigit * secondDigit;
    }

    /// Append the result of the multiplication to the result array, followed with the carry if needed
    /// The index should never be above the max capacity, or it would overflow the array.
    /// This function will also initialize the array with a 0 value if the current index is higher than the result size
    /// \param multipleToAdd The result of the multiplication to include
    /// \param index The current index (power of ten) we are working with
    /// \param result The result array
    /// \param resultSize The current size of the result array
    /// \param maxCapacity The maximum capacity of the result array
    void addMultiplicationToResult(
            const DigitType multipleToAdd, const size_t index,
            DigitType result[], size_t &resultSize,
            const size_t maxCapacity
    ) {
        assert(index < maxCapacity);
        DigitType &resultDigit = result[index];

        if (index >= resultSize) {
            resultDigit = 0;
            resultSize++;
        }

        resultDigit = (DigitType) (resultDigit + multipleToAdd);
        DigitType carry = extractCarry(resultDigit);

        if (carry && index + 1 < maxCapacity) {
            // Shifts the carry to the next position in the array, recursively until it would
            // overflow the array or the carry is 0
            addMultiplicationToResult(carry, index + 1, result, resultSize, maxCapacity);
        }
    }

    void multiply(
            const DigitType firstInput[], const size_t firstInputSize,
            const DigitType secondInput[], const size_t secondInputSize,
            DigitType result[], size_t &resultSize, const size_t maxCapacity
    ) {
        resultSize = 0;
        for (unsigned i = 0; i < secondInputSize; ++i) {
            DigitType secondInputDigit = secondInput[i];
            for (unsigned j = 0; j < firstInputSize && i + j < maxCapacity; ++j) {
                DigitType firstInputDigit = firstInput[j];
                DigitType currentResult = multiplyTwoDigits(secondInputDigit, firstInputDigit);
                addMultiplicationToResult(currentResult, i + j, result, resultSize, maxCapacity);
            }
        }
        trimOverflow(result, resultSize);
    }
}