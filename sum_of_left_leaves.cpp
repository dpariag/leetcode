// Leetcode: https://leetcode.com/problems/sum-of-left-leaves/description/
// Return the sum of all left leaves in a binary tree.

// Approach: Traverse the tree tracking if the current node is a left child or not. O(n) time.

#include <vector>
#include <iostream>
#include <assert.h>
#include "tree_node.h"

// Accepted. 3ms. Beats 41.30% of submissions, ties 58.70% of submissions.
class Solution {
public:
    int sum(TreeNode* root, bool is_left) {
        if (root == nullptr) { return 0; }

        if (root->left == nullptr && root->right == nullptr) {
            return is_left ? root->val : 0;
        } 
        return sum(root->left, true) + sum(root->right, false);
    }
    
    int sumOfLeftLeaves(TreeNode* root) {
        return sum(root, false);
    }
};

int main(int argc, char** argv) {
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
