#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>

typedef unsigned int uint;
typedef unsigned long long ull;
typedef long double ldouble;

using namespace std;

string dec2binary(ull num, uint fixedLength) {
    string res;
    for (uint i = 0; i < fixedLength; ++i) {
        res += to_string(num % 2);
        num /= 2;
    }
    return string{res.rbegin(), res.rend()};
}

int main() {
    constexpr short OUTPUT_FIRST_COL_LENGTH = 15;

    string srcNum_str;
    uint nbTotalBits;
    uint nbMantissaBits;
    cout << "Entrez un nombre reel, le nombre de bits total et celui de la mantisse " << endl;
    cin >> srcNum_str >> nbTotalBits >> nbMantissaBits;
    uint nbExpBits = nbTotalBits - nbMantissaBits - 1;

    if (srcNum_str == "0" || srcNum_str == "-0") {
        cout << left << setw(OUTPUT_FIRST_COL_LENGTH) << "Representation" << " : "
             << (srcNum_str[0] == '-' ? "1 " : "0 ")
             << string(nbExpBits, '0') << " " << string(nbMantissaBits, '0') << endl;
        return EXIT_SUCCESS;
    }
    cout << endl;
    ldouble srcNum{stold(srcNum_str)};

    bool sign = srcNum < 0.f;
    srcNum = abs(srcNum);

    int bias = (int) pow(2, nbExpBits - 1) - 1;
    int exponent = (int) floor(log2(srcNum));
    uint biasedExp = (uint) (exponent + bias);
    string biasedExpBinary = dec2binary(biasedExp, nbExpBits);

    ldouble scientificNum = srcNum / pow(2, exponent) - 1;
    ull mantissaDenominator = (ull) pow(2, nbMantissaBits);
    ull mantissaNumerator = (ull) round(scientificNum * mantissaDenominator);
    string mantissaBinary = dec2binary(mantissaNumerator, nbMantissaBits);

    cout << fixed << setprecision(6)
         << srcNum_str << " = " << (sign ? "-" : "+") << 1 + scientificNum << " * ( 2 ^ " << exponent << " )"
         << "\n" << endl;

    string biasedExpDisplay = to_string(exponent) + " + " + to_string(bias) + " = " + to_string(biasedExp);
    string mantissaDisplay = "1 + ( " + to_string(mantissaNumerator) + " / " + to_string(mantissaDenominator) + " )";
    string floatingPointDisplay = to_string(sign) + " " + biasedExpBinary + " " + mantissaBinary;

    const string sep = " : ";
    const int sepLen = OUTPUT_FIRST_COL_LENGTH + (int) sep.size();
    cout << left << setw(OUTPUT_FIRST_COL_LENGTH) << "Signe" << sep << (sign ? "-1" : "+1") << "\n"
         << right << setw(sepLen) << sep << sign << "\n" << endl;
    cout << left << setw(OUTPUT_FIRST_COL_LENGTH) << "Exposant biaise" << sep << biasedExpDisplay << "\n"
         << right << setw(sepLen) << sep << biasedExpBinary << "\n" << endl;
    cout << left << setw(OUTPUT_FIRST_COL_LENGTH) << "Mantisse" << sep << mantissaDisplay << "\n"
         << right << setw(sepLen) << sep << mantissaBinary << "\n" << endl;
    cout << left << setw(OUTPUT_FIRST_COL_LENGTH) << "Representation" << sep << floatingPointDisplay << endl;

    return EXIT_SUCCESS;
}
