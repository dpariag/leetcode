// Leetcode: https://leetcode.com/problems/binary-tree-maximum-path-sum/#/description
// Given a binary tree, find the maximum path sum. A path is defined as any non-empty sequence
// of nodes from using only parent-child connections. The path does not need to go through the root.

// Brute Force: Explore all n choose 2 pairs of nodes, tracking max path. O(n^3) time.
// Better: Traverse the tree, tracking the sum of each subtree, with and without the root. O(n) time

#include <vector>
#include <iostream>
#include <assert.h>
#include <limits>
#include "tree_node.h"

// Accepted. 19ms. Beats 71.05% of submissions, ties 28.63% of submissions.
class Solution {
public:
    // return the maximum sum possible that includes traversing the root node.
    int maxPathSum(TreeNode* root, int& max_span) {
        if (root == nullptr) { 
            max_span = std::max(max_span, 0);
            return 0;
        }

        if (root->left == nullptr && root->right == nullptr) {
            max_span = std::max(max_span, root->val);
            return root->val;
        }

        int left_sum, right_sum, max_subtree;
        left_sum = right_sum = max_subtree = std::numeric_limits<int>::min();
        auto left_plus_root = root->val;
        if (root->left) {
            // Find the sum of left subtree nodes, with and without the root
            left_sum = maxPathSum(root->left, max_span);
            max_subtree = std::max(max_subtree, left_sum);
            left_plus_root += left_sum;
        }

        auto right_plus_root = root->val;
        if (root->right) {
            // Find the sum of right subtree nodes, with and without the root
            right_sum = maxPathSum(root->right, max_span);
            right_plus_root += right_sum;
            max_subtree = std::max(max_subtree, right_sum);
        }

        // Find the largest sum involving the root
        auto max_with_root = std::max(left_plus_root, right_plus_root);
        max_with_root = std::max(max_with_root, root->val);

        // See if we can find a larger sum in either the root, or one of its subtrees
        max_span = std::max(max_span, root->val);
        max_span = std::max(max_span, max_subtree);
        max_span = std::max(max_span, max_with_root);
        if (root->left && root->right) {
            // See if we can craft a larger sum using both subtrees and the root
            max_span = std::max(max_span, left_sum + right_sum + root->val);
        }
        return max_with_root;
    }

    int maxPathSum(TreeNode* root) {
        int max = std::numeric_limits<int>::min();
        maxPathSum(root, max);
        return max;
    }
};

bool test_max_path_sum(std::vector<int> values, int expected_max) {
    Solution soln;
    TreeNode* root = nullptr;
    bst_insert(root, values);
    auto max_path = soln.maxPathSum(root);
    return max_path == expected_max;
}

void test_max_path_sum() {
    assert(test_max_path_sum({-2,-1}, -1));
    assert(test_max_path_sum({}, 0));
    assert(test_max_path_sum({17}, 17));
    assert(test_max_path_sum({-17}, -17));
    assert(test_max_path_sum({17,-10,-20,30,40}, 87));
    assert(test_max_path_sum({17,-10,-20,30,40,20}, 90));
    assert(test_max_path_sum({17,-10,-20,15,30,40,20}, 92));
    assert(test_max_path_sum({17,-10,-20,10,15,30,40,20}, 102));
    assert(test_max_path_sum({9,16,-5,-6,3,3,-3,-3,-3,}, 26));
}

int main(int argc, char** argv) {
    test_max_path_sum();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
