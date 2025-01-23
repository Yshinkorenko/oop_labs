#include "Game.h"
#include "ToroidalUniverse.h"
#include "LifeLikeRule.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>  
#include <ctime>

Game::Game()
    : universe(nullptr), rule(nullptr),
      universeName("Unnamed universe"),
      iteration(0), exitFlag(false)
{
}

void Game::setUniverse(std::unique_ptr<BaseUniverse> u) {
    universe = std::move(u);
}
void Game::setRule(std::unique_ptr<IRule> r) {
    rule = std::move(r);
}

void Game::setUniverseName(const std::string& name) {
    universeName = name;
}

std::string Game::getUniverseName() const {
    return universeName;
}

int Game::getIteration() const {
    return iteration;
}
void Game::step() {
    if (!universe || !rule) {
        std::cerr << "Error: Universe or Rule not set.\n";
        return;
    }
    std::unique_ptr<BaseUniverse> newUniverse(
        new ToroidalUniverse(universe->getWidth(), universe->getHeight()));

    for (int y = 0; y < universe->getHeight(); ++y) {
        for (int x = 0; x < universe->getWidth(); ++x) {
            int n = universe->countNeighbors(x, y);
            bool alive = universe->isAlive(x, y);

            if (alive) {
                
                if (rule->shouldSurvive(n)) {
                    newUniverse->setAlive(x, y);
                } else {
                    newUniverse->setDead(x, y);
                }
            } else {
                
                if (rule->shouldBirth(n)) {
                    newUniverse->setAlive(x, y);
                } else {
                    newUniverse->setDead(x, y);
                }
            }
        }
    }
    universe = std::move(newUniverse);
    iteration++;
}

void Game::step(int n) {
    for (int i = 0; i < n; i++) {
        step();
    }
}

void Game::printUniverse() const {
    if (!universe) {
        std::cerr << "No universe to print.\n";
        return;
    }
    std::cout << "Universe name: " << universeName << "\n";
    if (rule) {
        std::cout << "Rule: " << rule->toString() << "\n";
    } else {
        std::cout << "Rule: (none)\n";
    }
    std::cout << "Iteration: " << iteration << "\n";
    universe->print(std::cout);
}

bool Game::loadFromFile(const std::string& filename) {
    std::ifstream fin(filename);
    if (!fin.is_open()) {
        std::cerr << "Error: cannot open file " << filename << std::endl;
        return false;
    }

    std::string line;
    bool hasLifeLine = false;
    bool hasName = false;
    bool hasRule = false;

    std::vector<std::pair<int,int>> aliveCells;
    int minX=0, maxX=0;
    int minY=0, maxY=0;
    bool firstCoord = true;

    int lineNumber = 0;
    while (std::getline(fin, line)) {
        lineNumber++;
        if (lineNumber == 1) {
            if (line != "Life 1.06") {
                std::cerr << "Warning: first line is not 'Life 1.06'.\n";
            } else {
                hasLifeLine = true;
            }
            continue;
        }

        if (!line.empty() && line[0] == '#') {
            if (line.size() > 1 && line[1] == 'N') {
                hasName = true;
                if (line.size() > 3) {
                    universeName = line.substr(3);
                } else {
                    universeName = "Unnamed universe";
                }
            } else if (line.size() > 1 && line[1] == 'R') {
                hasRule = true;

                if (line.size() > 3) {
                    std::string r = line.substr(3);
                    auto lifeRule = std::make_unique<LifeLikeRule>();
                    lifeRule->parseRule(r);
                    setRule(std::move(lifeRule));
                } else {
                    auto lifeRule = std::make_unique<LifeLikeRule>("B3/S23");
                    setRule(std::move(lifeRule));
                }
            }
            continue;
        }

        if (!line.empty()) {
            std::istringstream iss(line);
            int x, y;
            if (!(iss >> x >> y)) {
                std::cerr << "Warning: invalid coordinate format in line "
                          << lineNumber << ": " << line << std::endl;
                continue;
            }
            aliveCells.push_back({x, y});
            if (firstCoord) {
                minX = maxX = x;
                minY = maxY = y;
                firstCoord = false;
            } else {
                if (x < minX) minX = x;
                if (x > maxX) maxX = x;
                if (y < minY) minY = y;
                if (y > maxY) maxY = y;
            }
        }
    }

    if (!hasRule) {
        std::cerr << "Warning: no rule found. Using default B3/S23.\n";
        auto defaultRule = std::make_unique<LifeLikeRule>("B3/S23");
        setRule(std::move(defaultRule));
    }
    if (!hasName) {
        std::cerr << "Warning: no universe name found. Using default name.\n";
        universeName = "Unnamed universe";
    }

    int w = maxX - minX + 1;
    int h = maxY - minY + 1;
    if (w <= 0) w = 1;
    if (h <= 0) h = 1;

    auto newUni = std::make_unique<ToroidalUniverse>(w, h);
    
    for (auto& cell : aliveCells) {
        int x = cell.first - minX;
        int y = cell.second - minY;
        if (x < 0 || x >= w || y < 0 || y >= h) {
            std::cerr << "Warning: cell out of range after shift.\n";
            continue;
        }
        newUni->setAlive(x, y);
    }

    setUniverse(std::move(newUni));
    iteration = 0;
    return true;
}

bool Game::saveToFile(const std::string& filename) const {
    if (!universe || !rule) {
        std::cerr << "No universe or rule to save.\n";
        return false;
    }
    std::ofstream fout(filename);
    if (!fout.is_open()) {
        std::cerr << "Error: cannot open file " << filename << " for writing.\n";
        return false;
    }
    fout << "Life 1.06\n";
    fout << "#N " << universeName << "\n";
    fout << "#R " << rule->toString() << "\n";

    for (int y = 0; y < universe->getHeight(); ++y) {
        for (int x = 0; x < universe->getWidth(); ++x) {
            if (universe->isAlive(x, y)) {
                fout << x << " " << y << "\n";
            }
        }
    }
    return true;
}

// Интерактивный режим
void Game::runInteractive() {
    exitFlag = false;
    std::cout << "Type 'help' for available commands.\n";
    while (!exitFlag) {
        std::cout << "> ";
        std::string cmdLine;
        if (!std::getline(std::cin, cmdLine)) {
            break;
        }
        processCommand(cmdLine);
    }
}

void Game::processCommand(const std::string& commandLine) {
    std::istringstream iss(commandLine);
    std::string cmd;
    iss >> cmd;
    if (cmd.empty()) return;

    if (cmd == "help") {
        printHelp();
    }
    else if (cmd == "exit") {
        exitFlag = true;
    }
    else if (cmd == "dump") {
        std::string fname;
        iss >> fname;
        if (fname.empty()) {
            std::cerr << "Usage: dump <filename>\n";
        } else {
            saveToFile(fname);
            std::cout << "Universe dumped to " << fname << "\n";
        }
    }
    else if (cmd == "tick" || cmd == "t") {
        int n = 1;
        if (!(iss >> n)) {
            n = 1;
        }
        step(n);
        printUniverse();
    }
    else {
        std::cerr << "Unknown command: " << cmd << "\n";
        printHelp();
    }
}

void Game::printHelp() const {
    std::cout << "Available commands:\n"
              << "  help                - show this help\n"
              << "  exit                - exit the game\n"
              << "  dump <filename>     - save universe to file\n"
              << "  tick <n=1> or t <n=1> - calculate n iterations (default 1) and print\n";
}
