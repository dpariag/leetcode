#ifndef TREE_NODE_H
#define TREE_NODE_H

#include <iostream>
#include <vector>

// Leetcode definition of a TreeNode
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    ~TreeNode() { delete left; delete right; }
    TreeNode(const TreeNode& other): left(nullptr), right(nullptr) {
        val = other.val;
        if (other.left != nullptr) { left = new TreeNode(*other.left); }
        if (other.right != nullptr) { right = new TreeNode(*other.right); }
    }
};

void bst_insert(TreeNode*& node, int value) {
    if (node == nullptr) {
        node = new TreeNode(value);
        return;
    }

    if (value < node->val) {
        bst_insert(node->left, value);  // insert in left subtree
    } else {
        // duplicates go on the right
        bst_insert(node->right, value); // insert in right subtree
    }
}

void bst_insert(TreeNode*& root, const std::vector<int>& values) {
    for (auto v : values) {
        bst_insert(root, v);
    }
}

void print(TreeNode* node) {
    if (node == nullptr) { return; }
    std::cout << node->val << "--> {";
    if (node->left != nullptr) {
        std::cout << node->left->val;
    }
    std::cout << ",";
    if (node->right != nullptr) {
        std::cout << node->right->val;
    }
    std::cout << "}" << std::endl;
    print(node->left);
    print(node->right);
}
#endif // TREE_NODE_H
