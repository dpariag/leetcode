// Leetcode: https://leetcode.com/problems/path-sum/#/description
// Given a binary tree and a number, determine if the tree has a root-to-leaf path whose values sum
// to the given number.

// Brute Force:
// Better:

#include <vector>
#include <iostream>
#include <assert.h>
#include "tree_node.h"

// Accepted. 9ms. Beats 23.71% of submissions, ties 65.73% of submissions.
class Solution {
public:
    bool hasPathSum(TreeNode* root, int sum) {
        if (root == nullptr) { return false; }

        sum -= root->val;
        if (root->left == nullptr && root->right == nullptr) {
            return sum == 0; 
        }
        return hasPathSum(root->left, sum) || hasPathSum(root->right, sum);
    }
};

int main(int argc, char** argv) {
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
