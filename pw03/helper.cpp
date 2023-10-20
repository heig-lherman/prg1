#include "longmath.h"

namespace longMath {

    void trimOverflow(const DigitType result[], size_t &resultSize) {
        size_t i = resultSize - 1;

        while (result[i] == (DigitType) 0 && i > 0) {
            --i;
            --resultSize;
        }
    }
}
