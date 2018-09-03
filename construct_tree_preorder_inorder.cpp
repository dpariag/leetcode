// Leetcode: https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/description/
// Given preorder and inorder traversal of a tree, construct the binary tree.

// Approach: The preorder traversal gives the next node to be inserted. The inorder traversal
// determines if that node is inserted on the left or the right subtree

#include <vector>
#include <iostream>
#include <unordered_map>
#include <assert.h>
#include "tree_node.h"

using Traversal = std::vector<int>;
using TraversalMap = std::unordered_map<int, int>;

// Accepted. 12ms. Beats 69.42% of cpp submissions.
class Solution {
public:
  void build(TreeNode*& node, const Traversal& preorder, const Traversal& inorder, 
             TraversalMap& map, int& pre_idx, int in_start, int in_end) {
    auto key = preorder[pre_idx];
    auto in_idx = map[key];
    if (in_idx < in_start || in_idx > in_end) { return; }

    node = new TreeNode(key);
    ++pre_idx;

    build(node->left, preorder, inorder, map, pre_idx, in_start, in_idx-1);
    build(node->right, preorder, inorder, map, pre_idx, in_idx+1, in_end);
  } 

  TreeNode* buildTree(const Traversal& preorder, const Traversal& inorder) {
    TreeNode* tree = nullptr;
    if (preorder.empty() || inorder.empty()) { return nullptr; }

    TraversalMap inorder_indices;
    for (int i = 0; i < inorder.size(); ++i) {
      inorder_indices[inorder[i]] = i;
    }
    int pre_idx = 0;
    build(tree, preorder, inorder, inorder_indices, pre_idx, 0, inorder.size() - 1);
    return tree;
  }
};

void test_build_tree() {
  Solution soln;
  auto tree = soln.buildTree({3,9,20,15,7}, {9,3,15,20,7});

  assert(tree->val == 3);
  assert(tree->left->val == 9);
  assert(tree->left->left == nullptr);
  assert(tree->left->right == nullptr);
  assert(tree->right->val == 20);
  assert(tree->right->left->val == 15);
  assert(tree->right->right->val == 7);
}

int main(int argc, char** argv) {
  test_build_tree();
  std::cout << argv[0] + 2 << "...OK!" << std::endl;
  return 0;
}
