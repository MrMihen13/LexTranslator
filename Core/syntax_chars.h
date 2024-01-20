#pragma once

#include "syntax_char.h"

// TODO: не понятно, это часть конфигурации или глобальный набор значений
// коды - индексы столбцов, т.е. часть конфигурации?
namespace SyntaxChars {
    const SyntaxChar FOR(0, "for ", TokenType::TERMINAL);
    const SyntaxChar DO(1, " do ", TokenType::TERMINAL);
    const SyntaxChar OPEN_BRACKET(2, "(", TokenType::TERMINAL);
    const SyntaxChar CLOSE_BRACKET(3, ")", TokenType::TERMINAL);
    const SyntaxChar LESS(4, "<", TokenType::TERMINAL);
    const SyntaxChar GREATER(5, ">", TokenType::TERMINAL);
    const SyntaxChar EQUAL(6, "=", TokenType::TERMINAL);
    const SyntaxChar ASSIGNMENT(7, ":=", TokenType::TERMINAL);
    const SyntaxChar IDENTIFIER(8, "I", TokenType::TERMINAL);
    const SyntaxChar NONTERMINAL(9, "S", TokenType::NONTERMINAL);
    const SyntaxChar SEMICOLON(10, ";", TokenType::TERMINAL);
    const SyntaxChar INC(11, "++", TokenType::TERMINAL);
    const SyntaxChar DEC(12, "--", TokenType::TERMINAL);
    const SyntaxChar LIMIT(13, "#", TokenType::TERMINAL);
}

