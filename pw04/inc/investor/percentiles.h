#ifndef INVESTOR_PERCENTILES_H
#define INVESTOR_PERCENTILES_H

#include <ostream>
#include <string>
#include <vector>

namespace investor {

    /**
     * Orders the given data and takes the n-th percentile value
     * @param values The data to compute, unordered
     * @param percentile The percentile to use
     * @return The value at the n-th percentile
     */
    long double getPercentileValue(const std::vector<long double> &values, double percentile);

    /**
     * Pipes the percentile line to the output stream
     * @param outputStream Where to output the data
     * @param strategyName What is the name of the strategy percentiles
     * @param percentileValues The percentile values for the strategy
     */
    void outputPercentilesAsCSV(std::ostream &outputStream, const std::string &strategyName,
                                const std::vector<long double> &percentileValues,
                                long double initialCashAmount);

    /**
     * @param percentages Percentages to pretty-print
     * @return pretty-printed string for CSV output
     */
    std::string prettyPrintPercentileNames(const std::vector<double> &percentages);

}  // namespace investor

#endif  // INVESTOR_PERCENTILES_H
