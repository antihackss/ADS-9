// Copyright 2022 NNTU-CS
#include "tree.h"
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>
#include <vector>

int main() {
    std::vector<char> in = {'1', '2', '3'};
    PMTree tree(in);

    auto perms = getAllPerms(tree);
    std::cout << "Все перестановки:\n";
    for (const auto& perm : perms) {
        for (char c : perm) std::cout << c;
        std::cout << '\n';
    }

    std::cout << "Перестановка №2 (getPerm1): ";
    auto p1 = getPerm1(tree, 2);
    for (char c : p1) std::cout << c;
    std::cout << '\n';

    std::cout << "Перестановка №2 (getPerm2): ";
    auto p2 = getPerm2(tree, 2);
    for (char c : p2) std::cout << c;
    std::cout << '\n';

    std::ofstream fout("result/times.csv");
    fout << "n,all,perm1,perm2\n";

    std::random_device rd;
    std::mt19937 gen(rd());

    for (int n = 1; n <= 8; ++n) {
        std::vector<char> symbols(n);
        for (int i = 0; i < n; ++i)
            symbols[i] = 'a' + i;

        PMTree tree(symbols);
        int total = 1;
        for (int i = 2; i <= n; ++i) total *= i;
        std::uniform_int_distribution<> dis(1, total);

        int num = dis(gen);

        auto t1 = std::chrono::high_resolution_clock::now();
        auto all = getAllPerms(tree);
        auto t2 = std::chrono::high_resolution_clock::now();
        auto perm1 = getPerm1(tree, num);
        auto t3 = std::chrono::high_resolution_clock::now();
        auto perm2 = getPerm2(tree, num);
        auto t4 = std::chrono::high_resolution_clock::now();

        double dt_all = std::chrono::duration<double, std::milli>(t2 - t1).count();
        double dt_perm1 = std::chrono::duration<double, std::milli>(t3 - t2).count();
        double dt_perm2 = std::chrono::duration<double, std::milli>(t4 - t3).count();

        fout << n << "," << dt_all << "," << dt_perm1 << "," << dt_perm2 << "\n";
        std::cout << "n=" << n << " done\n";
    }
    fout.close();

    std::cout << "Эксперимент завершён. Данные в result/times.csv\n";
    return 0;
}
