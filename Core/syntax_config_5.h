#pragma once

#include "syntax_chars.h"
#include "syntax_rule.h"
#include "operators_matrices.h"
#include "syntax_config.h"
#include "term_types.h"

#include <map>

const std::map<TermType, SyntaxChar> TERM_TYPE_TO_MATRIX_INDEX = {
    { TermTypes::FOR, SyntaxChars::FOR },
    { TermTypes::DO, SyntaxChars::DO },
    { TermTypes::OPEN_BRACKET, SyntaxChars::OPEN_BRACKET },
    { TermTypes::CLOSE_BRACKET, SyntaxChars::CLOSE_BRACKET },
    { TermTypes::LESS, SyntaxChars::LESS },
    { TermTypes::GREATER, SyntaxChars::GREATER },
    { TermTypes::EQUAL, SyntaxChars::EQUAL },
    { TermTypes::ASSIGNMENT, SyntaxChars::ASSIGNMENT },
    { TermTypes::IDENTIFIER, SyntaxChars::IDENTIFIER },
    { TermTypes::NUMBER, SyntaxChars::IDENTIFIER },
    { TermTypes::SEMICOLON, SyntaxChars::SEMICOLON },
    { TermTypes::INC, SyntaxChars::INC },
    { TermTypes::DEC, SyntaxChars::DEC },
    { TermTypes::LIMIT, SyntaxChars::LIMIT },
};

namespace SyntaxRules {
    const SyntaxRule R1 = SyntaxRule(1, BuildRule({ SyntaxChars::NONTERMINAL, SyntaxChars::SEMICOLON }));
    const SyntaxRule R2 = SyntaxRule(2, BuildRule({ SyntaxChars::FOR, SyntaxChars::OPEN_BRACKET, SyntaxChars::NONTERMINAL, SyntaxChars::CLOSE_BRACKET, SyntaxChars::DO, SyntaxChars::NONTERMINAL }));
    const SyntaxRule R3 = SyntaxRule(3, BuildRule({ SyntaxChars::NONTERMINAL, SyntaxChars::SEMICOLON, SyntaxChars::NONTERMINAL, SyntaxChars::SEMICOLON, SyntaxChars::NONTERMINAL }));
    const SyntaxRule R4 = SyntaxRule(4, BuildRule({ SyntaxChars::SEMICOLON, SyntaxChars::NONTERMINAL, SyntaxChars::SEMICOLON, SyntaxChars::NONTERMINAL }));
    const SyntaxRule R5 = SyntaxRule(5, BuildRule({ SyntaxChars::NONTERMINAL, SyntaxChars::SEMICOLON, SyntaxChars::NONTERMINAL, SyntaxChars::SEMICOLON }));
    const SyntaxRule R6 = SyntaxRule(6, BuildRule({ SyntaxChars::SEMICOLON, SyntaxChars::NONTERMINAL, SyntaxChars::SEMICOLON }));
    const SyntaxRule R7 = SyntaxRule(7, BuildRule({ SyntaxChars::IDENTIFIER, SyntaxChars::ASSIGNMENT, SyntaxChars::NONTERMINAL }));
    const SyntaxRule R8 = SyntaxRule(7, BuildRule({ SyntaxChars::IDENTIFIER, SyntaxChars::ASSIGNMENT, SyntaxChars::IDENTIFIER }));
    const SyntaxRule R9 = SyntaxRule(8, BuildRule({ SyntaxChars::NONTERMINAL, SyntaxChars::LESS, SyntaxChars::NONTERMINAL }));
    const SyntaxRule R10 = SyntaxRule(9, BuildRule({ SyntaxChars::NONTERMINAL, SyntaxChars::GREATER, SyntaxChars::NONTERMINAL }));
    const SyntaxRule R11 = SyntaxRule(10, BuildRule({ SyntaxChars::NONTERMINAL, SyntaxChars::EQUAL, SyntaxChars::NONTERMINAL }));
    const SyntaxRule R12 = SyntaxRule(11, BuildRule({ SyntaxChars::IDENTIFIER }));
    const SyntaxRule R13 = SyntaxRule(12, BuildRule({ SyntaxChars::IDENTIFIER, SyntaxChars::INC }));
    const SyntaxRule R14 = SyntaxRule(13, BuildRule({ SyntaxChars::IDENTIFIER, SyntaxChars::DEC }));
}

const std::vector<SyntaxRule> RULES = {
    SyntaxRules::R1,
    SyntaxRules::R2,
    SyntaxRules::R3,
    SyntaxRules::R4,
    SyntaxRules::R5,
    SyntaxRules::R6,
    SyntaxRules::R7,
    SyntaxRules::R8,
    SyntaxRules::R9,
    SyntaxRules::R10,
    SyntaxRules::R11,
    SyntaxRules::R12,
    SyntaxRules::R13,
    SyntaxRules::R14
};

SyntaxConfig MathGrammarConfig(MATRIX_1, TERM_TYPE_TO_MATRIX_INDEX, RULES, MATRIX_1_ERRORS);