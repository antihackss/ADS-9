// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>
#include <memory>

class PMTree {
public:
    explicit PMTree(const std::vector<char>& in);
    int getTotalPermutations() const { return totalPermutations; }
    std::vector<std::vector<char>> getAllPerms() const;
    std::vector<char> getPermByNum(int num) const;

private:
    struct Node {
        char value;
        std::vector<std::shared_ptr<Node>> children;
        Node(char v) : value(v) {}
    };

    std::shared_ptr<Node> root;
    int totalPermutations;
    std::vector<char> elements;

    void buildTree(std::shared_ptr<Node> parent, const std::vector<char>& remaining);
    void collectPermutations(std::shared_ptr<Node> node, 
                           std::vector<char>& current, 
                           std::vector<std::vector<char>>& result) const;
    bool findPermByNum(std::shared_ptr<Node> node, 
                      int& remainingSteps, 
                      std::vector<char>& result) const;
};

#endif  // INCLUDE_TREE_H_
