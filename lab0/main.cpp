#include <iostream>
#include "WordCounter.h"
#include "CSVWriter.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Write: " << argv[0] << " in.txt out.csv" << std::endl;
        return 1;
    }

    WordCounter wordCounter;
    WordCounter wordCounter2 = new WordCounter;
    wordCounter.countWordsFromFile(argv[1]);

    std::vector<std::pair<std::string, int>> sortedWords = wordCounter.getSortedWord();
    int totalWords = wordCounter.getTotalWords();

    CSVWriter::writeToFile(argv[2], sortedWords, totalWords);

    return 0;
}
