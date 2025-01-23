#ifndef I_RULE_H
#define I_RULE_H

#include <string>

class IRule {
public:
    virtual ~IRule() = default;
    
    virtual bool shouldBirth(int neighbors) const = 0;
    virtual bool shouldSurvive(int neighbors) const = 0;

    virtual std::string toString() const = 0;
    
    virtual void parseRule(const std::string& ruleStr) = 0;
};

#endif 
