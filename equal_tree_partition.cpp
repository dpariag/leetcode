// Leetcode: https://leetcode.com/problems/equal-tree-partition/submissions/

// Brute Force: Repeatedly remove each edge of the tree and re-calculate sums. O(n^2) time.
// Better: Traverse the tree once to calculate the sum of all node values. Traverse a second time to
// calculate the sum of each subtree and compare it to the tree sum. The root node is a special case.
// Acceptance: 37.2% 

#include <iostream>
#include <unordered_map>
#include <assert.h>
#include "tree_node.h"

// Accepted. 24ms. Faster than 45.31% of cpp submissions.
class Solution {
public:
  void pre_order(TreeNode* root, int64_t& sum) {
    if (root == nullptr) { return; }
    sum += root->val;
    pre_order(root->left, sum);
    pre_order(root->right, sum);
  }

  bool find_split(TreeNode* parent, TreeNode* root, int64_t tree_sum, int64_t& parent_sum) {
    if (root == nullptr) { return false; }
    
    int64_t subtree_sum = root->val;
    if (find_split(root, root->left, tree_sum, subtree_sum)) { return true; }
    if (find_split(root, root->right, tree_sum, subtree_sum)) { return true; }
    if (subtree_sum * 2 == tree_sum && parent != nullptr) { return true; }
    parent_sum += subtree_sum;
    return false;
  }

  bool checkEqualTree(TreeNode* root) {
    int64_t tree_sum = 0;
    pre_order(root, tree_sum);
    if (tree_sum % 2) { return false; }
    int64_t subtree_sum = 0;
    return find_split(nullptr, root, tree_sum, subtree_sum);
  }
};

bool test_find_split(std::vector<int> tree_values, bool expected) {
  Solution soln;
  TreeNode* root = nullptr;
  bst_insert(root, tree_values);
  return soln.checkEqualTree(root) == expected;
}

void test_find_split() {
  assert(test_find_split({0,-1,1}, false));
  assert(test_find_split({10,8,6,2,13,13}, true));
}

int main(int argc, char** argv) {
  test_find_split();
  std::cout << argv[0] + 2 << "...OK!" << std::endl;
  return 0;
}
