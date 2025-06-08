// Copyright 2022 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include <algorithm>
#include <stdexcept>
#include  "tree.h"

PMTree::PMTree(const std::vector<char>& in) {
    if (in.empty()) {
        root = nullptr;
        totalPermutations = 0;
        return;
    }

    totalPermutations = 1;
    for (size_t i = 2; i <= in.size(); i++) {
        totalPermutations *= i;
    }

    root = std::make_shared<Node>(in[0]);
    std::vector<char> remaining = in;
    remaining.erase(remaining.begin());
    buildTree(root, remaining);
}

void PMTree::buildTree(std::shared_ptr<Node> node, const std::vector<char>& remaining) {
    if (remaining.empty()) return;

    for (char val : remaining) {
        auto child = std::make_shared<Node>(val);
        node->children.push_back(child);

        std::vector<char> newRemaining;
        for (char r : remaining) {
            if (r != val) newRemaining.push_back(r);
        }

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
    current.push_back(node->value);

    if (node->children.empty()) {
        result.push_back(current);
    } else {
        for (const auto& child : node->children) {
            collectPermutations(child, current, result);
        }
    }

    current.pop_back();
}

std::vector<char> PMTree::getPermByNum(int num) const {
    std::vector<char> result;
    if (num < 1 || num > totalPermutations || !root) return result;

    int remainingSteps = num - 1;
    findPermutation(root, remainingSteps, result);
    return result;
}

bool PMTree::findPermutation(std::shared_ptr<Node> node, 
                            int& remainingSteps, 
                            std::vector<char>& result) const {
    result.push_back(node->value);

    if (node->children.empty()) {
        return true;
    }

    size_t childCount = node->children.size();
    size_t subtreeSize = totalPermutations / (result.size() * childCount);

    for (const auto& child : node->children) {
        if (remainingSteps < subtreeSize) {
            return findPermutation(child, remainingSteps, result);
        }
        remainingSteps -= subtreeSize;
    }

    return false;
}

size_t PMTree::getTotalPermutations() const {
    return totalPermutations;
}

std::vector<std::vector<char>> getAllPerms(const PMTree& tree) {
    return tree.getAllPerms();
}

std::vector<char> getPerm1(const PMTree& tree, int num) {
    auto allPerms = tree.getAllPerms();
    if (num < 1 || num > allPerms.size()) return {};
    return allPerms[num - 1];
}

std::vector<char> getPerm2(const PMTree& tree, int num) {
    return tree.getPermByNum(num);
}
