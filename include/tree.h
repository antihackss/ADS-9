// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>
#include <memory>

class PMTree {
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
    void getAllPermsHelper(std::shared_ptr<Node> node, std::vector<char>& current, 
                          std::vector<std::vector<char>>& result) const;
    void getPermByNumHelper(std::shared_ptr<Node> node, int& remainingSteps, 
                           std::vector<char>& result) const;

public:
    explicit PMTree(const std::vector<char>& in);
    int getTotalPermutations() const { return totalPermutations; }
    const std::vector<char>& getElements() const { return elements; }
    std::shared_ptr<Node> getRoot() const { return root; }
};

std::vector<std::vector<char>> getAllPerms(const PMTree& tree);
std::vector<char> getPerm1(const PMTree& tree, int num);
std::vector<char> getPerm2(const PMTree& tree, int num);

#endif  // INCLUDE_TREE_H_
