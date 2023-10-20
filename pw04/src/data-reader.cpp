#include "investor/data-reader.h"

#include <algorithm>
#include <cassert>
#include <string>
#include <vector>

#include "investor/string-utils.h"

using namespace std;

namespace investor {

    MarketData mapDataLine(const vector<string> &lineParts) {
        return {lineParts[0],        stold(lineParts[1]), stold(lineParts[2]),
                stold(lineParts[3]), stold(lineParts[4]), stoull(lineParts[5])};
    }

    vector<MarketData> read(istream &fileStream, bool sortOldestFirst) {
        vector<MarketData> res;

        string line;
        string header;

        getline(fileStream, header);
        while (getline(fileStream, line)) {
            vector<string> lineParts = stringUtils::split(line, ',', true);
            assert(lineParts.size() >= 6);

            bool hasStar = any_of(lineParts.begin() + 1, lineParts.end(),
                                  [](const string &s) { return s == "*"; });
            if (hasStar) {
                // The current day is a closed day, no data can be extracted
                continue;
            }

            res.push_back(mapDataLine(lineParts));
        }

        if (sortOldestFirst) {
            return {res.rbegin(), res.rend()};
        }

        return res;
    }

}  // namespace investor
