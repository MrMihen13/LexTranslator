#pragma once

#include "../Core/syntax_chars.h"
#include "../Core/syntax_node.h"
#include "../Core/token.h"
#include "../Core/ref_tree.h"

#include <list>

class SyntaxTreeBuilder {
public:
    RefTree<std::string>& treeView;

    SyntaxTreeBuilder(RefTree<std::string>& treeView)
        : treeView(treeView)
    { }

    void build(std::list<SyntaxNode>& ruleNodes, std::list<::Token> tokens) {
        RefTreeNode<std::string>* root = new RefTreeNode<std::string>(treeView.root, new std::string("S"));

        moveOperatorsUpper(root, ruleNodes, tokens, 0);

        treeView.root->items.push_back(root);
    }

    void moveOperatorsUpper(RefTreeNode<std::string>* parent, std::list<SyntaxNode>& rnodes,
        std::list<::Token>& tokens, int depth) {
        if (rnodes.empty())
            return;

        auto& rnode = rnodes.back();
        auto items = rnode.syntaxRule.buildRule.items;

        std::vector<RefTreeNode<std::string>*> treenodes;

        for (int i = items.size() - 1; i >= 0; --i) {
            if (items[i] == SyntaxChars::IDENTIFIER && !rnodes.empty()) { // TODO: not only for IDENTIFIER
                std::string text = tokens.back().value;
                tokens.pop_back();
                RefTreeNode<std::string>* node = new RefTreeNode<std::string>(parent, new std::string(text));

                treenodes.push_back(node);
            }
            else {
                std::string text = items[i].tokenString;
                RefTreeNode<std::string>* node = new RefTreeNode<std::string>(parent, new std::string(text));

                treenodes.push_back(node);

                if (items[i] == SyntaxChars::NONTERMINAL && !rnodes.empty()) {
                    rnodes.pop_back();
                    moveOperatorsUpper(node, rnodes, tokens, depth + 1);
                }
            }
        }

        for (int i = treenodes.size() - 1; i >= 0; --i) {
            parent->items.push_back(treenodes[i]);
        }
    }
};
