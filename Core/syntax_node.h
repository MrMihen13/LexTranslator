#pragma once

#include "syntax_rule.h"

struct SyntaxNode {
    // TODO: Если заменить "SyntaxRule syntaxRule" на "const SyntaxRule& syntaxRule" падает bad_alloc
    SyntaxNode(SyntaxRule syntaxRule)
        : syntaxRule(syntaxRule)
    { };

    SyntaxRule syntaxRule;

    friend std::ostream& operator<<(std::ostream& s, const SyntaxNode& node)
    {
        s << "[rule]: " << node.syntaxRule << std::endl;
        return s;
    }
};
