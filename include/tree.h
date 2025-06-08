// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <memory>
#include <vector>

class PMTree {
public:
  struct Node {
    char value;
    std::vector<std::unique_ptr<Node>> children;
    explicit Node(char v = '\0') : value(v) {}
  };
  std::unique_ptr<Node> root;

  explicit PMTree(const std::vector<char>& symbols) {
    root = std::make_unique<Node>('\0');
    buildTree(root.get(), symbols);
  }

private:
  void buildTree(Node* parent, const std::vector<char>& symbols) {
    if (symbols.empty()) return;
    for (size_t i = 0; i < symbols.size(); ++i) {
      parent->children.emplace_back(new Node(symbols[i]));
      std::vector<char> next_symbols;
      for (size_t j = 0; j < symbols.size(); ++j) {
        if (j != i) next_symbols.push_back(symbols[j]);
      }
      buildTree(parent->children.back().get(), next_symbols);
    }
  }
};

std::vector<std::vector<char>> getAllPerms(PMTree& tree);
std::vector<char> getPerm1(PMTree& tree, int num);
std::vector<char> getPerm2(PMTree& tree, int num);

#endif  // INCLUDE_TREE_H_
