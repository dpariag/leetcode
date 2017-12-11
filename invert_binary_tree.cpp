// Leetcode: https://leetcode.com/problems/invert-binary-tree/description/
// Invert a binary tree.

// Approach: Perform a post-order traversal, swapping left and right children during visit.

#include <vector>
#include <iostream>
#include <assert.h>
#include "tree_node.h"

// Accepted. 0ms. Beats 60.94% of submissions, ties 39.06% of submissions.
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if (root == nullptr) { return root; }

        invertTree(root->left);
        invertTree(root->right);
        std::swap(root->left, root->right);
        return root;
    }
};

int main(int argc, char** argv) {
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}