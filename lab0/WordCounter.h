#ifndef WORDCOUNTER_H
#define WORDCOUNTER_H

#include <map>
#include <list>
#include <vector>
#include <string>

class WordCounter {
private:
    std::map<std::string, int> wordCount;
    int totalWords{0};
    bool isDelimiter(char c);
    std::list<std::string> splitIntoWords(const std::string& line);

public:
    void countWords(const std::list<std::string>& lines);
    std::vector<std::pair<std::string, int>> getSortedWords() const;
    int getTotalWords() const;
};

#endif
