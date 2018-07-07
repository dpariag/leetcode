// Leetcode: https://leetcode.com/problems/maximum-binary-tree/description/

// Brute Force: Scan for max, make it the root and recurse on left and right halves of the array. O(n*logn) time.
// Better: Use a stack to process the array. Items smaller than the top of the stack are pushed on.
// If the incoming item is larger than the top of the stack, pop the stack and build the tree.
// The popped item either belongs to the incoming node, or the new stack.top()

#include "tree_node.h"
#include <stack>
#include <iostream>
#include <assert.h>

// Accepted: 36ms. Beats 100% of submissions.
class Solution {
public:
    TreeNode* constructMaximumBinaryTree(std::vector<int>& nums) {
        std::stack<TreeNode*> stack;

        for (int i = 0; i < nums.size(); ++i) {
            TreeNode* new_node = new TreeNode(nums[i]);
            if (stack.empty() || (new_node->val < stack.top()->val)) {
                // Items smaller than the stack top get pushed on
                stack.push(new_node);
            } else {
                // Incoming node is larger than stack.top()
                while (!stack.empty() && new_node->val > stack.top()->val) {
                    auto prev = stack.top();
                    stack.pop();
                    if (!stack.empty()) {
                        if (new_node->val > stack.top()->val) {
                            // New node is bigger, so prev is the right child of top
                            stack.top()->right = prev;
                        } else {
                            // New node is smaller, so prev is it's left child
                            new_node->left = prev; 
                            break;
                        }
                    } else {
                        new_node->left = prev;
                    }
                }
                stack.push(new_node);
            }
        }
        
        while (stack.size() > 1) {
            auto prev = stack.top();
            stack.pop();
            stack.top()->right = prev;
        }

        return stack.top();
    }
};

void test_max_binary_tree() {
    std::vector<int> nums{10,40,20,50,30,5};
    Solution soln;

    auto tree = soln.constructMaximumBinaryTree(nums);
    assert(tree->val == 50);
    assert(tree->left->val == 40);
    assert(tree->right->val == 30);
    assert(tree->left->left->val == 10);
    assert(tree->left->right->val == 20);
    assert(tree->right->right->val == 5);
    assert(tree->left->left->left == nullptr);
    assert(tree->left->left->right == nullptr);
    assert(tree->left->right->left == nullptr);
    assert(tree->left->right->right == nullptr);
}

int main(int argc, char** argv) {
    test_max_binary_tree();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
