#pragma once
#include "triad.h"
#include "syntax_chars.h"

struct TriadH {
    static bool isIdentifier(Triad* triad) {
        return (!triad->isOperation() &&
            triad->getTokenType() == TermTypes::IDENTIFIER);
    }

    static bool isSameTokens(Triad* triad1, Triad* triad2) {
        return triad1->getTokenType() == triad2->getTokenType() &&
            triad1->getTokenValue() == triad2->getTokenValue();
    }

    static bool isSameValues(Triad* a, Triad* b, bool isDepEqual) {
        if (a->isValue() && b->isValue() && TriadH::isSameTokens(a, b)) {
            if (a->getTokenType() == TermTypes::IDENTIFIER) {
                return isDepEqual;
            }
            else {
                return true;
            }
        }
        return false;
    }

    static bool isSame(Triad* a, Triad* b) {
        bool isSame = false, isSame0 = false, isSame1 = false;

        isSame0 = isSameValues(a->operands.at(0), b->operands.at(0), a->dep == b->dep);
        isSame1 = isSameValues(a->operands.at(1), b->operands.at(1), a->dep == b->dep);

        /*if ((*a->op == SyntaxChars::PLUS || *a->op == SyntaxChars::MULTIPLY) &&
            (!isSame0 && !isSame1)) {

            isSame0 = isSameValues(a->operands.at(0), b->operands.at(1), a->dep == b->dep);
            isSame1 = isSameValues(a->operands.at(1), b->operands.at(0), a->dep == b->dep);
        }*/

        return isSame0 && isSame1;
    }
};