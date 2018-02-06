// Leetcode: https://leetcode.com/problems/validate-binary-search-tree/description/
// Given a binary tree, determine if it is a valid binary search tree (BST).
// A node's left subtree must contain only smaller keys, it's right subtree must contain only larger keys.

// Brute Force:
// Better:

#include <iostream>
#include <assert.h>
#include "tree_node.h"

struct Min {
	int val = 0;
	bool valid = false;
};

struct Max 
{
	int val = 0;
	bool valid = false;
};

// Accepted. 10ms. Beats 29.31% of submissions, ties < 1% of submissions.
class Solution {
public:
	// Pre-order traversal
	bool is_valid_bst(TreeNode* root, Min min, Max max) {
		if (root == nullptr) { return true; }

		if (min.valid && root->val <= min.val) { return false; }
		if (max.valid && root->val >= max.val) { return false; }

		bool left = false, right = false;
		left = is_valid_bst(root->left, min, Max{root->val, true});
		if (left) right = is_valid_bst(root->right, Min{root->val, true}, max);
		return left && right;
	}

    bool isValidBST(TreeNode* root) {
  		return is_valid_bst(root, Min(), Max());
    }
};

int main(int argc, char** argv) {
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
