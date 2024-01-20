#pragma once
#include "syntax_char.h"
#include "token.h"

struct RefValue {
    SyntaxChar* syntaxChar;
    Token* value;

    RefValue(SyntaxChar* syntaxChar = nullptr, Token* value = nullptr)
        : syntaxChar(syntaxChar)
        , value(value)
    { }
};