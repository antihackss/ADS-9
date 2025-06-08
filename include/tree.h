// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>
#include <memory>

class PMTree {
public:
    struct Node {
        char value;
        std::vector<std::unique_ptr<Node>> children;
        Node(char v);
    };

    explicit PMTree(const std::vector<char>& symbols);

    std::unique_ptr<Node> root;

private:
    void buildTree(Node* parent, const std::vector<char>& symbols);
};

std::vector<std::vector<char>> getAllPerms(PMTree& tree);
std::vector<char> getPerm1(PMTree& tree, int num);
std::vector<char> getPerm2(PMTree& tree, int num);

#endif  // INCLUDE_TREE_H_
