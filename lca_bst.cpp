// Leetcode:https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/description/
// Given a binary search tree (BST), find the lowest common ancestor (LCA) of two given nodes in 
// the BST. A node is allowed to be a descendant of itself.

// Brute Force: Usual LCA algorithm, based on pre-order traversal. O(n) time. 
// Better: Use the BST property to eliminate one side of the tree at each step. O(h) time.

#include <vector>
#include <iostream>
#include <assert.h>
#include "tree_node.h"

// Accepted. 26ms. Beats 40.72% of submissions, ties 50.05% of submissions.
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        while (root != nullptr) {
            if (p-> val > root->val && q->val > root->val) {
                root = root->right;
            } else if (p->val < root->val && q->val < root->val) {
                root = root->left;
            } else if ((p->val < root->val && q->val > root->val) ||
                       (q->val < root->val && p->val > root->val) ||
                       (root->val == p->val || root->val == q->val)) {
                break;
            }
        }
        return root;
    }
};


int main(int argc, char** argv) {
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
