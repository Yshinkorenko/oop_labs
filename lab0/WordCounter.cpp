#include "WordCounter.h"
#include <cctype>
#include <algorithm>

bool WordCounter::isDelimiter(char c) {
    return !std::isalnum(static_cast<unsigned char>(c));
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
            word += static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
        }
    }

    if (!word.empty()) {
        words.push_back(word);
    }

    return words;
}

void WordCounter::countWords(const std::list<std::string>& lines) {
    for (const auto& line : lines) {
        auto words = splitIntoWords(line);
        for (const auto& word : words) {
            wordCount[word]++;
            totalWords++;
        }
    }
}

std::vector<std::pair<std::string, int>> WordCounter::getSortedWords() const {
    std::vector<std::pair<std::string, int>> sortedWords(wordCount.begin(), wordCount.end());
    std::sort(sortedWords.begin(), sortedWords.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });
    return sortedWords;
}

int WordCounter::getTotalWords() const {
    return totalWords;
}
