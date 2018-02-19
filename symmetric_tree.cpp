// Leetcode: https://leetcode.com/problems/symmetric-tree/description/
// Given a binary tree, check whether it is a mirror of itself (i.e., symmetric around its center).

// Approach: Use two pointers to traverse the tree. O(n) time and O(h) space.

#include <iostream>
#include <assert.h>
#include "tree_node.h"

// Accepted. 9ms. Ties 9.90% of submissions.
class Solution {
public:

    bool is_symmetric(TreeNode* left, TreeNode* right) {
        if (left == nullptr && right == nullptr) { return true;  }
        if (left == nullptr || right == nullptr) { return false; }
    
        // Neither is null
        if (left->val != right->val) { return false; }
        return is_symmetric(left->left, right->right) &&
               is_symmetric(left->right, right->left);
    }

    bool isSymmetric(TreeNode* root) {
        if (root == nullptr) { return true; }
        return is_symmetric(root->left, root->right);
    }
};

int main(int argc, char** argv) {
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}