// Leetcode: https://leetcode.com/problems/merge-two-binary-trees/
// Perform a 'merge' of two binary trees.

#include <iostream>
#include <assert.h>
#include "tree_node.h"

// Accepted. 28ms. Beats 94.33% of submissions.
class Solution {
public:
  void merge_trees(TreeNode*& new_tree, TreeNode* t1, TreeNode* t2) {
    if (t1 == nullptr && t2 == nullptr) { return; }
    if (t1 != nullptr && t2 != nullptr) {
      new_tree = new TreeNode(t1->val + t2->val);
      merge_trees(new_tree->left, t1->left, t2->left);
      merge_trees(new_tree->right, t1->right, t2->right);
    }
    if (t1 != nullptr && t2 == nullptr) {
      new_tree = new TreeNode(t1->val);
      merge_trees(new_tree->left, t1->left, nullptr);
      merge_trees(new_tree->right, t1->right, nullptr);
    }
    if (t1 == nullptr && t2 != nullptr) {
      new_tree = new TreeNode(t2->val);
      merge_trees(new_tree->left, nullptr, t2->left);
      merge_trees(new_tree->right, nullptr, t2->right);
    }
  }

  TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2) {
    TreeNode* new_tree = nullptr;
    merge_trees(new_tree, t1, t2);
    return new_tree;
  }
};

int main(int argc, char** argv) {
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
