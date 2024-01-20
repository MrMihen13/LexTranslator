#pragma once
#include "ref_tree.h"
#include "ref_value.h"
#include "syntax_chars.h"
#include "syntax_node.h"

#include <list>

class SyntaxTreeByCharBuilder {
public:
    RefTree<RefValue>& treeView;

    SyntaxTreeByCharBuilder(RefTree<RefValue>& treeView)
        : treeView(treeView)
    { }

    void build(std::list<SyntaxNode>& ruleNodes, std::list<::Token> tokens) {
        RefTreeNode<RefValue>* root = new RefTreeNode<RefValue>(
            treeView.root,
            new RefValue(
                new SyntaxChar(
                    SyntaxChars::NONTERMINAL.code,
                    SyntaxChars::NONTERMINAL.tokenString,
                    SyntaxChars::NONTERMINAL.type),
                nullptr));

        moveOperatorsUpper(root, ruleNodes, tokens, 0);

        treeView.root->items.push_back(root);
    }

    void moveOperatorsUpper(RefTreeNode<RefValue>* parent, std::list<SyntaxNode>& rnodes,
        std::list<::Token>& tokens, int depth) {
        if (rnodes.empty())
            return;

        auto& rnode = rnodes.back();
        auto items = rnode.syntaxRule.buildRule.items;

        std::vector<RefTreeNode<RefValue>*> treeNodes;

        for (int i = items.size() - 1; i >= 0; --i) {

            if (items[i] == SyntaxChars::OPEN_BRACKET ||
                items[i] == SyntaxChars::CLOSE_BRACKET ||
                items[i] == SyntaxChars::SEMICOLON)
            {
                continue;
            }

            // TODO: not only for IDENTIFIER         
            if (items[i] == SyntaxChars::IDENTIFIER && !rnodes.empty()) {
                std::string text = tokens.back().value;
                Token token = tokens.back();
                tokens.pop_back();
                RefTreeNode<RefValue>* node = new RefTreeNode<RefValue>(parent,
                    new RefValue(new SyntaxChar(SyntaxChars::IDENTIFIER),
                        new Token(token)));
                treeNodes.push_back(node);
            }
            else {
                std::string text = items[i].tokenString;
                RefTreeNode<RefValue>* node = new RefTreeNode<RefValue>(parent,
                    new RefValue(new SyntaxChar(items[i]), nullptr));
                treeNodes.push_back(node);
                if (items[i] == SyntaxChars::NONTERMINAL && !rnodes.empty()) {
                    rnodes.pop_back();
                    moveOperatorsUpper(node, rnodes, tokens, depth + 1);
                }
            }
        }

        for (int i = treeNodes.size() - 1; i >= 0; --i) {
            parent->items.push_back(treeNodes[i]);
        }
    }
};