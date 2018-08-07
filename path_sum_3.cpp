// Leetcode: https://leetcode.com/problems/path-sum-iii/description/

// Brute Force: Generate all possible paths, and compute their sums. O(2^n) time.
// Better: Pre-order traversal using a hash map to store root->cur_node sums. O(n) time.

#include <iostream>
#include <assert.h>
#include <unordered_map>
#include "tree_node.h"

using PathSums = std::unordered_map<int,int>;

// Accepted. 8ms. Beats 99.62% of cpp submissions.
class Solution {
public:
    // Based on a pre-order traversal and using a hash map to store path sums.
    int count_path_sums(TreeNode* root, int cur_sum, int target, PathSums& sums) {
        if (root == nullptr) { return 0; }
       
        int count = 0;
        cur_sum += root->val;
        if (cur_sum == target) ++count;
        auto found = sums.find(cur_sum - target);
        count += found != sums.end() ? found->second : 0;

        ++sums[cur_sum];
        count += count_path_sums(root->left, cur_sum, target, sums);
        count += count_path_sums(root->right, cur_sum, target, sums);
        --sums[cur_sum];
        return count;
    }

    int pathSum(TreeNode* root, int sum) {
        PathSums path_sums;
        return count_path_sums(root, 0, sum, path_sums);
    }
};

int main(int argc, char** argv) {
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
