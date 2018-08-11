// Leetcode: https://leetcode.com/problems/find-bottom-left-tree-value/description/
// Given a binary tree, find the leftmost value in the last row of the tree.

// Approach: Do a pre-order traversal, tracking the depth of each node visited.
// Each time a new level is discovered, it's leftmost leaf is visited first. O(n) time.

#include <iostream>
#include <assert.h>
#include "tree_node.h"

// Accepted. 8ms. Beats 98.04% of cpp submissions.
class Solution {
public:
    void bottom_left(TreeNode* root, int cur_level, int& max_level, int& value) {
        if (root == nullptr) return;

        if (cur_level > max_level) {
            max_level = cur_level;
            value = root->val;
        }
        
        bottom_left(root->left, cur_level+1, max_level, value);
        bottom_left(root->right, cur_level+1, max_level, value);
    }

    // Based on a pre-order traversal
    int findBottomLeftValue(TreeNode* root) {
        int value, max_level = -1;
        bottom_left(root, 0, max_level, value);
        return value; 
    }
};

int main(int argc, char** argv) {
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
