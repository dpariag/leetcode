// Leetcode: https://leetcode.com/problems/inorder-successor-in-bst/description/
// Given a binary search tree and a node in it, find the in-order successor of that node in the BST.

// Brute Force: Do an in-order traversal of the tree, returning the first node following the given node. O(n) time.
// Better: The node's successor is either the leftmost node in it's right subtree, or the lowest ancestor
// that holds it in it's left subtree. Leverages the BST property for O(logN) time.

#include <vector>
#include <iostream>
#include <assert.h>
#include "tree_node.h"

// Accepted. 26ms. Beats 25.62% of submissions, ties 42.86% of submissions.
class Solution {
public:
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        TreeNode* succ = nullptr;
        if (p->right) {
            // Return the leftmost node in p's right subtree
            auto succ = p->right;
            while (succ && succ->left) { succ = succ-> left; }
            return succ;
        }

        // Return the lowest ancestor of p that holds p in it's left subtree
        auto cur = root;
        while (cur != nullptr && cur != p) {
            if (p->val <= cur->val) {
                // p lies in the left subtree
                succ = cur;
                cur = cur->left;
            } else {
                // p lies in the right subtree
                cur = cur->right;
            }
        }
        return succ;
    }
};

void test_in_order_succ() {
    Solution soln;
    TreeNode* root = nullptr;

    bst_insert(root, {10, 15, 5, 12, 20, 13});
    assert(soln.inorderSuccessor(root, bst_find(root, 10)) == bst_find(root, 12));
    assert(soln.inorderSuccessor(root, bst_find(root, 5)) == bst_find(root, 10));
    assert(soln.inorderSuccessor(root, bst_find(root, 15)) == bst_find(root, 20));
    assert(soln.inorderSuccessor(root, bst_find(root, 12)) == bst_find(root, 13));
    assert(soln.inorderSuccessor(root, bst_find(root, 13)) == bst_find(root, 15));
    assert(soln.inorderSuccessor(root, bst_find(root, 20)) == nullptr);
}

int main(int argc, char** argv) {
    test_in_order_succ();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
