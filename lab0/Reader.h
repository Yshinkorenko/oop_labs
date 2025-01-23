#ifndef READER_H
#define READER_H

#include <list>
#include <string>

class Reader {
public:
    std::list<std::string> readFromFile(const std::string& filename);
};

#endif
