// Leetcode: https://leetcode.com/problems/convert-sorted-array-to-binary-search-tree/description/
// Given a sorted array, convert it to a height balanced BST (i.e., a BST in which the depth of left
// and right subtrees of a node never differ by more than 1).

// Approach: Choose the middle element as the root, recursively process right and left halves.

#include <vector>
#include <iostream>
#include <assert.h>
#include "tree_node.h"

// Accepted. 13ms. Beats 50.20% of submissions, ties 40.22% of submissions.
class Solution {
public:
    void build_bst(std::vector<int>& nums, int start, int end, TreeNode*& root) {
        if (start > end) { return; } 
        int mid = start + (end - start) / 2; 
        
        root = new TreeNode(nums[mid]);
        build_bst(nums, start, mid-1, root->left);
        build_bst(nums, mid+1, end, root->right);
    }

    TreeNode* sortedArrayToBST(std::vector<int>& nums) {
        TreeNode* root = nullptr;
        build_bst(nums, 0, nums.size()-1, root);
        return root; 
    }
};

bool is_balanced(const TreeNode* root, int& max_height) {
    if (root == nullptr) {
        max_height = 0;
        return true;
    }
    int left_height = 0, right_height = 0;
    if (!is_balanced(root->left, left_height)) { return false; }
    if (!is_balanced(root->right, right_height)) { return false; }

    max_height = std::max(left_height, right_height) + 1;
    return std::abs(left_height - right_height) <= 1;
}

void traverse(TreeNode* root, std::vector<int>& values) {
    if (root == nullptr) { return; }

    traverse(root->left, values);
    values.emplace_back(root->val);
    traverse(root->right, values);
}

bool test_build_bst(std::vector<int> nums) {
    Solution soln;
    
    auto tree = soln.sortedArrayToBST(nums);
    std::vector<int> values;
    traverse(tree, values);
    
    int max_height = 0;
    return values == nums && is_balanced(tree, max_height);
}

void test_build_bst() {
    assert(test_build_bst({10}));
    assert(test_build_bst({5,10}));
    assert(test_build_bst({10,15}));
    assert(test_build_bst({5,10,15}));
    assert(test_build_bst({1,5,6,10,12,15,20}));
}


int main(int argc, char** argv) {
    test_build_bst();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
