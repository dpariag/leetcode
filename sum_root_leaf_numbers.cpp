// Leetcode: https://leetcode.com/problems/sum-root-to-leaf-numbers/
// Given a binary tree containing digits from 0-9 only, each root-to-leaf path represents a number.
// Example: The root-to-leaf path 1->2->3 which represents the number 123.
// Find the total sum of all root-to-leaf numbers in the tree

#include <vector>
#include <iostream>
#include <assert.h>
#include "tree_node.h"

// Accepted. 3ms. Beats 8.57% of submissions, and ties 90.82% of submisssions.
class Solution {
public:
    int sumNumbers(TreeNode* root) {
        return pre_order_sum(root, 0);
    }

private:
    int pre_order_sum(TreeNode* node, int current_sum) {
        if (node == nullptr) { return 0; }

        current_sum *= 10;
        current_sum += node->val;

        // Avoid recursing on empty subtrees (to save time)
        if (node->left == nullptr && node->right == nullptr) { return current_sum; }
        if (node->left == nullptr) { return pre_order_sum(node->right, current_sum); }
        if (node->right == nullptr) { return pre_order_sum(node->left, current_sum); }
        return pre_order_sum(node->left, current_sum) + pre_order_sum(node->right, current_sum);
    }
};

bool test_sum_numbers(const std::vector<int>& numbers, int expected_sum) {
    Solution soln;
    TreeNode* tree = nullptr;

    bst_insert(tree, numbers);
    return (soln.sumNumbers(tree) == expected_sum);
}

void test_sum_numbers() {
    assert(test_sum_numbers({}, 0));                    // empty tree
    assert(test_sum_numbers({5}, 5));                   // single node tree
    assert(test_sum_numbers({5, 4, 7}, 111));           // full tree (all nodes have 2 children)
    assert(test_sum_numbers({5, 4, 7, 2}, 599));        // node with one child
    assert(test_sum_numbers({5, 3, 7, 2, 4}, 1123));    // unbalanced tree
    assert(test_sum_numbers({0, 3, 7, 2, 4}, 406));     // zero root
    assert(test_sum_numbers({1, 0, 7, 2, 4}, 1734));    // zero leaf 
}

int main(int argc, char** argv) {
    test_sum_numbers();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
