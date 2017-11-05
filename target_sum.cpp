// Leetcode: https://leetcode.com/problems/target-sum/description/
// Given a list of non-negative integers and a target sum S.
// Find out how many ways you can assign '+' and '-' operators to obtain the target sum S.

// Brute Force: Use recursion to assign +/- signs to each number. O(2^n)
// Better: Memoize the recursion to avoid re-calculating paths

#include <vector>
#include <unordered_map>
#include <iostream>
#include <assert.h>

struct PairHash {
    size_t operator()(const std::pair<int,int>& p) const {
        return p.first * 13 + p.second * 17;
    }
};
using Cache = std::unordered_map<std::pair<int,int>, int, PairHash>; // (index, target) -> # ways 

class Solution {
public:
    int find_ways(const std::vector<int>& nums, int i, int target, Cache& cache) {
        if (i == nums.size() - 1) {
            if (nums.back() == target || nums.back() == -target) { return 1; }
            return 0;
        }
        auto found = cache.find(std::make_pair(i, target));
        if (found != cache.end()) { return found->second; }

        int ways = find_ways(nums, i+1, target-nums[i], cache) +
                   find_ways(nums, i+1, target+nums[i], cache);

        cache.emplace(std::make_pair(i, target), ways);
        return ways;
    }

    int findTargetSumWays(const std::vector<int>& nums, int S) {
        Cache cache;
        return find_ways(nums, 0, S, cache);
    }
};

void test_target_sum() {
    Solution soln;
    assert(soln.findTargetSumWays({1,1,1,1,1}, 3) == 5);
    assert(soln.findTargetSumWays({1,2,3,4,5}, 15) == 1);
    assert(soln.findTargetSumWays({1,2,3,4,5}, 11) == 1);
    assert(soln.findTargetSumWays({1,2,3,4,5}, 5) == 3);
}

int main(int argc, char** argv) {
    test_target_sum();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
