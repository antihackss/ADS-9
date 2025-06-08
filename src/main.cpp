// Copyright 2022 NNTU-CS
#include "tree.h"
#include <iostream>
#include <chrono>
#include <random>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>

void printPermutation(const std::vector<char>& perm) {
    for (char c : perm) {
        std::cout << c;
    }
    std::cout << std::endl;
}

int main() {
    std::vector<char> elements = {'1', '2', '3'};
    PMTree tree(elements);

    std::cout << "All permutations:" << std::endl;
    auto allPerms = getAllPerms(tree);
    for (const auto& perm : allPerms) {
        printPermutation(perm);
    }

    std::cout << "\nTest cases:" << std::endl;
    std::cout << "Permutation 1: ";
    printPermutation(getPerm1(tree, 1));

    std::cout << "Permutation 2: ";
    printPermutation(getPerm2(tree, 2));

    std::cout << "Permutation 6: ";
    printPermutation(getPerm1(tree, 6));

    std::cout << "Permutation 8: ";
    printPermutation(getPerm2(tree, 8));

    return 0;
}
