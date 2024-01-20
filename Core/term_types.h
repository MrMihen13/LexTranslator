#pragma once

#include "term_type.h"

namespace TermTypes {
    static const TermType UNDEFINED(0, "Неопределено");
    static const TermType IDENTIFIER(1, "Идентификатор");;
    static const TermType NUMBER(2, "Числовой литерал");
    static const TermType ASSIGNMENT(3, "Оператор присваивания");
    static const TermType OPEN_BRACKET(4, "Открывающая скобка");
    static const TermType CLOSE_BRACKET(5, "Закрывающая скобка");
    static const TermType PLUS(6, "Оператор \"+\"");
    static const TermType SEMICOLON(7, "Точка с запятой");
    static const TermType COMMENT(8, "Комментарий");
    static const TermType KEYWORD(9, "Ключевое слово");
    static const TermType MINUS(10, "Оператор \"-\"");
    static const TermType MULTIPLY(11, "Оператор \"*\"");
    static const TermType DIVIDE(12, "Оператор \"/\"");
    static const TermType OR(13, "Оператор OR");
    static const TermType XOR(14, "Оператор XOR");
    static const TermType AND(15, "Оператор AND");
    static const TermType NOT(16, "Оператор NOT");
    static const TermType IF(17, "Оператор IF");
    static const TermType THEN(18, "Оператор THEN");
    static const TermType ELSE(19, "Оператор ELSE");
    static const TermType LIMIT(20, "Конец строки");
    static const TermType FOR(21, "Оператор FOR");
    static const TermType DO(22, "Оператор DO");
    static const TermType LESS(23, "Оператор <");
    static const TermType GREATER(24, "Оператор >");
    static const TermType EQUAL(25, "Оператор =");
    static const TermType TRUE(26, "ИСТИНА");
    static const TermType FALSE(27, "ЛОЖЬ");
    static const TermType COMMA(28, "ЗАПЯТАЯ");
    static const TermType INC(29, "оператор ++");
    static const TermType DEC(30, "оператор --");
}
