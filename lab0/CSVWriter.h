#ifndef CSVWRITER_H
#define CSVWRITER_H

#include <string>
#include <vector>

class CSVWriter {
public:
    static void writeToFile(const std::string& filename, const std::vector<std::pair<std::string, int>>& data, int totalWords);
};

#endif
