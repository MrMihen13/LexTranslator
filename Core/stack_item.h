#pragma once

#include "term_types.h"
#include "syntax_chars.h"

#include <string>

struct StackItem {
    StackItem(int code, std::string value, SyntaxChar currentChar)
        : code(code)
        , value(value)
        , currentChar(currentChar)
    { }

    int code;
    SyntaxChar currentChar;

    std::string value;

    bool isNotTerm() {
        return code == SyntaxChars::NONTERMINAL.code;
    }
};

StackItem START_LIMIT = StackItem(SyntaxChars::LIMIT.code, "Í", SyntaxChars::LIMIT);
StackItem NONTERM = StackItem(SyntaxChars::NONTERMINAL.code, SyntaxChars::NONTERMINAL.tokenString, SyntaxChars::NONTERMINAL);
