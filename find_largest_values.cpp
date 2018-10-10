// Leetcode: https://leetcode.com/problems/find-largest-value-in-each-tree-row/description/
// Find the largest value in each row of a binary tree

// Approach: Do a pre-order traversal of the tree, tracking the level of each node visited.
// Track the max node seen at each level in a vector. O(n) time and O(h) space.

#include <vector>
#include <iostream>
#include <assert.h>
#include "tree_node.h"

// Accepted. 8ms. Beats 99.54% of submissions.
class Solution {
public:

  void largest_values(TreeNode* root, std::vector<int>& values, int depth) {
    if (root == nullptr) return;
    if (values.size() <= depth) values.emplace_back(std::numeric_limits<int>::min());

    values[depth] = std::max(values[depth], root->val);
    largest_values(root->left, values, depth + 1);
    largest_values(root->right, values, depth + 1);
  }


  std::vector<int> largestValues(TreeNode* root) {
    std::vector<int> values;
    largest_values(root, values, 0);
    return values; 
  }
};

void test_largest_values() {
  Solution soln;
  TreeNode* root = nullptr;
  bst_insert(root, {10, 5, 15, 1, 6, 11, 16});
  assert(soln.largestValues(root) == std::vector<int>({10, 15, 16}));
}

int main(int argc, char** argv) {
  test_largest_values();
  std::cout << argv[0] + 2 << "...OK!" << std::endl;
  return 0;
}
