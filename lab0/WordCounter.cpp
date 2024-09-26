#include "WordCounter.h"
#include <fstream>
#include <vector>

bool WordCounter::isDelimiter(char c) {
    return !std::isalnum(c);
}

std::list<std::string> WordCounter::splitIntoWords(const std::string& line) {
    std::list<std::string> words;
    std::string word;
    for (char c : line) {
        if (isDelimiter(c)) {
            if (!word.empty()) {
                words.push_back(word);
                word.clear();
            }
        } else {
            word += std::tolower(c);
        }
    }
    if (!word.empty()) {
        words.push_back(word);
    }
    return words;
}

void WordCounter::countWordsFromFile(const std::string& filename) {
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        throw std::runtime_error("Error: Could not open input file.");
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        std::list<std::string> words = splitIntoWords(line);
        for (const std::string& word : words) {
            wordCount[word]++;
            totalWords++;
        }
    }

    inputFile.close();
}

std::vector<std::pair<std::string, int>> WordCounter::getSortedWord() const {
    std::vector<std::pair<std::string, int>> sortedWords(wordCount.begin(), wordCount.end());
    std::sort(sortedWords.begin(), sortedWords.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });
    return sortedWords;
}

int WordCounter::getTotalWords() const {
    return totalWords;
}
