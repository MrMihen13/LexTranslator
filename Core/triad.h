#pragma once

#include <sstream>
#include <vector>
#include "ref_value.h"
#include "syntax_char.h"
#include "roman.h"
#include <iomanip>

struct Triad {
    int id = 0;
    int dep = 0;

    Triad* same = nullptr;

    SyntaxChar* op = nullptr;

    std::vector<Triad*> operands;

    RefValue* value = nullptr;

    Triad(int id) : id(id) {
        for (int i = 0; i < 2; ++i) {
            operands.push_back(nullptr);
        }
    }

    Triad(int id, SyntaxChar* op)
        : Triad(id)
    {
        this->op = op;
    }

    Triad(int id, RefValue* value)
        : Triad(id)
    {
        this->op = nullptr;
        this->value = value;
    }

   
    Triad* tryGetSame() {
        Triad* current = this;
        
        while (current->same != nullptr) {
            current = same;
        }

        return current;
    }

    std::string toString() const {
        std::stringstream ss;

        if (isValue()) {
            std::cerr << "Is not valid triad. Contains only variable value.";
            exit(-2);
        }

        ss << std::setw(3) << op->tokenString << " ( " << toString(this, 0) << ", " << toString(this, 1) << " );";

        return ss.str();
    }

    bool isValue() const {
        return value != nullptr;
    }

    bool isOperation() const {
        return op != nullptr;
    }

    bool isOperandsNumbersOrVars() {
        int getTriadValue = 0;

        for (Triad* triad : operands) {
            if (triad != nullptr && triad->isValue() && *triad->value->syntaxChar == SyntaxChars::IDENTIFIER) {
                getTriadValue += 1;
            }
        }

        return getTriadValue == 2;
    }

    Token* getToken() const {
        return this->value->value;
    }

    TermType getTokenType() const {
        return this->value->value->type;
    }

    std::string getTokenValue() const {
        return this->value->value->value;
    }

private:

    static std::string toString(const Triad* triad, int index) {
        std::stringstream ss;

        if (triad->operands.at(index) != nullptr && !triad->operands.at(index)->isValue()) {
            ss << "^" << triad->operands.at(index)->id % 1000;
        }
        else if (triad->operands.at(index) != nullptr && triad->operands.at(index)->isValue()) {
            ss << triad->operands.at(index)->value->value->value;
        }
        
        return ss.str();
    }
};