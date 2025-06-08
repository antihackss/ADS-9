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

void runExperiment() {
    std::vector<int> sizes = {3, 4, 5, 6, 7, 8};
    std::random_device rd;
    std::mt19937 gen(rd());
    
    std::cout << "n\tgetAllPerms (ms)\tgetPerm1 (ms)\tgetPerm2 (ms)\n";
    std::cout << "------------------------------------------------\n";
    
    for (int n : sizes) {
        std::vector<char> elements;
        for (int i = 1; i <= n; i++) {
            elements.push_back('0' + i);
        }
        
        PMTree tree(elements);
        
        std::uniform_int_distribution<> dist(1, tree.getAllPermsHelper().size());
        int num = dist(gen);
        
        auto start = std::chrono::high_resolution_clock::now();
        auto allPerms = ::getAllPerms(tree);
        auto end = std::chrono::high_resolution_clock::now();
        auto allPermsTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        
        start = std::chrono::high_resolution_clock::now();
        auto perm1 = ::getPerm1(tree, num);
        end = std::chrono::high_resolution_clock::now();
        auto perm1Time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        
        start = std::chrono::high_resolution_clock::now();
        auto perm2 = ::getPerm2(tree, num);
        end = std::chrono::high_resolution_clock::now();
        auto perm2Time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        
        std::cout << n << "\t"
                  << allPermsTime << "\t\t\t"
                  << perm1Time << "\t\t"
                  << perm2Time << "\n";
    }
}

int main() {
    std::vector<char> elements = {'1', '2', '3'};
    PMTree tree(elements);
    
    std::cout << "All permutations:\n";
    auto allPerms = ::getAllPerms(tree);
    for (const auto& perm : allPerms) {
        printPermutation(perm);
    }
    
    std::cout << "\nPermutation 1: ";
    printPermutation(::getPerm1(tree, 1));
    
    std::cout << "Permutation 2: ";
    printPermutation(::getPerm2(tree, 2));
    
    std::cout << "\nRunning performance experiment...\n\n";
    runExperiment();
    
    return 0;
}
