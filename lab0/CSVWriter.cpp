#include "CSVWriter.h"
#include <fstream>

void CSVWriter::writeToFile(const std::string& filename, const std::vector<std::pair<std::string, int>>& data, int totalWords) {
    std::ofstream outputFile(filename);
    if (!outputFile.is_open()) {
        throw std::runtime_error("Error: Could not open output file.");
    }

    outputFile << "Word,Frequency,Percentage\n";
    for (const auto& [word, count] : data) {
        double percentage = (static_cast<double>(count) / totalWords) * 100;
        outputFile << word << "," << count << "," << std::fixed << std::setprecision(2) << percentage << "%\n";
    }

    outputFile.close();
}
