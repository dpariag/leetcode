// Leetcode: https://leetcode.com/problems/split-array-largest-sum/description/
// Given an array of non-negative integers and an integer m, you can split the array into m non-empty subarrays. 
// Write an algorithm to minimize the largest sum among these m subarrays.

// Brute Force: Recursively try all possible splits, track smallest max subarray sum. O(n^m) time.
// Better: Table driven DP. table[k][i] is the min of max subarray sums over num[0..i] using k splits.

#include <vector>
#include <limits>
#include <iostream>
#include <assert.h>

using Table = std::vector<std::vector<int>>;

// Accepted. 119ms. Beats 6.08% of submissions, ties < 1% of submissions
class Solution {
public:
    int splitArray(const std::vector<int>& nums, int m) {
        if (nums.empty()) { return 0; }

        // table[k][i] = {min of max subarray sums over nums[0..i] using k splits}
        Table table(m+1, std::vector<int>(nums.size(), -1));

        // First row (zero splits) is just prefix sums
        table[0][0] = nums[0];
        for(int i = 1; i < nums.size(); ++i) {
            table[0][i] = table[0][i-1] + nums[i];
        }

        // Fill in table for k = 1,2,m-1 splits
        for (int k = 1; k < m; ++k) {
            // i doesn't have to start at 0. Doing k splits requires at least k+1 entries
            for (int i = k; i < nums.size(); ++i) {
                // Calculate table[k][i]
                int min = std::numeric_limits<int>::max();
                // Try doing the last split at k, k+1,...,i
                for (int split = k; split <= i; ++split) {
                    // Use prefix sums in row 0 to calculate sum to the right of the split
                    int right_sum = table[0][i] - table[0][split-1];
                    // Calculate max sum over left and right sides
                    int max_sum = std::max(right_sum, table[k-1][split-1]);
                    min = std::min(min, max_sum);
                }
                table[k][i] = min; // min of max sums
            }
        }
        return table[m-1].back();
    }
};

void test_split_array() {
    Solution soln;

    assert(soln.splitArray({7,2,5,10,8}, 2) == 18);
    assert(soln.splitArray({7,2,5,10,8}, 3) == 14);
}

int main(int argc, char** argv) {
    test_split_array();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
