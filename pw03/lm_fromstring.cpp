#include "longmath.h"
#include <string>
#include <cassert>

using namespace std;

namespace longMath {

    /// Returns whether the input char is a numeric character ('0' >= digit >= '9')
    /// \param digit The char to check
    /// \return Whether the input char is a numeric character
    constexpr bool isNumeric(const char digit) {
        return digit >= '0' && digit <= '9';
    }

    /// Pushes a value to the front of the given array,
    /// the resultSize must be within the bounds of the declared array
    /// \param value The value to add
    /// \param result The result array where the value should be added
    /// \param resultSize The last index of the digits present in the array
    ///                   (must be greater than 0, less than the capacity of the given array)
    void pushFront(const DigitType value, DigitType result[], size_t &resultSize) {
        assert(value <= 9);
        for (size_t i = resultSize; i > 0; --i) {
            result[i] = result[i - 1];
        }
        result[0] = value;
        resultSize++;
    }

    /// Converts the input character to a digit representation ('0' -> 0)
    /// \param charDigit The input char, must be within numeric bounds ('0' >= charDigit >= '9')
    /// \return The char as a number, in the range 0 to 9.
    DigitType convertCharToDigit(char charDigit) {
        assert(isNumeric(charDigit));
        return (DigitType) (charDigit - '0');
    }

    bool from_string(
            const string &inputNum,
            DigitType result[], size_t &resultSize, const size_t maxCapacity
    ) {
        resultSize = 0;
        for (char charDigit: inputNum) {
            if (isspace(charDigit)) {
                if (resultSize > 0) {
                    return true;
                }
                continue;
            }

            if (!isNumeric(charDigit)) {
                return false;
            }

            // skip leading zeros
            if (resultSize == 0 && charDigit == '0') {
                continue;
            }

            // the input digit would overflow our array capacity
            if (resultSize + 1 > maxCapacity) {
                return false;
            }

            pushFront(convertCharToDigit(charDigit), result, resultSize);
        }
        return true;
    }
}