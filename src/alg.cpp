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

std::vector<std::vector<char>> PMTree::getAllPerms() const {
    std::vector<std::vector<char>> result;
    if (!root) return result;

    std::vector<char> current;
    collectPermutations(root, current, result);
    return result;
}

void PMTree::collectPermutations(std::shared_ptr<Node> node, 
                               std::vector<char>& current, 
                               std::vector<std::vector<char>>& result) const {
    if (node->value != '\0') {
        current.push_back(node->value);
    }

    if (node->children.empty()) {
        result.push_back(current);
    } else {
        for (const auto& child : node->children) {
            collectPermutations(child, current, result);
        }
    }

    if (node->value != '\0') {
        current.pop_back();
    }
}

std::vector<char> PMTree::getPermByNum(int num) const {
    std::vector<char> result;
    if (num < 1 || num > totalPermutations || !root) return result;

    int remainingSteps = num;
    findPermByNum(root, remainingSteps, result);
    return result;
}

bool PMTree::findPermByNum(std::shared_ptr<Node> node, 
                         int& remainingSteps, 
                         std::vector<char>& result) const {
    if (node->value != '\0') {
        result.push_back(node->value);
    }

    if (node->children.empty()) {
        if (--remainingSteps == 0) return true;
    } else {
        for (const auto& child : node->children) {
            if (findPermByNum(child, remainingSteps, result)) {
                return true;
            }
        }
    }

    if (node->value != '\0') {
        result.pop_back();
    }
    return false;
}

std::vector<std::vector<char>> getAllPerms(const PMTree& tree) {
    return tree.getAllPerms();
}

std::vector<char> getPerm1(const PMTree& tree, int num) {
    if (num < 1 || num > tree.getTotalPermutations()) {
        return {};
    }

    auto allPerms = tree.getAllPerms();
    return allPerms[num - 1];
}

std::vector<char> getPerm2(const PMTree& tree, int num) {
    return tree.getPermByNum(num);
}
