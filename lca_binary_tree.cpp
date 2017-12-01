// Leetcode: https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/description/
// Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in the tree.
// The lowest common ancestor of nodes v and w is the lowest node in T that has both v and w as descendants 
// (a node to be a descendant of itself)

// Approach: Perform a post-order traversal of the tree, returning the first node whose subtrees hold both p and q.

#include <vector>
#include <iostream>
#include <assert.h>
#include "tree_node.h"

// Accepted. 13ms. Beats 46.74% of submisssions, ties 40.21% of submissions
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == nullptr || root == p || root == q) { 
            // Found one node. The other node is either in one of it's subtrees or 
            // will be in a subtree of an ancestor
            return root; 
        }

        auto left = lowestCommonAncestor(root->left, p, q);
        auto right = lowestCommonAncestor(root->right, p, q);

        if (left != nullptr && right != nullptr) {
            // Found both nodes in subtrees
            return root;
        }
        return (left != nullptr) ? left : right;
    }
};

void test_lca() {
    Solution soln;
    TreeNode* root = nullptr;

    bst_insert(root, {10, 15, 5, 12, 20, 13});
    assert(soln.lowestCommonAncestor(root, bst_find(root, 5), bst_find(root, 10)) == bst_find(root, 10));
    assert(soln.lowestCommonAncestor(root, bst_find(root, 15), bst_find(root, 10)) == bst_find(root, 10));
    assert(soln.lowestCommonAncestor(root, bst_find(root, 12), bst_find(root, 20)) == bst_find(root, 15));
    assert(soln.lowestCommonAncestor(root, bst_find(root, 13), bst_find(root, 20)) == bst_find(root, 15));
    assert(soln.lowestCommonAncestor(root, bst_find(root, 13), bst_find(root, 5)) == bst_find(root, 10));
    assert(soln.lowestCommonAncestor(root, bst_find(root, 13), bst_find(root, 12)) == bst_find(root, 12));
    assert(soln.lowestCommonAncestor(root, bst_find(root, 5), bst_find(root, 20)) == bst_find(root, 10));

}

int main(int argc, char** argv) {
    test_lca();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
