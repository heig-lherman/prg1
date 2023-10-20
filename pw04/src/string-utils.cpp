#include "investor/string-utils.h"

#include <sstream>
#include <string>
#include <vector>

using namespace std;

namespace investor::stringUtils {

    vector<string> split(const string &s, const char delim, bool trim) {
        stringstream ss(s);
        string item;
        vector<string> res;
        while (getline(ss, item, delim)) {
            if (trim) {
                stringUtils::trim(item);
            }
            res.push_back(item);
        }
        return res;
    }

    inline void ltrim(string &s) {
        auto find = find_if(s.begin(), s.end(), [](unsigned char ch) { return !isspace(ch); });
        s.erase(s.begin(), find);
    }

    inline void rtrim(string &s) {
        auto find = find_if(s.rbegin(), s.rend(), [](unsigned char ch) { return !isspace(ch); });
        s.erase(find.base(), s.end());
    }

    inline void trim(string &s) {
        ltrim(s);
        rtrim(s);
    }

}  // namespace investor::stringUtils
