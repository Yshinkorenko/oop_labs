#include <iostream>
#include <string>
#include <ctime>
#include <memory>
#include <cstdlib>  
#include "Game.h"
#include "ToroidalUniverse.h"
#include "LifeLikeRule.h"

struct Args {
    bool offlineMode = false;
    std::string inputFile;
    std::string outputFile;
    int iterations = 0;
};

Args parseArgs(int argc, char* argv[]) {
    Args args;
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-i" || arg == "--iterations") {
            if (i+1 < argc) {
                args.iterations = std::atoi(argv[++i]);
                args.offlineMode = true;
            }
        }
        else if (arg.rfind("--iterations=", 0) == 0) {
            auto val = arg.substr(13);
            args.iterations = std::atoi(val.c_str());
            args.offlineMode = true;
        }
        else if (arg == "-o" || arg == "--output") {
            if (i+1 < argc) {
                args.outputFile = argv[++i];
                args.offlineMode = true;
            }
        }
        else if (arg.rfind("--output=", 0) == 0) {
            auto val = arg.substr(9);
            args.outputFile = val;
            args.offlineMode = true;
        }
        else {
            args.inputFile = arg;
        }
    }
    return args;
}

int main(int argc, char* argv[]) {
    std::srand((unsigned)std::time(nullptr));

    Args args = parseArgs(argc, argv);

    Game game;


    if (!args.inputFile.empty()) {
        if (!game.loadFromFile(args.inputFile)) {
            std::cerr << "Error: cannot load file: " << args.inputFile << "\n";
            return 1;
        }
    } else {
        
        std::unique_ptr<BaseUniverse> uni(new ToroidalUniverse(5, 5));
        std::unique_ptr<IRule> rule(new LifeLikeRule("B3/S23"));

    
        uni->setAlive(4, 4);
        uni->setAlive(3, 3);
        uni->setAlive(2, 2);
        uni->setAlive(1, 1);
        uni->setAlive(0, 0);

        game.setUniverse(std::move(uni));
        game.setRule(std::move(rule));
        game.setUniverseName("Default universe");
        std::cout << "No input file provided. Using default 10x10 with a 'blinker' pattern.\n";
    }

  
    if (args.offlineMode && args.iterations > 0) {
        game.step(args.iterations);

        if (!args.outputFile.empty()) {
            if (!game.saveToFile(args.outputFile)) {
                std::cerr << "Error: cannot save to " << args.outputFile << "\n";
                return 1;
            }
        }
        return 0;
    }


    game.printUniverse();
    game.runInteractive();
    
    return 0;
}
