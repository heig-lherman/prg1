#include "montantEnToutesLettres.h"
#include <cmath>

using namespace std;

static constexpr long double MIN_INPUT = 0.L;
static constexpr long double MAX_INPUT = 999999999999.99L;
static constexpr char DIGIT_SEPARATOR = '-';
static constexpr char NUMBER_SEPARATOR = ' ';
static constexpr string_view NUMBER_CONJUNCTION = "et";

string convertNumberToString(unsigned long long, unsigned long);

/// Checks the user-defined input amount against defined boundaries
/// \param amount User-defined input amount
/// \param result A ref to a result string where the specific error message will be entered
/// \return Whether the input is valid or not (true means all checks passed)
bool checkBoundaries(long double amount, string &result) {
    if (amount < MIN_INPUT) {
        result = "montant negatif";
        return false;
    }

    if (amount > MAX_INPUT) {
        result = "montant trop grand";
        return false;
    }

    return true;
}

/// Rounds the input digit to a set amount of decimal places
/// \param value The input value
/// \param decimalPlaces The amount of decimal places to round up to
/// \return The rounded digit
long double roundUp(long double value, const int &decimalPlaces) {
    const long double multiplier = powl(10.0, decimalPlaces);
    return roundl(value * multiplier) / multiplier;
}

/// Splits the input amount in a fractional and whole part.
/// \param input The input, will be rounded up to the requested amount of decimal places
/// \param decimalPlaces Amount of decimal places to keep
/// \param fractionalPart A ref to where the fractional part should be saved
/// \param wholePart A ref to where the whole part should be saved
void splitFractionalDigit(
        long double input,
        const int decimalPlaces,
        unsigned long long &fractionalPart,
        unsigned long long &wholePart
) {
    long double whole, fraction;
    fraction = modf(roundUp(input, decimalPlaces), &whole);
    fractionalPart = (unsigned long long) roundl(fraction * powl(10.0, decimalPlaces));
    wholePart = (unsigned long long) whole;
}

/// Returns whether an adjective following the input number should use the plural version or not.
/// It is defined in the standard ruleset for the Canton de Vaud that any number that is greater or equal to 2
/// should pluralize an adjective following it.
/// \param number The input number
/// \return Whether an adjective following the number in letters should be pluralized or not
bool shouldFollowingAdjectiveBePlural(const unsigned long long number) {
    return number >= 2;
}

/// Returns whether the number is a multiple of a power of ten that is not considered a "simple word".
/// Those are defined by the standard rules to be any one-number-word higher than one thousand.
/// Considering our limits, those are only going to be multiples of "million" and "milliard"
/// \param number The input digit
/// \return Whether it is not considered to be a simple one-number-word
bool isNotRepresentableAsSimpleWord(const unsigned long number) {
    return number != 0 && (number % 1000000 == 0 || number % 1000000000 == 0);
}

/// Returns whether the number should include a conjunction word between the first and second words.
/// The convention defines those number as being all numbers ending with a 1 that are greater than 11, lower than 100.
/// \param modulus The current modulus that is being worked with
/// \param lastDigits The digits following the modulus (computed using number % modulus)
/// \return Whether it should use the standard conjunction between the modulus and the last digits
bool shouldIncludeNumberConjunction(const unsigned long modulus, const unsigned long long lastDigits) {
    return modulus >= 20 && modulus < 100 && lastDigits == 1;
}

/// Returns whether the current modulus should be displayed as the plural version or not.
/// The convention specifies that multiples of one hundred should be pluralized if it is not followed by anything,
/// unless it is followed by a fixed pluralize-able word.
/// It also specifies that "million" and "milliard" should be pluralized, which is defined in isNotRepresentableAsSimpleWord.
/// \param modulus The current modulus that is being worked with
/// \param parentPower The parent power of the current number that is being handled
/// \param firstDigits The digits preceding the modulus
/// \param lastDigits The digits following the modulus
/// \return Whether the plural version of the current word should be used
bool shouldUsePluralVersion(
        const unsigned long modulus,
        const unsigned long parentPower,
        const unsigned long long firstDigits,
        const unsigned long long lastDigits
) {
    if (modulus == 100) {
        return (parentPower == 0 || isNotRepresentableAsSimpleWord((unsigned long) pow(10.0, parentPower)))
               && shouldFollowingAdjectiveBePlural(firstDigits) && lastDigits == 0;
    }

    return isNotRepresentableAsSimpleWord(modulus);
}

/// Main computation function for handling the logic of dividing the number.
/// This function divides the number in two parts, the number preceding the modulus and the one following.
/// The modulus corresponds to the number representation of the single-word defined in the french language, that we
/// have to decompose. If it is a fixed number (like 12, for example), this method will not be called.
/// Once we have the preceding digits we can convert them to words individually, and then join them with the
/// string representation of the modulus, after checking whether we should use the plural version or not, and
/// afterwards, if needed, we can compute the following digits in word through recursion.
/// \param currentNumber The current number we are working with
/// \param modulus The current modulus (known french word)
/// \param parentPower The parent power of one thousand we have to handle, if the input number is less than
///                    one thousand it will be 0, otherwise 3, 6 or 9 depending on the scale.
///                    This is lowered when we handle the following part of the digit, which only happens
///                    if it is higher than one thousand, otherwise it will be resolved to the primitive
///                    and invariable numbers known in the french language.
/// \param singular The singular representation of the current modulus
/// \param plural The plural representation of the current modulus (= singular if invariable)
/// \return A full-string representation of the input number
string computeNumberToString(
        unsigned long long currentNumber,
        const unsigned long modulus,
        const unsigned long parentPower,
        const string &singular,
        const string &plural
) {
    const unsigned long long firstDigits = currentNumber / modulus;
    const unsigned long long lastDigits = currentNumber % modulus;

    string res;
    if (firstDigits == 1) {
        if (isNotRepresentableAsSimpleWord(modulus)) {
            // the modulus is considered an adjective, we need to prefix it with the number one
            res = convertNumberToString(1, 0) + NUMBER_SEPARATOR;
        }
        res += singular;
    } else {
        res = convertNumberToString(firstDigits, parentPower) + DIGIT_SEPARATOR;
        res += shouldUsePluralVersion(modulus, parentPower, firstDigits, lastDigits) ? plural : singular;
    }

    if (currentNumber == modulus || lastDigits == 0) {
        // there is no following digits, so we can stop there
        return res;
    }

    res += DIGIT_SEPARATOR;
    if (shouldIncludeNumberConjunction(modulus, lastDigits)) {
        res += NUMBER_CONJUNCTION;
        res += DIGIT_SEPARATOR;
    }
    return res + convertNumberToString(lastDigits, parentPower - 3);
}

/// Helper for computeNumberToString where the word representation is invariable.
string computeNumberToString(
        unsigned long long currentNumber,
        const unsigned long modulus,
        const unsigned long parentPower,
        const string &singular
) {
    return computeNumberToString(currentNumber, modulus, parentPower, singular, singular);
}

/// Entry point for the recursion and decomposing through the given number to resolve to known words.
/// <br>
/// Single-word numbers are also defined here, but the computeNumberToString function is
/// used for any word that allows to be composited with following or preceding digits.
/// Through recursion, we are able to resolve all known numbers down to the sixteen primary
/// one-word numbers, and the corresponding multiples of ten.
/// \param number The number to convert
/// \param parentPower The parent power of thousands, if coming from a recursive branch, otherwise set at 0
/// \return A string with the full-text representation of the input
string convertNumberToString(unsigned long long number, const unsigned long parentPower) {
    if (number >= 1000000000) return computeNumberToString(number, 1000000000, 9, "milliard", "milliards");
    if (number >= 1000000) return computeNumberToString(number, 1000000, 6, "million", "millions");
    if (number >= 1000) return computeNumberToString(number, 1000, 3, "mille");
    if (number >= 100) return computeNumberToString(number, 100, parentPower, "cent", "cents");
    if (number >= 90) return computeNumberToString(number, 90, parentPower, "nonante");
    if (number >= 80) return computeNumberToString(number, 80, parentPower, "huitante");
    if (number >= 70) return computeNumberToString(number, 70, parentPower, "septante");
    if (number >= 60) return computeNumberToString(number, 60, parentPower, "soixante");
    if (number >= 50) return computeNumberToString(number, 50, parentPower, "cinquante");
    if (number >= 40) return computeNumberToString(number, 40, parentPower, "quarante");
    if (number >= 30) return computeNumberToString(number, 30, parentPower, "trente");
    if (number >= 20) return computeNumberToString(number, 20, parentPower, "vingt");
    if (number == 16) return "seize";
    if (number == 15) return "quinze";
    if (number == 14) return "quatorze";
    if (number == 13) return "treize";
    if (number == 12) return "douze";
    if (number == 11) return "onze";
    if (number >= 10) return computeNumberToString(number, 10, parentPower, "dix");
    if (number == 9) return "neuf";
    if (number == 8) return "huit";
    if (number == 7) return "sept";
    if (number == 6) return "six";
    if (number == 5) return "cinq";
    if (number == 4) return "quatre";
    if (number == 3) return "trois";
    if (number == 2) return "deux";
    if (number == 1) return "un";
    return "zero";
}

/// Entry point for the conversion of a given number, the number will be decomposed into
/// all known number words of the French language within the defined bounds and assembled
/// using all the rules defined in the linguistic conventions of the Canton de Vaud.
/// \param fullNumber The given input number to be converted
/// \return A full string representation of the given number
string convertNumberToString(unsigned long long fullNumber) {
    return convertNumberToString(fullNumber, 0);
}

/// Allows to convert a number with an adjective suffix. The adjective will be itself suffixed
/// with an "s" if it should be pluralized (according to the official ruleset).
/// \param number The input number to convert
/// \param adjective The adjective to append
/// \return A full string representation of the given number with the appended adjective
string convertNumberToStringWithAdjective(unsigned long long number, const string &adjective) {
    string res = convertNumberToString(number) + NUMBER_SEPARATOR;
    if (isNotRepresentableAsSimpleWord(number)) {
        res += "de ";
    }
    res += adjective;
    if (shouldFollowingAdjectiveBePlural(number)) {
        res += "s";
    }
    return res;
}

/// Converts the given monetary inputs to their string representation and adds them to the returned
/// based of some logic:
///     - If there is >= 0 francs and 0 centimes, it will only display the francs
///     - If there is 0 francs and > 0 centimes, it will only display the centimes
///     - If there is > 0 francs and > 0 centimes, it will display both
/// \param francs The amount of francs to display
/// \param cents The amount of centimes to display
/// \return A full string representation of the given inputs formatted with the aforementioned logic.
string convertFrancsAndCentimes(unsigned long long francs, unsigned long long cents) {
    string strFrancs = convertNumberToStringWithAdjective(francs, "franc");
    string strCents = convertNumberToStringWithAdjective(cents, "centime");
    if (francs == 0) {
        if (cents > 0) {
            return strCents;
        }
        return strFrancs;
    }

    string res = strFrancs;
    if (cents > 0) {
        res += " et ";
        res += strCents;
    }
    return res;
}

string montantEnToutesLettres(long double montant) {
    string res;
    if (!checkBoundaries(montant, res)) {
        return "erreur : " + res;
    }

    unsigned long long francs;
    unsigned long long cents;
    splitFractionalDigit(montant, 2, cents, francs);

    return convertFrancsAndCentimes(francs, cents);
}
