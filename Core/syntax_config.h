#pragma once

#include "relations.h"

#include <stdexcept>

class SyntaxConfig {
public:
    SyntaxConfig(
        const std::vector<std::vector<Relations>> matrix, 
        const std::map<TermType, SyntaxChar> termTypeToSyntaxChar, 
        std::vector<SyntaxRule> rules, 
        const std::vector<std::vector<StatusCode>> errors)   
        : matrix(matrix)
        , termTypeToSyntaxChar(termTypeToSyntaxChar)
        , errors(errors)
    {
        if (matrix.size() != matrix.at(0).size()) {
            throw std::invalid_argument("SyntaxConfig `matrix` is not relation matrix.");
        }

        for (SyntaxRule rule : rules) {
            stringRuleMap.insert({ rule.buildRule.ruleString, rule });
        }
    }

    Relations getRelation(int leftTermIndex, int rightTermIndex) const {
        if (leftTermIndex >= matrix.size() || rightTermIndex >= matrix.size())
            throw std::exception("Relation matrix out of range");

        return matrix.at(leftTermIndex).at(rightTermIndex);
    }

    StatusCode getStatusCode(int leftTermIndex, int rightTermIndex) {
        if (leftTermIndex >= errors.size() || rightTermIndex >= errors.size())
            throw std::exception("Relation matrix out of range");

        return errors.at(leftTermIndex).at(rightTermIndex);
    }
    
    SyntaxChar getSyntaxChar(TermType tokenType) const {
        return termTypeToSyntaxChar.at(tokenType);
    }

    int getIndex(TermType tokenType) const {
        return termTypeToSyntaxChar.at(tokenType).code;
    }

    SyntaxRule getRuleByString(std::string ruleString) {
        return stringRuleMap.at(ruleString);
    }

private:
    const std::vector<std::vector<Relations>> matrix;
    const std::vector<std::vector<StatusCode>> errors;
    const std::map<TermType, SyntaxChar> termTypeToSyntaxChar;

    std::map<std::string, SyntaxRule> stringRuleMap;
};