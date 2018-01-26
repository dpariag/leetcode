// Leetcode: https://leetcode.com/problems/closest-binary-search-tree-value/description/
// Given a non-empty binary search tree and a floating point target value, 
// find the value in the BST that is closest to the target.

// Brute Force: Traverse the entire tree comparing distance to the target. O(n) time.
// Better: Binary search for target, comparing distance to target along the way. O(h) time.

#include <limits>
#include <iostream>
#include <cmath>
#include <assert.h>
#include "tree_node.h"

// Accepted. 10ms. Beats 11.30% of submissions, ties 62.34% of submissions.
class Solution {
public:
    int closestValue(TreeNode* root, double target) {
        TreeNode* cur = root;
        int closest = std::numeric_limits<int>::max();
        double min_delta = std::numeric_limits<double>::max();

        while (cur != nullptr) {
            double cur_value(cur->val);
            double delta = std::abs(target - cur_value);
            if (delta < min_delta) {
                min_delta = delta;
                closest = cur->val;
            }

            if (target < cur->val) {
                cur = cur->left;
            } else {
                cur = cur->right;
            }
        }
        return closest;
  }
};

int main(int argc, char** argv) {
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
