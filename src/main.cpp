// Copyright 2022 NNTU-CS
#include "tree.h"
#include <iostream>
#include <chrono>
#include <random>
#include <algorithm>
#include <fstream>
#include <sstream>

void printPermutation(const std::vector<char>& perm) {
    for (char c : perm) {
        std::cout << c;
    }
    std::cout << std::endl;
}

void runExperiment() {
    std::ofstream dataFile("experiment_data.csv");
    dataFile << "n,getAllPerms,getPerm1,getPerm2\n";

    for (int n = 1; n <= 10; ++n) {
        std::vector<char> in;
        for (int i = 0; i < n; ++i) {
            in.push_back('1' + i);
        }

        PMTree tree(in);

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distr(1, tree.getTotalPermutations());
        std::vector<int> randomNums;
        for (int i = 0; i < 10; ++i) {
            randomNums.push_back(distr(gen));
        }

        auto start = std::chrono::high_resolution_clock::now();
        auto allPerms = getAllPerms(tree);
        auto end = std::chrono::high_resolution_clock::now();
        double getAllTime = std::chrono::duration<double>(end - start).count();

        start = std::chrono::high_resolution_clock::now();
        for (int num : randomNums) {
            getPerm1(tree, num);
        }
        end = std::chrono::high_resolution_clock::now();
        double getPerm1Time = std::chrono::duration<double>(end - start).count() / randomNums.size();

        start = std::chrono::high_resolution_clock::now();
        for (int num : randomNums) {
            getPerm2(tree, num);
        }
        end = std::chrono::high_resolution_clock::now();
        double getPerm2Time = std::chrono::duration<double>(end - start).count() / randomNums.size();

        dataFile << n << "," << getAllTime << "," << getPerm1Time << "," << getPerm2Time << "\n";
    }

    dataFile.close();

}

int main() {
    std::vector<char> in = {'1', '2', '3'};
    PMTree tree(in);

    std::cout << "All permutations:" << std::endl;
    auto allPerms = getAllPerms(tree);
    for (const auto& perm : allPerms) {
        printPermutation(perm);
    }

    std::cout << "\nPermutation 1: ";
    printPermutation(getPerm1(tree, 1));

    std::cout << "Permutation 2: ";
    printPermutation(getPerm2(tree, 2));

    std::cout << "Permutation 6: ";
    printPermutation(getPerm1(tree, 6));

    std::cout << "Permutation 8: ";
    auto perm8 = getPerm2(tree, 8);
    if (perm8.empty()) {
        std::cout << "Not exists" << std::endl;
    }

    runExperiment();

    return 0;
}
