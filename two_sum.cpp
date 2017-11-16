// Leetcode: Given an array of integers, return indices of the two numbers such that they add up to 
// a specific target. Each input has exactly one solution, and the returned indices must be distinct.
// Example: nums = {2,7,11,15} and target = 9 => return {0,1}

// Brute Force: Evaluate all possible pairs of integers. O(n^2) time and O(1) space.
// Better: Perform a single pass, using an unordered_map to map values back to indices. 
// Since each input has exactly one solution, a value that appears in a solution may not occur 
// more than twice in the input => ignore duplicates. O(n) time and space.

#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <assert.h>

using IndexMap = std::unordered_map<int, int>;
using Numbers = std::vector<int>;

// Accepted. 6ms. Beats 95.17% of submissions, ties 4.83% of submissions.
class Solution {
public:
    Numbers twoSum(Numbers& nums, int target) {
        IndexMap index_map;
        Numbers result;
        for (int i = 0; i < nums.size(); ++i) {
            int complement = target - nums[i];
            auto found = index_map.find(complement);

            if (found != index_map.end()) {
                return Numbers({i, found->second});
            }  else {
                index_map.emplace(nums[i], i);
            }
        }
        return Numbers();
    }
};

bool test_two_sum(Numbers nums, int target, Numbers expected) {
    Solution soln;
    auto result = soln.twoSum(nums, target);
    std::sort(result.begin(), result.end());
    std::sort(expected.begin(), expected.end());
    return result == expected;
}

void test_two_sum() {
    assert(test_two_sum({}, 9, {}));
    assert(test_two_sum({2,7,11,15}, 9, {0,1}));
    assert(test_two_sum({1,2,3,4,5}, 9, {3,4}));
    assert(test_two_sum({1,1,1,1,1,2,4,1,1,5}, 6, {5,6}));
    assert(test_two_sum({1,1,1,1,1,2,4,1,1,5}, 7, {5,9}));
}

int main(int argc, char** argv) {
    test_two_sum();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
