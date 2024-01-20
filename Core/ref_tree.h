#pragma once

#include "pch.h"

#include <iostream>
#include <vector>
#include <functional>

template <class T>
struct RefTreeNode {
    T* value;
    RefTreeNode<T>* parent;
    std::vector<RefTreeNode<T>*> items;

    RefTreeNode(RefTreeNode<T>* parent, T* value) {
        this->value = value;
        this->parent = parent;
    }

    void addChild(T* value) {
        RefTreeNode<T>* node = new RefTreeNode<T>(this, value);
        this->items.push_back(node);
    }
};

template <class T>
class RefTree {
public:
    RefTreeNode<T>* root;

    RefTree() {
        root = new RefTreeNode<T>(NULL, NULL);
    }

    void print(std::function<void(RefTreeNode<T>* node, int depth)> action) {
        printInorderCascade(root, 0, action);
    }

    void inorder(std::function<void(RefTreeNode<T>* node, int depth)> action) {
        inorderCascade(root, 0, action);
    }

private:

    static void inorderCascade(RefTreeNode<T>* node, int depth, std::function<void(RefTreeNode<T>* node, int depth)> action) {
        if (node == nullptr)
            return;

        for (RefTreeNode<T>* item : node->items) {
            action(item, depth);
            inorderCascade(item, depth + 1, action);
        }
    }

    static void printInorderCascade(RefTreeNode<T>* node, int depth,
        std::function<void(RefTreeNode<T>* node, int depth)> action) {

        if (node == NULL)
            return;

        for (RefTreeNode<T>* item : node->items) {
            action(item, depth);
            printInorderCascade(item, depth + 1, action);
        }
    }
};