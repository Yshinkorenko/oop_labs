#include <iostream>
#include "Reader.h"
#include "WordCounter.h"
#include "CSVWriter.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input.txt> <output.csv>" << std::endl;
        return 1;
    }


    try {
        Reader reader;
        auto lines = reader.readFromFile(argv[1]);

        WordCounter wordCounter;
        wordCounter.countWords(lines);

        auto sortedWords = wordCounter.getSortedWords();
        int totalWords = wordCounter.getTotalWords();

        CSVWriter::writeToFile(argv[2], sortedWords, totalWords);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
