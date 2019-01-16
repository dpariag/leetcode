// Leetcode: https://leetcode.com/problems/check-completeness-of-a-binary-tree/
// Given a binary tree, determine if it is a complete binary tree.

// Brute Force: Do a level traversal of the tree, look for gaps or nulls in in level traversal. O(2^n) space.
// Better: Pre-order traversal, recording nulls and gaps in each level
// Acceptance: 44.8% 

#include <iostream>
#include <assert.h>
#include "tree_node.h"

struct LevelData {
  int num_nodes = 0;
  int has_null = false;
  int has_gap = false;
  LevelData() = default;
};
using Levels = std::vector<LevelData>;

// Accepted. 4ms. Faster than 100% of cpp submissions.
class Solution {
public:
    void pre_order(TreeNode* root, int cur_level, Levels& levels) {
      if (cur_level >= levels.size()) { levels.emplace_back(LevelData()); }
      if (root == nullptr) { 
        levels[cur_level].has_null = true;
        return; 
      } 
      
      if (levels[cur_level].has_null) {
        levels[cur_level].has_gap = true;
        levels[cur_level].num_nodes++;
      }
      pre_order(root->left, cur_level+1, levels); 
      pre_order(root->right, cur_level+1, levels); 
    }

    bool isCompleteTree(TreeNode* root) {
      Levels levels;
      levels.reserve(100);

      pre_order(root, 0, levels);
      int num_levels = levels.size();
      int last_level = num_levels - 2;
      for (int i = 0; i < last_level; ++i) {
        if (i < last_level && levels[i].has_null) return false;
      }
      if (levels[last_level].has_gap) return false;
      return true;
    }
};

bool test_is_complete(std::vector<int> node_values, bool expected) {
  Solution soln;
  TreeNode* tree = nullptr;
  bst_insert(tree, node_values);
  return soln.isCompleteTree(tree) == expected;
}

void test_is_complete() {
  assert(test_is_complete({10}, true));
  assert(test_is_complete({10,5}, true));
  assert(test_is_complete({10,15}, false));
  assert(test_is_complete({10,5,15}, true));
  assert(test_is_complete({10,5,15,4}, true));
  assert(test_is_complete({10,5,15,6}, false));
  assert(test_is_complete({10,5,6}, false));
}

int main(int argc, char** argv) {
  test_is_complete();
  std::cout << argv[0] + 2 << "...OK!" << std::endl;
  return 0;
}
