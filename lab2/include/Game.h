#ifndef GAME_H
#define GAME_H

#include <string>
#include <memory>   
#include "BaseUniverse.h"
#include "IRule.h"

class Game {
private:
    std::unique_ptr<BaseUniverse> universe;  
    std::unique_ptr<IRule> rule;           
    std::string universeName;
    int iteration;
    bool exitFlag;

public:
    Game();
    ~Game() = default;

    void setUniverse(std::unique_ptr<BaseUniverse> u);
    void setRule(std::unique_ptr<IRule> r);

    void setUniverseName(const std::string& name);
    std::string getUniverseName() const;

    int getIteration() const;

    void step();
    void step(int n);

    void printUniverse() const;

    bool loadFromFile(const std::string& filename);
    bool saveToFile(const std::string& filename) const;

    void runInteractive();
    void processCommand(const std::string& commandLine);

private:
    void printHelp() const;
};

#endif 
