#include "LifeLikeRule.h"
#include <sstream>
#include <iostream>
#include <cctype>

LifeLikeRule::LifeLikeRule() {
    parseRule("B3/S23");
}

LifeLikeRule::LifeLikeRule(const std::string& ruleStr) {
    parseRule(ruleStr);
}

bool LifeLikeRule::shouldBirth(int neighbors) const {
    return (birthSet.find(neighbors) != birthSet.end());
}


bool LifeLikeRule::shouldSurvive(int neighbors) const {
    return (survivalSet.find(neighbors) != survivalSet.end());
}

void LifeLikeRule::parseRule(const std::string& ruleStr) {
    parseString(ruleStr);
}

std::string LifeLikeRule::toString() const {
    std::ostringstream ossB, ossS;
    ossB << "B";
    for (int b : birthSet) {
        ossB << b;
    }
    ossS << "/S";
    for (int s : survivalSet) {
        ossS << s;
    }
    return ossB.str() + ossS.str();
}

void LifeLikeRule::parseString(const std::string& ruleStr) {
    birthSet.clear();
    survivalSet.clear();

    auto slashPos = ruleStr.find('/');
    if (slashPos == std::string::npos) {
        std::cerr << "Warning: Invalid rule format \"" << ruleStr 
                  << "\". Using default B3/S23.\n";
        parseString("B3/S23");
        return;
    }
    std::string left = ruleStr.substr(0, slashPos);   
    std::string right = ruleStr.substr(slashPos + 1); 

    if (left.size() < 2 || left[0] != 'B' ||
        right.empty() || right[0] != 'S')
    {
        std::cerr << "Warning: Invalid rule format \"" << ruleStr 
                  << "\". Using default B3/S23.\n";
        parseString("B3/S23");
        return;
    }

    std::string births = left.substr(1);
    for (char c : births) {
        if (std::isdigit(c)) {
            birthSet.insert(c - '0');
        }
    }

    std::string survs = right.substr(1);
    for (char c : survs) {
        if (std::isdigit(c)) {
            survivalSet.insert(c - '0');
        }
    }
}
