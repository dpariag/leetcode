// Leetcode: https://leetcode.com/problems/minimum-absolute-difference-in-bst/description/
// Given a BST with non-negative values, find the minimum absolute difference between any two node values.

// Approach: Think of the BST as a sorted array. Traverse the BST in-order
// comparing each node's value to it's predecessor's value. O(n) time.

#include <limits>
#include <iostream>
#include <assert.h>
#include "tree_node.h"

// Accepted. 21ms. Beats 24.60% of submisssions, ties < 1% of submissions.
class Solution {
public:
    void min_difference(TreeNode* root, int& pred, int& min_diff) {
        if (root == nullptr) { return; }

        min_difference(root->left, pred, min_diff);

        if (pred == -1) {
            pred = root->val;
        } else {
            min_diff = std::min(min_diff, std::abs(root->val - pred));
            pred = root->val;
        }
        min_difference(root->right, pred, min_diff);
    }

    int getMinimumDifference(TreeNode* root) {
        int pred = -1, min_diff = std::numeric_limits<int>::max();
        min_difference(root, pred, min_diff);
        return min_diff;
    }
};

int main(int argc, char** argv) {
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}