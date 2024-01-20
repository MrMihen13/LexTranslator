#pragma once

#include "enum_struct.h"

#include <string>

struct TermType : EnumStruct {
public:
    TermType(const int code, const std::string string)
        : EnumStruct(code, string)
    { }

    int code() const {
        return _code;
    }

    operator std::string() const {
        return toString();
    }

    TermType operator=(TermType& a) {
        return a;
    }
};
