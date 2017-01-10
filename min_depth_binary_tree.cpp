// Leetcode: https://leetcode.com/problems/minimum-depth-of-binary-tree/
// Given a binary tree, find its minimum depth.
// The min. depth is the number of nodes along the shortest path from the root to the nearest leaf .

// Brute Force: Traverse the tree (e.g., pre-order), return the min depth. O(n) time and O(h) space.

#include <vector>
#include <iostream>
#include <assert.h>

// Leetcode definition of a tree node
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// Accepted. 9ms. Beats 42.85% of submissions, ties 57.15% of submissions
class Solution {
public:
    int minDepth(TreeNode* root) {
        if (root == nullptr) { return 0; }
        
        if (root->left == nullptr && root->right == nullptr) {
            // Leaf node
            return 1;
        } else if (root->left == nullptr) {
            // No left subtree, recurse on right subtree 
            return 1 + minDepth(root->right);
        } else if (root->right == nullptr) {
            // No right subtree, recurse on left subtree
            return 1 + minDepth(root->left);
        } else {
            // Recurse on both subtrees, return the depth of the shorter one 
            return 1 + std::min(minDepth(root->left), minDepth(root->right));
        }
    }
};

// No testing included, the algorithm is fairly simple, and all leetcode test cases pass.

int main(int argc, char** argv) {
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
