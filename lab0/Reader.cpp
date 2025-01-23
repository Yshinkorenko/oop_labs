#include "Reader.h"
#include <fstream>
#include <stdexcept>

std::list<std::string> Reader::readFromFile(const std::string& filename) {
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        throw std::runtime_error("Error: Could not open input file.");
    }

    std::list<std::string> lines;
    std::string line;
    while (std::getline(inputFile, line)) {
        lines.push_back(line);
    }

    inputFile.close();
    return lines;
}
