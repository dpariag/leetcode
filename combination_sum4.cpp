// Leetcode: https://leetcode.com/problems/combination-sum-iv/description/
// Given an integer array with all positive numbers and no duplicates, 
// find the number of possible combinations that add up to a positive integer target.

// Brute Force:
// Better:

#include <vector>
#include <unordered_map>
#include <iostream>
#include <assert.h>

using Cache = std::unordered_map<int, int>;

// Accepted. 5ms. Beats 9.28% of submissions, ties < 1% of submissions.
class Solution {
public:
    int count_combos(const std::vector<int>& nums, int sum, int target, Cache& cache) {
        if (sum > target) { return 0; }
        if (sum == target) { return 1; }

        auto found = cache.find(sum);
        if (found != cache.end()) { return found->second; }
        
        int combos = 0;
        for (int i = 0; i < nums.size(); ++i) {
            if (sum + nums[i] <= target) {
                combos += count_combos(nums, sum + nums[i], target, cache);
            }
        }
        cache[sum] = combos;
        return combos;
    }

    int combinationSum4(const std::vector<int>& nums, int target) {
        Cache cache(1000); // reserve some space
        return count_combos(nums, 0, target, cache);
    }
};

void test_combination_sum4() {
    Solution soln;
    assert(soln.combinationSum4({1,2,3}, 3) == 4);
    assert(soln.combinationSum4({1,2,3}, 4) == 7);
}

int main(int argc, char** argv) {
    test_combination_sum4();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
