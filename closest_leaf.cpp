// Leetcode: https://leetcode.com/problems/closest-leaf-in-a-binary-tree/description/
// Given a binary tree containing unique values, and a target key k, find the value of the nearest 
// leaf node to target k in the tree. The tree has at most 1000 nodes, with keys in range [1, 1000]

// Approach: Perform two traversals of the tree. First a post-order traversal finds the nearest leaf
// that is a child. Then a pre-order traversal compares to the nearest leaf accessible from a node's
// parent. Use a vector indexed by node value to cache data for each node.

#include <vector>
#include <iostream>
#include <assert.h>
#include "tree_node.h"

struct NodeData {
  int parent_val = -1;
  int nearest_leaf = -1;
  int distance = std::numeric_limits<int>::max() - 1; // Minimum distance to nearest_leaf
};

using TreeData = std::vector<NodeData>;

// Accepted. 8ms. Beats 100% of cpp submissions.
class Solution {
public:
  void post_order(TreeNode* root, int parent_val, TreeData& tree_data) {
    if (root == nullptr) { return; }

    auto val = root->val;
    tree_data[val].parent_val = parent_val;
    if (root->left == nullptr && root->right == nullptr) { 
      tree_data[val].distance = 0;
      tree_data[val].nearest_leaf = root->val;
      return;
    } 

    if (root->left != nullptr) {
      post_order(root->left, val, tree_data);
      tree_data[val].distance = 1 + tree_data[root->left->val].distance;
      tree_data[val].nearest_leaf = tree_data[root->left->val].nearest_leaf;
    }
    if (root->right != nullptr) {
      post_order(root->right, val, tree_data);
      if (tree_data[root->right->val].distance + 1 < tree_data[val].distance) {
        tree_data[val].distance = 1 + tree_data[root->right->val].distance;
        tree_data[val].nearest_leaf = tree_data[root->right->val].nearest_leaf;
      }
    }
  }

  void pre_order(TreeNode* root, int parent_val, TreeData& tree_data) {
    if (root == nullptr) { return; }
   
    auto val = root->val; 
    if (parent_val != -1) {
      if (tree_data[parent_val].distance + 1 < tree_data[val].distance) {
        tree_data[val].distance = 1 + tree_data[parent_val].distance;
        tree_data[val].nearest_leaf = tree_data[parent_val].nearest_leaf;
      }
    }
    pre_order(root->left, val, tree_data);
    pre_order(root->right, val, tree_data);
  }

  int findClosestLeaf(TreeNode* root, int k) {
    TreeData tree_data(1001);
    post_order(root, 0, tree_data); // Use zero for the root's parent value
    pre_order(root, 0, tree_data);
    return tree_data[k].nearest_leaf;
  }
};

void test_closest_leaf() {
  Solution soln;
  TreeNode* tree = nullptr;
  bst_insert(tree, {10, 8, 20, 11, 30, 12, 25, 13, 24, 14, 23});

  assert(soln.findClosestLeaf(tree, 14) == 14);
  assert(soln.findClosestLeaf(tree, 23) == 23);
  assert(soln.findClosestLeaf(tree, 13) == 14);
  assert(soln.findClosestLeaf(tree, 24) == 23);
  assert(soln.findClosestLeaf(tree, 12) == 14);
  assert(soln.findClosestLeaf(tree, 8) == 8);
  assert(soln.findClosestLeaf(tree, 10) == 8);
  assert(soln.findClosestLeaf(tree, 20) == 8);
}

int main(int argc, char** argv) {
  test_closest_leaf();
  std::cout << argv[0] + 2 << "...OK!" << std::endl;
  return 0;
}
