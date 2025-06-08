// Copyright 2022 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include <algorithm>
#include <stdexcept>
#include  "tree.h"

PMTree::PMTree(const std::vector<char>& in) : elements(in), totalPermutations(1) {
    if (in.empty()) {
        root = nullptr;
        return;
    }

    for (size_t i = 2; i <= in.size(); ++i) {
        totalPermutations *= i;
    }

    root = std::make_shared<Node>('\0');
    buildTree(root, in);
}

void PMTree::buildTree(std::shared_ptr<Node> parent, const std::vector<char>& remaining) {
    if (remaining.empty()) return;

    for (size_t i = 0; i < remaining.size(); ++i) {
        auto child = std::make_shared<Node>(remaining[i]);
        parent->children.push_back(child);

        std::vector<char> newRemaining = remaining;
        newRemaining.erase(newRemaining.begin() + i);
        buildTree(child, newRemaining);
    }
}

void PMTree::getAllPermsHelper(std::shared_ptr<Node> node, std::vector<char>& current, 
                             std::vector<std::vector<char>>& result) const {
    if (node->value != '\0') {
        current.push_back(node->value);
    }

    if (node->children.empty()) {
        result.push_back(current);
    } else {
        for (const auto& child : node->children) {
            getAllPermsHelper(child, current, result);
        }
    }

    if (node->value != '\0') {
        current.pop_back();
    }
}

void PMTree::getPermByNumHelper(std::shared_ptr<Node> node, int& remainingSteps, 
                              std::vector<char>& result) const {
    if (node->value != '\0') {
        result.push_back(node->value);
    }

    if (node->children.empty()) {
        remainingSteps--;
    } else {
        for (const auto& child : node->children) {
            if (remainingSteps <= 0) break;
            getPermByNumHelper(child, remainingSteps, result);
        }
    }

    if (remainingSteps > 0 && node->value != '\0') {
        result.pop_back();
    }
}

std::vector<std::vector<char>> getAllPerms(const PMTree& tree) {
    std::vector<std::vector<char>> result;
    if (tree.getRoot() == nullptr) return result;

    std::vector<char> current;
    tree.getAllPermsHelper(tree.getRoot(), current, result);
    return result;
}

std::vector<char> getPerm1(const PMTree& tree, int num) {
    if (num < 1 || num > tree.getTotalPermutations()) {
        return {};
    }

    auto allPerms = getAllPerms(tree);
    return allPerms[num - 1];
}

std::vector<char> getPerm2(const PMTree& tree, int num) {
    if (num < 1 || num > tree.getTotalPermutations()) {
        return {};
    }

    std::vector<char> result;
    int remainingSteps = num;
    tree.getPermByNumHelper(tree.getRoot(), remainingSteps, result);
    return result;
}

