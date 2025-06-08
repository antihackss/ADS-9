// Copyright 2022 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include <algorithm>
#include <stdexcept>
#include  "tree.h"

PMTree::PMTree(const std::vector<char>& elements) {
    if (elements.empty()) {
        root = nullptr;
        totalPermutations = 0;
        return;
    }
    
    root = std::make_shared<Node>(elements[0]);
    std::vector<char> remaining = elements;
    remaining.erase(remaining.begin());
    buildTree(root, remaining);
    
    totalPermutations = 1;
    for (size_t i = 2; i <= elements.size(); i++) {
        totalPermutations *= i;
    }
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
    getAllPerms(root, current, result);
    return result;
}

void PMTree::getAllPerms(std::shared_ptr<Node> node, std::vector<char>& current, std::vector<std::vector<char>>& result) const {
    current.push_back(node->value);
    
    if (node->children.empty()) {
        result.push_back(current);
    } else {
        for (const auto& child : node->children) {
            getAllPerms(child, current, result);
        }
    }
    
    current.pop_back();
}

std::vector<char> PMTree::getPermByNum(int num) const {
    std::vector<char> result;
    if (num < 1 || num > totalPermutations || !root) return result;
    
    int remainingSteps = num - 1;
    getPermByNum(root, remainingSteps, result);
    return result;
}

void PMTree::getPermByNum(std::shared_ptr<Node> node, int& remainingSteps, std::vector<char>& result) const {
    result.push_back(node->value);
    
    if (node->children.empty()) {
        return;
    }
    
    int childFactorial = 1;
    for (int i = 2; i <= node->children.size(); i++) {
        childFactorial *= i;
    }
    
    for (const auto& child : node->children) {
        if (remainingSteps < childFactorial) {
            getPermByNum(child, remainingSteps, result);
            break;
        }
        remainingSteps -= childFactorial;
    }
}

std::vector<std::vector<char>> getAllPerms(const PMTree& tree) {
    return tree.getAllPermsHelper();
}

std::vector<char> getPerm1(const PMTree& tree, int num) {
    auto allPerms = tree.getAllPermsHelper();
    if (num < 1 || num > allPerms.size()) return {};
    return allPerms[num - 1];
}

std::vector<char> getPerm2(const PMTree& tree, int num) {
    return tree.getPermByNumHelper(num);
}

std::vector<std::vector<char>> PMTree::getAllPermsHelper() const {
    return getAllPerms();
}

std::vector<char> PMTree::getPermByNumHelper(int num) const {
    return getPermByNum(num);
}
