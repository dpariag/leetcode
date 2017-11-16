// Leetcode: https://leetcode.com/problems/path-sum/#/description
// Given a binary tree and a number, return all root-to-leaf paths whose sum equals the given number

// Brute Force: Generate all possible paths, check which are root->leaf and have the right sum.
// Better: Perform a pre-order traversal, tracking the path sum as we go. O(n) time and O(logN) space.

#include <vector>
#include <iostream>
#include <assert.h>
#include <algorithm>
#include "tree_node.h"

using Path = std::vector<int>;
using Paths = std::vector<Path>;

// Accepted. 9ms. Beats 72.55% of submissions, ties 27.45% of submissions.
class Solution {
public:
    Paths pathSum(TreeNode* root, int sum) {
        Paths paths;
        Path cur_path;
        find_paths(root, sum, cur_path, paths);
        return paths;
    }

    void find_paths(TreeNode* root, int sum, Path& cur_path, Paths& paths) {
        if (root == nullptr) { return; }

        sum -= root->val;
        cur_path.emplace_back(root->val);
        if (root->left == nullptr && root->right == nullptr && sum == 0) {
            paths.push_back(cur_path);
            cur_path.pop_back();
            return;
        }
        if (root->left != nullptr) {
            find_paths(root->left, sum, cur_path, paths); 
        }
        if (root->right != nullptr) {
            find_paths(root->right, sum, cur_path, paths);
        }
        cur_path.pop_back();
    }
};

bool test_path_sum(const std::vector<int>& values, int sum, Paths expected_paths) {
    Solution soln;
    TreeNode* tree = nullptr;
    bst_insert(tree, values);
   
    auto paths = soln.pathSum(tree, sum);
    std::sort(paths.begin(), paths.end());
    std::sort(expected_paths.begin(), expected_paths.end());
    return paths == expected_paths;
}

void test_path_sum() {
    assert(test_path_sum({10,5,15,1,11}, 16, {{10,5,1}}));
    assert(test_path_sum({10,5,15,1,11}, 36, {{10,15,11}}));
    assert(test_path_sum({10,5,15,1,11,8}, 23, {{10,5,8}}));
}

int main(int argc, char** argv) {
    test_path_sum();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
