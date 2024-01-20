#pragma once

#include "ref_value.h"
#include "ref_tree.h"
#include "syntax_chars.h"

class OperatorsTreeBuilder {
public:
    RefTree<RefValue>& tree;

    OperatorsTreeBuilder(RefTree<RefValue>& tree)
        : tree(tree)
    { }

    void build() {
        removeUselessNonterms(tree.root, 0);
        moveOperatorsUpper(tree.root, 0);
    }

    void removeUselessNonterms(RefTreeNode<RefValue>* parent, int depth) {
        if (parent->items.size() == 1 && depth != 0) {
            if (*parent->items[0]->value->syntaxChar == SyntaxChars::IDENTIFIER) {
                parent->value = parent->items[0]->value;
                parent->items.clear();
            }

            if (parent->items.size() == 1 && *parent->items[0]->value->syntaxChar == SyntaxChars::NONTERMINAL) {
                parent->items = parent->items[0]->items;
            }

        }

        for (int i = parent->items.size() - 1; i >= 0; --i) {
            removeUselessNonterms(parent->items[i], depth + 1);
        }
    }

    void moveOperatorsUpper(RefTreeNode<RefValue>* parent, int depth) {
        for (int i = parent->items.size() - 1; i >= 0; --i) {
            moveOperatorsUpper(parent->items[i], depth + 1);
        }

        if (parent->items.size() == 3) {
            parent->value = parent->items[1]->value;

            parent->items.erase(parent->items.begin() + 1, parent->items.begin() + 2);

        }
    }
};