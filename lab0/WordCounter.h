#ifndef WORDCOUNTER_H
#define WORDCOUNTER_H

#include <string>
#include <map>
#include <list>
#include <vector>

class WordCounter {
private:
    std::map<std::string, int> wordCount;
    int totalWords{0};
    bool isDelimiter(char c);
    std::list<std::string> splitIntoWords(const std::string& line);
public:
    void countWordsFromFile(const std::string& filename);
    std::vector<std::pair<std::string, int>> getSortedWord() const;
    int getTotalWords() const;
};

#endif
