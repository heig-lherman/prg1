#ifndef INVESTOR_DATA_READER_H
#define INVESTOR_DATA_READER_H

#include <istream>
#include <string>
#include <vector>

namespace investor {

    /**
     * Market data is the basic data parsed from the given file
     */
    struct MarketData {
        std::string date;
        long double close;
        long double open;
        long double high;
        long double low;
        unsigned long long volume;
    };

    /**
     * Read data from a file stream
     * @param fileStream An open file stream, will be read and then closed.
     * @param sortOldestFirst Reverses the input data
     * @return A vector of market data parsed from the given file
     */
    std::vector<MarketData> read(std::istream &fileStream, bool sortOldestFirst = true);

}  // namespace investor

#endif  // INVESTOR_DATA_READER_H
