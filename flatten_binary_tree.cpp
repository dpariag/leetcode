// Leetcode: https://leetcode.com/problems/flatten-binary-tree-to-linked-list/description/
// Given a binary tree, flatten it to a linked list in-place.

// Brute Force: In-order traversal, appending Nodes to a vector. Build list from vector. 
// O(n) time, O(n+h) space.
// Better: A post-order traversal in which each recursive call returns head and tail pointers
// to the sub-lists. Build list from sublists. O(n) time and O(h) space (recursion).

#include <vector>
#include <iostream>
#include <assert.h>
#include "tree_node.h"

// Accepted. 6ms. Beats 41.55% of submissions, ties 56.84% of submissions.
class Solution {
public:

    void flatten_tree(TreeNode* tree, TreeNode*& head, TreeNode*& tail) {
        if (tree == nullptr) {
            head = nullptr, tail = nullptr;
            return;
        }

        TreeNode* left_head = nullptr, *left_tail = nullptr;
        if (tree->left)
            flatten_tree(tree->left, left_head, left_tail);

        TreeNode* right_head = nullptr, *right_tail = nullptr;
        if (tree->right)
            flatten_tree(tree->right, right_head, right_tail);

        TreeNode* cur_tail = tree;
        if (left_head != nullptr) {
            cur_tail->right = left_head;
            cur_tail->left = nullptr;
            cur_tail = left_tail;
        }

        if (right_head != nullptr) {
            cur_tail->right = right_head; 
            cur_tail->left = nullptr;
            cur_tail = right_tail;
        }

        head = tree;
        tail = cur_tail;
    }

    // Flatten the tree, using right-child pointers as "next" pointers
    void flatten(TreeNode* root) {
        TreeNode* head = root, *tail = root;
        flatten_tree(root, head, tail); 
    }
};

bool test_flatten(std::vector<int> values, std::vector<int> list_order) {
    Solution soln;
    TreeNode* tree = nullptr;

    bst_insert(tree, values);
    soln.flatten(tree);

    TreeNode* cur = tree;
    int i = 0;
    while (i < list_order.size() && cur != nullptr) {
        if (cur->val != list_order[i]) { return false; }
        ++i, cur = cur->right;
    }
    return (cur == nullptr) && (i == list_order.size());
}

void test_flatten() {
    assert(test_flatten({2},{2}));
    assert(test_flatten({2,1},{2,1}));
    assert(test_flatten({2,1,3}, {2,1,3}));
    assert(test_flatten({4,3,5,2,9}, {4,3,2,5,9}));
    assert(test_flatten({4,3,5,2,9,1}, {4,3,2,1,5,9}));
    assert(test_flatten({10,5,15,6,12}, {10,5,6,15,12}));
    assert(test_flatten({10,5,15,4,12}, {10,5,4,15,12}));
    assert(test_flatten({10,5,15,4,17}, {10,5,4,15,17}));
    assert(test_flatten({10,5,15,4,17,12}, {10,5,4,15,12,17}));
}

int main(int argc, char** argv) {
    test_flatten();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
