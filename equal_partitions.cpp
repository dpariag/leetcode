// Leetcode: https://leetcode.com/problems/partition-equal-subset-sum/
// Given a non-empty array (A) containing +ve integers, determine if A can be partitioned into 
// two subsets whose sums are equal. Special notes: A.size() <= 200 and A[i] <= 100 for any i. 

// Brute Force: Generate all 2^n subsets and their sums. Return true iff any pair of subsets have 
// equal sums. O(2^n * n) time and O(2^n) space
// Better: Solve this as a special case of the knapsack problem. The knapsack is of size sum(A)/2.
// An integer's weight is it's value, we ignore value/cost of integers. O(n*sum(A)/2) time and space

// Example: {1,5,5,7,4} --> {1,5,5} and {7,4}
// Example: {1,1,4,4,5,7} --> {1,1,4,5} and {7,4}
// Example: {1,1,1,3} --> {} and {}

#include <vector>
#include <numeric>
#include <iostream>
#include <assert.h>

using Table = std::vector<std::vector<int>>;

// Accepted. 48ms. Beats 57.98% of submissions, ties 2.48% of submissions.
class Solution {
public:
    bool canPartition(const std::vector<int>& nums) {
        auto sum = std::accumulate(nums.begin(), nums.end(), 0);
        if (sum % 2 != 0) { return false; }
        auto target = sum / 2;
        // extra row and column for simpler indexing
        Table table(nums.size() + 1, std::vector<int>(target + 1, 0)); 

        for (auto i = 1; i < table.size(); ++i) {
            int value = nums[i-1];
            for (auto j = 0; j < table[0].size(); ++j) {
                if (j - value >= 0) {
                    table[i][j] = std::max(value + table[i-1][j - value], table[i-1][j]);
                } else {
                    table[i][j] = table[i-1][j];
                }
            }
            if (table[i].back() == sum / 2) { return true; }
        }
        return false;
    }
};

void test_can_partition() {
    Solution soln;
    assert(soln.canPartition({2}) == false);
    assert(soln.canPartition({5}) == false);
    assert(soln.canPartition({2,2}) == true);
    assert(soln.canPartition({1,2,3,4,2}) == true);
    assert(soln.canPartition({1,4,2,5,0}) == true);
    assert(soln.canPartition({1,4,3,5,0}) == false);
    assert(soln.canPartition({1,3,3,2,11}) == false);
}


int main(int argc, char** argv) {
    test_can_partition();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
