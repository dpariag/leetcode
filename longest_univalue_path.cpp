// Leetcode: https://leetcode.com/problems/longest-univalue-path/description/
// Given a binary tree, find the length of the longest path in which each node has the same value. 
// This path may or may not pass through the root.

// Approach: Perform a post-order traversal. When visiting a node, examine the longest univalue
// path involving that node and either one or both of it's children. 

#include <vector>
#include <iostream>
#include <assert.h>
#include "tree_node.h"

// Accepted. 63ms. Beats 73.27% of submissions, ties 9.63% of submissions.
class Solution {
public:
    int find_longest(TreeNode* root, int& longest) {
        if (root == nullptr) { return 0; }
  
        int left = 0, right = 0;
        if (root->left != nullptr) {
            left = find_longest(root->left, longest);
            left += (root->left->val == root->val) ? 1 : -left;
        }

        if (root->right != nullptr) {
            right = find_longest(root->right, longest);
            right += (root->right->val == root->val) ? 1 : -right;
        }

        int local_max = std::max(left, right); 
        longest = std::max(longest, local_max);
        
        if (root->left != nullptr && root->right != nullptr &&
            root->left->val == root->val && root->right->val == root->val) {
            longest = std::max(longest, left + right);
        }
        return local_max;
    }

    int longestUnivaluePath(TreeNode* root) {
        int longest = 0;
        find_longest(root, longest);
        return longest;
    }
};

int main(int argc, char** argv) {
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
