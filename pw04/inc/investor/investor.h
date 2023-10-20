#ifndef INVESTOR_INVESTOR_H
#define INVESTOR_INVESTOR_H

#include <istream>
#include <ostream>
#include <string>

namespace investor {

    /**
     * Main entry point for the calculations of investment strategies,
     * takes in a data stream and processes the data.
     * @param inputStream The input stream to process
     * @param outputStream Where to output the data
     */
    void process(std::istream &inputStream, std::ostream &outputStream);

    void process(const std::string &inputFilePath, const std::string &outputFilePath);

    void process(const std::string &inputFilePath, std::ostream &outputStream);

    void process(std::istream &inputStream, const std::string &outputFilePath);

}  // namespace investor

#endif  // INVESTOR_INVESTOR_H
