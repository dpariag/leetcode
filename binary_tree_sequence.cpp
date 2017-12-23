// Leetcode: https://leetcode.com/problems/binary-tree-longest-consecutive-sequence/description/
// Given a binary tree, find the length of the longest path that follows parent-child pointers,
// and consists of consecutive numbers.

// Brute Force: Generate all possible paths through the tree, determine which have consecutive elems.
// Better: Perform a pre-order traversal tracking the length of the current and longest path so far.

#include <vector>
#include <iostream>
#include <assert.h>
#include "tree_node.h"

// Accepted. 22ms. Beats 85.83% of submissions, ties 9.98% of submissions.
class Solution {
public:

    // Pre-order traversal, tracking the length of the current and longest path
    void find_path(TreeNode* root, TreeNode* parent, int cur_len, int& longest) {
        if (root == nullptr) { return; }

        if (parent == nullptr || parent->val == (root->val - 1)) {
            ++cur_len;            
        } else {
            cur_len = 1;
        }

        longest = std::max(longest, cur_len);
        find_path(root->left, root, cur_len, longest);
        find_path(root->right, root, cur_len, longest);
    }

    int longestConsecutive(TreeNode* root) {
        int longest = 0;
        find_path(root, nullptr, 0, longest);
        return longest;
    }
};

int main(int argc, char** argv) {
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
