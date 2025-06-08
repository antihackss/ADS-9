// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>
#include <memory>

class PMTree {
public:
    explicit PMTree(const std::vector<char>& elements);
    
    std::vector<std::vector<char>> getAllPerms() const;
    std::vector<char> getPermByNum(int num) const;
    size_t getTotalPermutations() const;

private:
    struct Node {
        char value;
        std::vector<std::shared_ptr<Node>> children;
        Node(char val) : value(val) {}
    };
    
    std::shared_ptr<Node> root;
    size_t totalPermutations;
    
    void buildTree(std::shared_ptr<Node> node, const std::vector<char>& remaining);
    void collectPermutations(std::shared_ptr<Node> node, std::vector<char>& current, 
                           std::vector<std::vector<char>>& result) const;
    bool findPermutation(std::shared_ptr<Node> node, int& remainingSteps, 
                        std::vector<char>& result) const;
};

std::vector<std::vector<char>> getAllPerms(const PMTree& tree);
std::vector<char> getPerm1(const PMTree& tree, int num);
std::vector<char> getPerm2(const PMTree& tree, int num);

#endif  // INCLUDE_TREE_H_
