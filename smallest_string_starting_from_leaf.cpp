// Leetcode: https://leetcode.com/problems/smallest-string-starting-from-leaf/
// Given the root of a binary tree, each node has a value from 0 to 25 representing the letters 'a' to 'z': a 
// value of 0 represents 'a', a value of 1 represents 'b', and so on.
// Find the lexicographically smallest string that starts at a leaf of this tree and ends at the root.

// Brute Force: Generate all root->leaf strings, sort & return the lexicographically smallest string. O(nlogn) time.
// Better: Pre-order traversal (post-order won't work), tracking the smallest root->leaf string. O(n) time.
// Acceptance: 45.0

#include <iostream>
#include <string>
#include <assert.h>
#include "tree_node.h"

// Accepted. 8ms. Faster than 93.78% of C++ submissions
class Solution {
public:
    inline char to_char(int i) { return 'a' + i; }

    void pre_order(TreeNode* root, std::string& str, std::string& min) {
      if (root == nullptr) { return; }
      
      auto ch = to_char(root->val);
      str.push_back(ch);
      if (root->left == nullptr && root->right == nullptr) {
        // At a leaf
        auto r = str;
        std::reverse(r.begin(), r.end());
        if (min.empty() || r < min) {
          min = r;
        }
      } else {
        // Not a leaf
        pre_order(root->left, str, min);
        pre_order(root->right, str, min);
      }
      str.pop_back();
    }

    std::string smallestFromLeaf(TreeNode* root) {
      std::string smallest, cur;
      pre_order(root, cur, smallest);
      return smallest;
    }
};

bool test_smallest_from_leaf(TreeNode* root, std::string expected) {
  Solution soln;
  return soln.smallestFromLeaf(root) == expected; 
}

void test_smallest_from_leaf() {
  TreeNode* root = nullptr;
  
  in_order_insert(root, {3,1,4,0,3,2,4});
  // a -> {b,c}
  // b -> {d,e}
  // c -> {d,e} 
  assert(test_smallest_from_leaf(root, "dba"));

  delete root;
  root = nullptr;
  in_order_insert(root, {1,1,3,25,0,3,2});
  // z -> {b,d}
  // b -> {b,d}
  // d -> {a,c}
  assert(test_smallest_from_leaf(root, "adz"));

  delete root;
  root = nullptr;
  root = new TreeNode(2);
  root->left = new TreeNode(2);
  root->left->right = new TreeNode(1);
  root->left->right->left = new TreeNode(0);
  root->right = new TreeNode(1);
  root->right->left = new TreeNode(0);
  assert(test_smallest_from_leaf(root, "abc"));  
}

int main(int argc, char** argv) {
  test_smallest_from_leaf();
  std::cout << argv[0] + 2 << "...OK!" << std::endl;
  return 0;
}
