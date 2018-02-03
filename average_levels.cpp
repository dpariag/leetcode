// Leetcode: https://leetcode.com/problems/average-of-levels-in-binary-tree/description/
// Given a non-empty binary tree, return the average value of the nodes on each level in the form of an array.

// Approach: Traverse the tree, tracking level as we go. For each node, increment the sum
// and count of nodes at that level. A final pass calculates averages. O(n) time, O(h) space.

#include <vector>
#include <iostream>
#include <assert.h>
#include "tree_node.h"

struct SumCount {
    int64_t sum = 0;
    int64_t count = 0;
    SumCount(int s, int c): sum(s), count(c) {}
};
using LevelCounts = std::vector<SumCount>;

// Accepted. 17ms. Beats 37.68% of submissions, ties < 1% of submissions.
class Solution {
public:

    void traverse(TreeNode* node, LevelCounts& level_counts, int cur_level) {
        if (node == nullptr) { return; }

        if (cur_level == level_counts.size()) {
            level_counts.emplace_back(0,0);
        }
        level_counts[cur_level].sum += node->val;
        level_counts[cur_level].count += 1;

        traverse(node->left, level_counts, cur_level+1);
        traverse(node->right, level_counts, cur_level+1);
    }

    std::vector<double> averageOfLevels(TreeNode* root) {
        LevelCounts level_counts;
        traverse(root, level_counts, 0);

        std::vector<double> averages(level_counts.size(), 0.0);
        for (int i = 0; i < level_counts.size(); ++i) {
            averages[i] = double(level_counts[i].sum) / double(level_counts[i].count);            
        }
        return averages;
    }
};

int main(int argc, char** argv) {
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}