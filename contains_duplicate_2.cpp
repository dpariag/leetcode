// Leetcode: https://leetcode.com/problems/contains-duplicate-ii/?tab=Description
// Given an array of integers and an integer k, determine if there are distinct indices i and j 
// such that nums[i] == nums[j] and abs(i - j) <= k 

// Brute Force: Consider all pairs of indices (i,j) against the criteria. O(n^2) time.
// Better: Use a hash_map to map value to index, and perform a single pass.

#include <vector>
#include <unordered_map>
#include <iostream>
#include <assert.h>

using IndexMap = std::unordered_map<int, int>;

// Accepted. 29ms. Beats 86.24% of submissions and ties 10.25% of submissions.
class Solution {
public:
    bool containsNearbyDuplicate(std::vector<int>& nums, int k) {
        IndexMap index_map(nums.size() * 2);
        for (int i = 0; i < nums.size(); ++i) {
            auto found = index_map.find(nums[i]);
            if (found != index_map.end() && (i - found->second) <= k) {
                return true;
            } else {
                index_map[nums[i]] = i;
            }
        }
        return false;
    }
};

bool test_duplicates(std::vector<int> nums, int k, bool expected) {
    Solution soln;
    return soln.containsNearbyDuplicate(nums, k) == expected;
}

void test_duplicates() {
    assert(test_duplicates({}, 1, false));
    assert(test_duplicates({1,1}, 1, true));
    assert(test_duplicates({1,2,1}, 1, false));
    assert(test_duplicates({1,2,1}, 2, true));
    assert(test_duplicates({1,2,3,4,5,1}, 2, false));
    assert(test_duplicates({1,2,3,4,5,1}, 5, true));
    assert(test_duplicates({1,2,3,4,5,1}, 16, true));
    assert(test_duplicates({1,2,3,4,5,6}, 16, false));
}

int main(int argc, char** argv) {
    test_duplicates();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
