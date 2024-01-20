#pragma once

#include "term_type.h"
#include "term_types.h"

#include <string>
#include <iostream>

struct Token {
    Token(std::string value, TermType type) 
        : value(value)
        , type(type)
    { }

    std::string value = "";
    TermType type = TermTypes::UNDEFINED;

    friend bool operator==(const Token& t1, const Token& t2) {
        return t1.value == t2.value &&
            t1.type == t2.type;
    }

    friend bool operator!=(const Token& t1, const Token& t2) {
        return !(t1 == t2);
    }

    friend std::ostream& operator<<(std::ostream& s, const Token& token)
    {
        s << "code: " << token.type.code() << " typeName: " << token.type.toString() << " value: " << token.value;
        return s;
    }
};
