#pragma once
#include "table_of_vars.h"
#include <list>
#include "syntax_chars.h"
#include "triad_math.h"

struct TriadOpt2 {
    TableOfVars tableOfVars;

    std::list<Triad*>& triads;

    TriadOpt2(std::list<Triad*>& triads)
        : triads(triads)
    {

    }

    void setDepValues() {
        int i = 1;
        for (Triad* triad : triads) {
            if (*triad->op == SyntaxChars::ASSIGNMENT) {
                triad->dep = i;
                tableOfVars.saveVariable(triad->operands[0]->getToken()->value, triad);
            }
            else {
                int deps[2] = { 0,0 };
                for (int i = 0; i < triad->operands.size(); ++i) {
                    Triad* operand = triad->operands.at(i);
                    if (TriadH::isIdentifier(operand)) {
                        if (!tableOfVars.tryGetDep(operand->getToken()->value, deps[i])) {
                            deps[i] = operand->dep;
                        }
                    }
                }
                triad->dep = 1 + std::max<int>(deps[0], deps[1]);
            }
            ++i;
        }
    }

    void clearSameTriads() {
        int i = 1;

        std::list<Triad*> onRemove;

        for (Triad* aTriad : triads) {
            bool isMarkedToRemove = false;

            Triad* a = aTriad->tryGetSame();

            for (Triad* bTriad : triads) {
                if (aTriad == bTriad) {
                    break;
                }
                Triad* b = bTriad->tryGetSame();

                if (a->same == nullptr && TriadH::isSame(a, b)) {
                    a->same = b;
                    onRemove.push_back(a);
                    isMarkedToRemove = true;
                }
            }

            //if (!isMarkedToRemove) {
            //    aTriad->id = i++;
            //}
        }

        i = 1;
        for (Triad* triad : triads) {
            triad->id = i++;
        }

        for (Triad* triad : triads) {
            std::cout << " | " << std::setw(2) << triad->id << "  | " << std::setw(18) << triad->toString() <<
                " DEP = " << std::setw(2) << triad->dep << ";";
            
            if (triad->same != nullptr) {
                
                std::cout << " -> SAME(^" << triad->tryGetSame()->id <<",0)";
            }
                
            std::cout << "\n";
        }

        for (Triad* triad : onRemove) {
            triads.remove(triad);
        }

        i = 1;
        for (Triad* triad : triads) {
            triad->id = i++;
        }

        for (Triad* triad : triads) {
            for (int i = 0; i < triad->operands.size(); ++i) {
                if (triad->operands[i]->same != nullptr) {
                    triad->operands[i] = triad->operands[i]->tryGetSame();
                }
            }
        }
    }
};