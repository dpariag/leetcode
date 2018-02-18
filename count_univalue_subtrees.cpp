// Leetcode: https://leetcode.com/problems/count-univalue-subtrees/description/

// Approach: Post-order traversal, returning whether the subtree is univalue and if so, it's value

#include <vector>
#include <iostream>
#include <assert.h>
#include "tree_node.h"

// Accepted. 5ms. Beats 14.10% of submissions, ties < 1% of submissions.
class Solution {
public:
    bool is_univalue(TreeNode* root, int& value, int& count) {
        if (root->left == nullptr && root->right == nullptr) {
            ++count, value = root->val;
            return true;
        }

        bool left_is_unival = false, right_is_unival = false;
        int left_val, right_val;
        if (root->left != nullptr) {
            left_is_unival = is_univalue(root->left, left_val, count);
        }

        if (root->right != nullptr) {
            right_is_unival = is_univalue(root->right, right_val, count);
        }

        if (left_is_unival && right_is_unival) {
            if (left_val == root->val && right_val == root->val) {
                ++count, value = root->val;
                return true;
            }
        } else if (left_is_unival && root->right == nullptr) {
            if (left_val == root->val) {
                ++count, value = root->val;
                return true;
            }
        } else if (right_is_unival && root->left == nullptr) {
            if (right_val == root->val) {
                ++count, value = root->val;
                return true;
            }
        }
        return false;
    }

    int countUnivalSubtrees(TreeNode* root) {
        int count = 0, value = 0;
        if (root != nullptr) {
            is_univalue(root, value, count);
        }        
        return count;
    }
};

int main(int argc, char** argv) {
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
