#pragma once

#include <vector>
#include <sstream>
#include <list>
#include <functional>

#include "token.h"

struct Command {
    bool isValid = true;

    std::vector<Token> tokens;
    std::list<Token> values;

    std::string toString(int lt = 0) {
        std::stringstream ss;

        for (int i = 0; i < tokens.size() - lt; ++i) {
            ss << tokens[i].value;
        }

        return ss.str();
    }

    std::list<Token> getValueTokens() {
        return values;
    }
};