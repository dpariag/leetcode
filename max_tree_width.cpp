// Leetcode: https://leetcode.com/problems/maximum-width-of-binary-tree/description/
// Given a binary tree, calculate the tree's maximum width over all levels. The width of a level 
// is the distance between the leftmost and rightmost non-null nodes (including null nodes).

// Brute Force:
// Better: In-order traversal, storing positions of leftmost and rightmost nodes in each level.
// O(n) time and O(logN) space.

#include <vector>
#include <iostream>
#include <assert.h>
#include "tree_node.h"

const int int_min = std::numeric_limits<int>::min();
const int int_max = std::numeric_limits<int>::max();
using Widths = std::vector<std::pair<int,int>>; 

// Accepted. 6ms. Beats 33.37% of submissions, ties 58.53% of submissions.
class Solution {
public:
    int widthOfBinaryTree(TreeNode* root) {
        Widths widths;
        find_tree_width(root, widths, 0, 0);

        int max = 0;
        for (auto& w : widths) {
            max = std::max(max, w.second - w.first + 1);
        }
        return max;
    }

    void find_tree_width(const TreeNode* root, Widths& widths, int level, int position) {
        if (root == nullptr) { return; }
        if (level >= widths.size()) { widths.emplace_back(std::pair<int,int>(int_max, int_min)); }

        find_tree_width(root->left, widths, level+1, position*2);

        widths[level].first = std::min(widths[level].first, position);
        widths[level].second = std::max(widths[level].second, position);

        find_tree_width(root->right, widths, level+1, 1+position*2);
    }
};

bool test_tree_width(std::vector<int> values, int expected_width) {
    Solution soln;
    TreeNode* root = nullptr;

    bst_insert(root, values);
    auto width = soln.widthOfBinaryTree(root);
    return width == expected_width;
}

void test_tree_width() {
    assert(test_tree_width({}, 0));
    assert(test_tree_width({1}, 1));
    assert(test_tree_width({11,10}, 1));
    assert(test_tree_width({11,10,12}, 2));
    assert(test_tree_width({11,10,12,14}, 2));
    assert(test_tree_width({11,10,12,13,14,1}, 4));
    assert(test_tree_width({11,10,15,13,14,1}, 3));
}

int main(int argc, char** argv) {
    test_tree_width();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
