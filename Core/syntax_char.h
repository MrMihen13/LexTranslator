#pragma once

#include <string>
#include <ostream>

#include "token_types.h"

struct SyntaxChar {
    SyntaxChar() {}

    SyntaxChar(int code, std::string tokenString, TokenType type)
        : code(code)
        , tokenString(tokenString)
        , type(type)
    { }

    int code;
    std::string tokenString;
    TokenType type;

    bool operator ==(const SyntaxChar& token) const {
        return this->code == token.code;
    }

    friend std::ostream& operator<<(std::ostream& s, const SyntaxChar& token)
    {
        s << "code: " << token.code << " symbol: " << token.tokenString.c_str() << " type: " << (int)(token.type);
        return s;
    }
};
