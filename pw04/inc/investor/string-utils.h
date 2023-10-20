#ifndef INVESTOR_STRING_UTILS_H
#define INVESTOR_STRING_UTILS_H

#include <string>
#include <vector>

namespace investor::stringUtils {

    /**
     * Splits a string at every char to a vector
     * @param s The input string
     * @param delim The delimiter
     * @return A vector with the substrings
     */
    std::vector<std::string> split(const std::string &s, char delim, bool trim = false);

    /**
     * Trims a string from the left side, removing any space-like character
     * @param s The input string
     * @return The ltrimmed string
     */
    inline void ltrim(std::string &s);

    /**
     * Trims a string from the right side, removing any space-like character
     * @param s The input string
     * @return The rtrimmed string
     */
    inline void rtrim(std::string &s);

    /**
     * Trims a string from both sides, removing any space-like character
     * @param s The input string
     * @return The trimmed string
     */
    inline void trim(std::string &s);

}  // namespace investor::stringUtils

#endif  // INVESTOR_STRING_UTILS_H
