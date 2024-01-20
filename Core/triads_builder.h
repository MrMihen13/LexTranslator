#pragma once
#include "ref_tree.h"
#include "syntax_chars.h"
#include "triad.h"
#include <list>
#include "table_of_constants.h"
#include "table_of_vars.h"
#include "triad_math.h"
#include <algorithm>

struct TriadBuilderV2 {
    int gen = 1;
    std::list<Triad*> triads;

    RefTree<RefValue>& tree;

    TriadBuilderV2(RefTree<RefValue>& tree)
        : tree(tree)
    {

    }

    void buildCascade(RefTreeNode<RefValue>* node, int depth, Triad* p_triad) {
        if (node == NULL)
            return;

        for (int i = 0; i < node->items.size(); ++i) {
            RefTreeNode<RefValue>* item = node->items[i];

            if (*item->value->syntaxChar == SyntaxChars::IDENTIFIER) {
                Triad* triad = new Triad(0, item->value);

                if (p_triad != nullptr) {
                    p_triad->operands[i] = triad;
                }
            }
            else {
                Triad* triad = new Triad(gen++, item->value->syntaxChar);

                if (p_triad != nullptr) {
                    p_triad->operands[i] = triad;
                }

                triads.push_front(triad);

                buildCascade(item, depth + 1, triad);           
            }
        }
    }

    std::list<Triad*> build(int id = 0) {
        buildCascade(tree.root, 0, nullptr);

        for (Triad* triad : triads) {
            triad->id = (triads.size() - triad->id + 1 + id);
        }

        return triads;
    }
};


struct TriadOpt1 {
public:
    bool error = false;
    std::string message = "";
private:

    TableOfContants tableOfContants;
    
    std::list<Triad*>& triads;

    void saveIfConst(Triad* triad) {
        if (triad->operands[1]->isValue() &&
            triad->operands[1]->getToken()->type == TermTypes::NUMBER) {

            auto& key = triad->operands[0]->getToken()->value;
            auto& value = triad->operands[1];

            tableOfContants.saveVariable(key, value);
        }
    }

    std::string getTriadValue(SyntaxChar& op, int a, int b) {
        int result = 0;
        //if (op == SyntaxChars::PLUS) {
        //    result = a + b;
        //}
        //else if (op == SyntaxChars::MINUS) {
        //    result = a - b;
        //}
        //else if (op == SyntaxChars::MULTIPLY) {
        //    result = a * b;
        //}
        //else if (op == SyntaxChars::DIVIDE) {
        //    result = a / b;
        //}

        //if (result <= 0 || result >= 4000) {

        //    error = true;
        //    message = "Семантическая ошибка: \nПереполнение типа 'Римское число' [1-3999] при выполнении операции: `" 
        //        + Roman::to_roman(a) + " " + op.tokenString + " " + Roman::to_roman(b) + "`";
        //    return Roman::to_roman(1);
        //}

        return Roman::to_roman(result);
    }

    void assignIfConst(bool& isAssigned, Token* token, int& assignTo) {
        if (!isAssigned && token->type == TermTypes::IDENTIFIER) {
            isAssigned = tableOfContants.tryAssignIntTo(token->value, assignTo);
        }
    }

    void assignIfValue(bool& isAssigned, Token* token, int& assignTo) {
        if (!isAssigned && token->type == TermTypes::NUMBER) {
            assignTo = Roman::to_int(token->value);
            isAssigned = true;
        }
    }

    struct CountValue {
        bool isAssigned = false;
        int value = 0;
        Token* token = nullptr;

        CountValue(Token* token)
            : token(token)
        { }
    };

public:

    TriadOpt1(std::list<Triad*>& triads)
        : triads(triads)
    {

    }

    void reduce() {
        int i = 1;

        std::list<Triad*> onRemove;

        for (Triad* triad : triads) {
            bool isMarkedToRemove = false;

            if (triad->op == nullptr) {
                std::cerr << "operator is nullptr\n";
                exit(-3);
            }

            if (!triad->isValue() && *triad->op == SyntaxChars::ASSIGNMENT) {

                std::cout << " | " << std::setw(2) << triad->id << "  | " << std::setw(18) << triad->toString() << "\n";
                saveIfConst(triad);
            }
            else if (!triad->isValue() && triad->isOperandsNumbersOrVars()) {
                
                std::vector<CountValue> elements {
                    CountValue(triad->operands[0]->getToken()),
                    CountValue(triad->operands[1]->getToken())
                };

                for (auto& element : elements) {
                    assignIfValue(element.isAssigned, element.token, element.value);
                    assignIfConst(element.isAssigned, element.token, element.value);
                }

                if (elements.at(0).isAssigned && elements.at(1).isAssigned) {
                    
                    std::string roman = getTriadValue(*triad->op,
                        elements.at(0).value, elements.at(1).value);

                    std::cout << " | " << std::setw(2) << triad->id << "  | " << std::setw(18) << triad->toString() << " -> C("
                        << roman << ", 0)\n";
                    
                    triad->operands.clear();
                    triad->op = nullptr;
                    triad->value = new RefValue(
                        new SyntaxChar(SyntaxChars::IDENTIFIER),
                        new Token(roman, TermTypes::NUMBER)
                    );

                    onRemove.push_back(triad);
                    isMarkedToRemove = true;
                }
                else {
                    std::cout << " | " << std::setw(2) << triad->id << "  | " << std::setw(18) << triad->toString() << "\n";
                }
            }
            else {
                std::cout << " | " << std::setw(2) << triad->id << "  | " << std::setw(18) << triad->toString() << "\n";
            }

            if (!isMarkedToRemove) {
                triad->id = i++;
            }          
        }

        for (Triad* triad : onRemove) {
            triads.remove(triad);
        }
    }
};



