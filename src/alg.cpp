// Copyright 2022 NNTU-CS
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <locale>
#include <stdexcept>
#include <vector>
#include "tree.h"

static void collectAll(PMTree::Node* node,
                      std::vector<char>& path,
                      std::vector<std::vector<char>>& result) {
    if (!node) return;
    if (node->value != '\0') path.push_back(node->value);

    if (node->children.empty()) {
        if (!path.empty()) result.push_back(path);
    } else {
        for (auto& child : node->children)
            collectAll(child.get(), path, result);
    }

    if (node->value != '\0') path.pop_back();
}

std::vector<std::vector<char>> getAllPerms(PMTree& tree) {
    std::vector<std::vector<char>> result;
    std::vector<char> path;
    collectAll(tree.root.get(), path, result);
    return result;
}

std::vector<char> getPerm1(PMTree& tree, int num) {
    auto perms = getAllPerms(tree);
    if (num < 1 || num > static_cast<int>(perms.size()))
        return {};
    return perms[num - 1];
}

static int factorial(int n) {
    int res = 1;
    for (int i = 2; i <= n; ++i)
        res *= i;
    return res;
}

std::vector<char> getPerm2(PMTree& tree, int num) {
    std::vector<char> symbols;
    for (auto& child : tree.root->children)
        symbols.push_back(child->value);

    int n = static_cast<int>(symbols.size());
    int total = factorial(n);
    if (num < 1 || num > total)
        return {};

    --num;
    std::vector<char> result;
    std::vector<char> pool = symbols;

    for (int i = n; i >= 1; --i) {
        int f = factorial(i - 1);
        int idx = num / f;
        result.push_back(pool[idx]);
        pool.erase(pool.begin() + idx);
        num %= f;
    }
    return result;
}
