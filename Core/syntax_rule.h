#pragma once

#include "build_rule.h"
#include <ostream>

struct SyntaxRule {
    SyntaxRule()
        : SyntaxRule(-1, BuildRule())
    { };

    SyntaxRule(int code, BuildRule buildRule)
        : code(code)
        , buildRule(buildRule)
    { }

    friend std::ostream& operator<<(std::ostream& s, const SyntaxRule& syntaxRule)
    {
        s << "rule: " << syntaxRule.buildRule;
        return s;
    }

    BuildRule buildRule;
    int code;
};
