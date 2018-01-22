// Leetcode: https://leetcode.com/problems/find-mode-in-binary-search-tree/description/
// Given a BST with duplicates, find all the mode(s) (the most frequently occurred element) in the BST.

// Brute Force: Traverse the BST counting elements in a hash map. Dump the hash map to an array, 
// sort it, and then scan to find modes. O(n*logn)
// Better: The BST is already in sorted order! Traverse BST in-order tracking element counts and max count
// Traverse again counting elements and collecting any element whose count equals the max. O(n) time.

#include <vector>
#include <iostream>
#include <algorithm>
#include <assert.h>
#include "tree_node.h"

// Accepted. 15ms. Beats 70.87% of submissions, ties 2.10% of submissions.
class Solution {
public:
    void find_mode(TreeNode* root, int& cur, int& count, int& max_count) {
        if (root == nullptr) { return; }

        // Recurse left
        find_mode(root->left, cur, count, max_count);

        if (root->val == cur) { 
            ++count;            
        } else {
            cur = root->val, count = 1;
        }
        max_count = std::max(count, max_count);

        // Recurse right
        find_mode(root->right, cur, count, max_count);
    }

    void collect_modes(TreeNode* root, int& cur, int& count, int max_count, std::vector<int>& modes) {
        if (root == nullptr) { return; }

        collect_modes(root->left, cur, count, max_count, modes);
        if (root->val == cur) {
            ++count;
        } else {
            cur = root->val, count = 1;
        }

        if (count == max_count) {
            modes.emplace_back(root->val);
        }
        collect_modes(root->right, cur, count, max_count, modes);
    }

    std::vector<int> findMode(TreeNode* root) {
        int cur = 0, count = 0, max_count = 0;

        // Find the count of the most common element(s)
        find_mode(root, cur, count, max_count);

        // max_count is now the count of all modes
        std::vector<int> modes;
        cur = 0, count = 0;
        collect_modes(root, cur, count, max_count, modes);
        return modes;
    }
};

bool test_find_modes(std::vector<int> values, std::vector<int> expected) {
    Solution soln;
    TreeNode* root = nullptr;

    bst_insert(root, values);
    auto modes = soln.findMode(root);
    std::sort(expected.begin(), expected.end());
    std::sort(modes.begin(), modes.end());
    return modes == expected;
}

void test_find_modes() {
    assert(test_find_modes({100}, {100}));
    assert(test_find_modes({100,100,100}, {100}));
    assert(test_find_modes({100,101,99}, {99,100,101}));
    assert(test_find_modes({100,101,99,101}, {101}));
}

int main(int argc, char** argv) {
    test_find_modes();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
