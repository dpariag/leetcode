// Leetcode: https://leetcode.com/problems/diameter-of-binary-tree/description/
// Given a binary tree, compute the length of the longest path between any two nodes in the tree.

// Brute Force: For every pair of nodes, find their distances from their LCA. O(n^3)
// Better: Post-order traversal of the tree, tracking the longest path in each subtree.
// Update the max diameter based on the sum of paths in each pair of subtrees. O(n) time.

#include <vector>
#include <iostream>
#include <assert.h>
#include "tree_node.h"

// Accepted. 6ms. Beats 86.09% of submissions, ties 13.91% of submissions.
class Solution {
public:
    int find_diameter(TreeNode* root, int& diameter) {
        if (root == nullptr) { return 0; }

        auto longest_left = find_diameter(root->left, diameter);
        auto longest_right = find_diameter(root->right, diameter);

        // Update diameter based on longest path in each subtree 
        diameter = std::max(diameter, longest_left + longest_right);
        // Return the longest available path to the parent
        return 1 + std::max(longest_left, longest_right);
    }

    int diameterOfBinaryTree(TreeNode* root) {
        int diameter = 0;
        find_diameter(root, diameter);
        return diameter;
    }
};

bool test_tree_diameter(const std::vector<int> node_values, int expected_diameter) {
    Solution soln;
    TreeNode* root = nullptr;
    bst_insert(root, node_values);
    return soln.diameterOfBinaryTree(root) == expected_diameter;
}

void test_tree_diameter() {
    assert(test_tree_diameter({10,4,3,8,2,6,1}, 5));
    assert(test_tree_diameter({10,4,3,8,2,6,1,15}, 5));
    assert(test_tree_diameter({10,4,3,8,2,6,1,15,12}, 6));
    assert(test_tree_diameter({10,4,3,8,2,6,1,15,12}, 6));
    assert(test_tree_diameter({10,4,3,8,2,6,1,15,12,34,22}, 7));
}

int main(int argc, char** argv) {
    test_tree_diameter();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
