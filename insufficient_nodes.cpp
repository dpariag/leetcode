// Leetcode: https://leetcode.com/problems/insufficient-nodes-in-root-to-leaf-paths/
// A node is insufficient if every root to leaf path intersecting the node has sum strictly less than limit.
// Delete all insufficient nodes simultaneously, and return the root of the resulting binary tree.

// Approach: A post-order traversal of the tree. A node is insufficient if both it's children are.
// Delete an insufficient child, and then return the status of this node to it's parent. O(n) time.
// Acceptance: 43.4

#include <iostream>
#include <assert.h>
#include "tree_node.h"

// Accepted. 44ms. Faster than 80.53% of cpp submissions.
class Solution {
public:
  inline bool is_leaf(TreeNode* node) {
    return node != nullptr && node->left == nullptr && node->right == nullptr;
  }

  bool is_insufficient(TreeNode* node, int limit, int sum) {
    if (node == nullptr) { return true; }

    sum += node->val;
    if (is_leaf(node)) {
      return sum < limit;
    }

    // Not a leaf
    auto left_insufficient = is_insufficient(node->left, limit, sum);
    auto right_insufficient = is_insufficient(node->right, limit, sum);
    
    if (left_insufficient) { 
      delete node->left; 
      node->left = nullptr;
    }
    if (right_insufficient) { 
      delete node->right; 
      node->right = nullptr;
    }
    return left_insufficient && right_insufficient;
  }

  TreeNode* sufficientSubset(TreeNode* root, int limit) {
    int sum{0};
    auto root_insufficient = is_insufficient(root, limit, sum);
    if (root_insufficient) {
      return nullptr;
    }
    return root;
  }
};

int main(int argc, char** argv) {
  std::cout << argv[0] + 2 << "...OK!" << std::endl;
  return 0;
}
