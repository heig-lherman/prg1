#include "longmath.h"

using namespace std;

namespace longMath {
    string to_string(DigitType const tab[], size_t n) {
        if(n==0) return "0";

        string s;
        for(size_t i = n; i > 0; ) {
           s += char('0' + tab[--i]);
        }
        return s;
    }
}