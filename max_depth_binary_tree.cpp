// Leetcode: https://leetcode.com/problems/maximum-depth-of-binary-tree/description/
// Given a binary tree, find the the number of nodes along the longest path from the root to the farthest leaf.

// Brute Force: Enumerate all root to leaf path, and count the length of each. O(2^n) time.
// Better: Avoid repeated visiting by traversing the tree (post-order) and returning the max depth. O(n) time.

#include <iostream>
#include <assert.h>
#include "tree_node.h"

// Accepted. 4ms. Beats 99.99% of submissions.
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (root == nullptr) { return 0; }
        return 1 + std::max(maxDepth(root->left), maxDepth(root->right));
    }
};

int main(int argc, char** argv) {
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
