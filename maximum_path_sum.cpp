// Leetcode: https://leetcode.com/problems/binary-tree-maximum-path-sum/#/description
// Given a binary tree, find the maximum path sum. A path is defined as any non-empty sequence
// of nodes from using only parent-child connections. The path does not need to go through the root.

// Brute Force: Explore all n choose 2 pairs of nodes, tracking max path. O(n^3) time.
// Better: Traverse the tree, 

#include <vector>
#include <iostream>
#include <assert.h>
#include "tree_node.h"

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
        //std::cout << "Root = " << root->val << std::endl;

        auto left_sum = maxPathSum(root->left, max_span);
        //std::cout << "left sum = " << left_sum << std::endl;
        auto left_plus_root = left_sum + root->val;
        //std::cout << "left plus root = " << left_plus_root << std::endl;


        auto right_sum = maxPathSum(root->right, max_span);
        auto right_plus_root = right_sum + root->val;
        //std::cout << "right plus root = " << right_plus_root << std::endl;

        auto max_subtree = std::max(left_sum, right_sum);
        auto max_with_root = std::max(left_plus_root, right_plus_root);
        //std::cout << "Max with root = " << max_with_root << std::endl;
        max_with_root = std::max(max_with_root, root->val);

        //std::cout << "  1. Max span = " << max_span << std::endl;
        max_span = std::max(max_span, root->val);
        //std::cout << "  2. Max span = " << max_span << std::endl;
        max_span = std::max(max_span, max_subtree);
        //std::cout << "  3. Max span = " << max_span << std::endl;
        max_span = std::max(max_span, max_with_root);
        //std::cout << "  4. Max span = " << max_span << std::endl;
        max_span = std::max(max_span, left_sum + right_sum + root->val);
        //std::cout << "  5. Max span = " << max_span << std::endl;
        return std::max(left_plus_root, right_plus_root);
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
    //print(root);

    auto max_path = soln.maxPathSum(root);
    std::cout << "Max Path = " << max_path << std::endl;
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
}

int main(int argc, char** argv) {
    test_max_path_sum();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
