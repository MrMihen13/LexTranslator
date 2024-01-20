#pragma once

#include "enum_struct.h"

#include <string>

struct GrammarCharType : EnumStruct {
public:
    GrammarCharType(const int code, const std::string string)
        : EnumStruct(code, string)
    { }

    GrammarCharType(const GrammarCharType& grammarCharType)
        : GrammarCharType(grammarCharType._code, grammarCharType._string)
    { }

    int code() const {
        return _code;
    }
};

namespace GrammarCharTypes {
    static const GrammarCharType TERMINAL(0, "Терминальный символ");
    static const GrammarCharType NONTERMINAL(1, "Нетерминальный символ");
}