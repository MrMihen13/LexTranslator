#pragma once

#include "funcs.h"
#include "syntax_char.h"
#include "syntax_chars.h"

#include <vector>
#include <string>
#include <algorithm>

class BuildRule {
private:
    std::vector<SyntaxChar> EXCLUDE_SYMBOLS = {
        SyntaxChars::OPEN_BRACKET,
        SyntaxChars::CLOSE_BRACKET,
        SyntaxChars::SEMICOLON
    };

    std::vector<std::string> getTokenSymbols(std::vector<SyntaxChar> items) {
        std::vector<std::string> symbols;
        for (auto& token : items) {
            symbols.push_back(token.tokenString);
        }
        return symbols;
    }

    std::vector<SyntaxChar> getSimpleRule(std::vector<SyntaxChar> items) {
        std::vector<SyntaxChar> filteredItems;
        std::copy_if(items.begin(), items.end(), std::back_inserter(filteredItems), [&](SyntaxChar item) {
            return std::find(EXCLUDE_SYMBOLS.begin(), EXCLUDE_SYMBOLS.end(), item) != EXCLUDE_SYMBOLS.end();
            });
        return filteredItems;
    }

    std::vector<SyntaxChar> _getTerminalItems(std::vector<SyntaxChar> items) {
        std::vector<SyntaxChar> filteredItems;
        std::copy_if(items.begin(), items.end(), std::back_inserter(filteredItems), [&](SyntaxChar item) {
            return item.type == TokenType::TERMINAL;
            });
        return filteredItems;
    }

    std::vector<SyntaxChar> _getNonterminalItems(std::vector<SyntaxChar> items) {
        std::vector<SyntaxChar> filteredItems;
        std::copy_if(items.begin(), items.end(), std::back_inserter(filteredItems), [&](SyntaxChar item) {
            return item.type == TokenType::NONTERMINAL;
            });
        return filteredItems;
    }

public:
    std::vector<SyntaxChar> items;
    std::string ruleString;

    BuildRule() { }

    BuildRule(std::vector<SyntaxChar> items)
        : items(items)
        , ruleString(Funcs::join(getTokenSymbols(items)))
    {};

    std::string getRuleString() {
        return Funcs::join(getTokenSymbols(getSimpleRule(items)));
    }

    std::string getTerminalsString() {
        return Funcs::join(getTokenSymbols(_getTerminalItems(items)));
    }

    std::vector<SyntaxChar> getNonTerminalItems() {
        return _getNonterminalItems(items);
    }

    std::vector<SyntaxChar> getTerminalItems() {
        return _getTerminalItems(items);
    };

    friend std::ostream& operator<<(std::ostream& s, const BuildRule& buildRule) {
        s << buildRule.ruleString << std::endl;
        return s;
    }
};
