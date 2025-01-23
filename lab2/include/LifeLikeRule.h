#ifndef LIFE_LIKE_RULE_H
#define LIFE_LIKE_RULE_H

#include "IRule.h"
#include <set>
#include <string>

class LifeLikeRule : public IRule {
private:
    std::set<int> birthSet;
    std::set<int> survivalSet;

public:
    LifeLikeRule();
    LifeLikeRule(const std::string& ruleStr);

    bool shouldBirth(int neighbors) const override;
    bool shouldSurvive(int neighbors) const override;
    
    void parseRule(const std::string& ruleStr) override;
    std::string toString() const override;

private:
    void parseString(const std::string& ruleStr);
};

#endif
