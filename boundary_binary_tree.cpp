// Leetcode: https://leetcode.com/problems/boundary-of-binary-tree/description/
// Return the boundary of a binary tree (moving anti-clockwise) with no duplicates.

// Brute force: 3 passes of the binary tree. O(n) time and O(h) space.
// Better: Add the root to the boundary, then:
// - do a pre-order traversal of the root's left subtree using a boolean to track if nodes are exterior.
// - do a post-order traversal of the root's right subtree using a boolean to track if nodes are exterior.
// O(n) time and O(h) space.

#include <vector>
#include <iostream>
#include <assert.h>
#include "tree_node.h"

using Traversal = std::vector<int>;

inline bool is_leaf(TreeNode* root) {
    return (root != nullptr && root->left == nullptr && root->right == nullptr);
}

void pre_order(TreeNode* root, bool is_exterior, Traversal& t) {
    if (root == nullptr) { return; }

    if (is_exterior || is_leaf(root)) {
        t.emplace_back(root->val);
    }

    pre_order(root->left, is_exterior, t);
    pre_order(root->right, (is_exterior && root->left == nullptr), t);
}

void post_order(TreeNode* root, bool is_exterior, Traversal& t) {
    if (root == nullptr) { return; }

    post_order(root->left, (is_exterior && root->right == nullptr), t);
    post_order(root->right, is_exterior, t);

    if (is_exterior || is_leaf(root)) {
        t.emplace_back(root->val);
    }
}

// Accepted. 15ms. Beats 53.85% of submissions.
class Solution {
public:
    Traversal boundaryOfBinaryTree(TreeNode* root) {
        Traversal t;
        if (root == nullptr) return t;

        t.emplace_back(root->val);
        pre_order(root->left, true, t);
        post_order(root->right, true, t);
        return t;
    }
};

bool test_tree_exterior(std::vector<int> values, Traversal expected) {
    Solution soln;

    TreeNode* root = nullptr;
    bst_insert(root, values);

    auto exterior = soln.boundaryOfBinaryTree(root);
    return exterior == expected;
}

void test_tree_exterior() {
    assert(test_tree_exterior({100}, {100}));
    assert(test_tree_exterior({100,50}, {100,50}));
    assert(test_tree_exterior({100,150}, {100,150}));

    assert(test_tree_exterior({100,50,150}, {100,50,150}));
    assert(test_tree_exterior({100,50,150,25}, {100,50,25,150}));
    assert(test_tree_exterior({100,50,150,25,125}, {100,50,25,125,150}));
    assert(test_tree_exterior({100,50,150,25,125,75,60,80,110}, {100,50,25,60,80,110,125,150}));
    assert(test_tree_exterior({100,50,150,25,125,75,60,80,110,200}, {100,50,25,60,80,110,200,150}));

}


int main(int argc, char** argv) {
    test_tree_exterior();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
