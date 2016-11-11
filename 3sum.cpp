// Leetcode: https://leetcode.com/problems/3sum/#include <vector>
// Given an array S of n integers, are there distinct elements a,b,c in S such that a + b + c = 0?
// Find all unique triplets in the array which sum to zero.

// Brute Force: Generate all triplets (i.e., choose(n,3)) and store unique triplets 
// which sum to zero. O(n^3) time and space.
// Better: Sort S, then for each S[i], scan the subarray S[i+1...n] from either end 
// looking for a pair such that S[i] + S[left] + S[right] == 0. O(n^2) time and O(1) space.

#include <vector>
#include <iostream>
#include <assert.h>
#include <limits>
#include <algorithm>

using Triple = std::vector<int>;        // alias the leetcode definition of a triple
using Triples = std::vector<Triple>;    // similarly, alias the leetcode definition

// Accepted. 39ms runtime, beating 93.87% of submissions and tying 5.98%
class Solution {
public:
    Triples threeSum(std::vector<int>& nums) {
        Triples result;
        if (nums.size() < 3) { return result; }

        std::sort(nums.begin(), nums.end());
        auto i = 0, left = 0, right = 0;

        while (i < nums.size() - 1) {
            // Scan S[i+1...end] from either end, looking for a triple that sums to zero
            left = i + 1;
            right = nums.size() - 1;

            while (left < right) {
                if (nums[i] > 0) { return result; } // sum can never equal 0 
                auto triple_sum = nums[i] + nums[left] + nums[right];
                if (triple_sum == 0) {
                    // record the triple and keep looking
                    result.emplace_back(Triple({nums[i], nums[left], nums[right]}));
                    while (left < right && nums[left] == nums[left+1]) { ++left; }
                    ++left;
                    while (left < right && nums[right] == nums[right-1]) { --right; }
                    --right;
                } else if (triple_sum < 0) {
                    ++left;
                } else { // triple_sum > 0
                    --right;
                }
            }
            while (i < nums.size() - 1 && nums[i] == nums[i+1]) { ++i; }
            ++i;
        }
        return result;
    }
};

bool test_three_sum(std::vector<int> nums, Triples expected) {
    Solution soln;
    auto result = soln.threeSum(nums);

    std::sort(result.begin(), result.end());
    std::sort(expected.begin(), expected.end());
    return (result == expected);
}

void test_three_sum() {
    assert(test_three_sum({0,0,0}, {{0,0,0}}));
    assert(test_three_sum({0,0,0,0}, {{0,0,0}}));
    assert(test_three_sum({0,0,0,0,1}, {{0,0,0}}));
    assert(test_three_sum({-1,0,1,2,-1,-4}, {{-1,0,1},{-1,-1,2}}));
    assert(test_three_sum({-10,-9,4,5,6}, {{-10,4,6},{-9,4,5}}));
    assert(test_three_sum({-10,-4,6,8,-4}, {{-4,-4,8}}));
    assert(test_three_sum({8,-10,-4,6,8,-4}, {{-4,-4,8}}));
    assert(test_three_sum({-1,1,0,10,-20,-9,6,3,1,10}, {{-1,0,1},{-9,3,6},{-20,10,10},{-9,-1,10}}));
    assert(test_three_sum({-4,-2,-2,-2,0,1,2,2,2,3,3,4,4,6,6},
                          {{-4,-2,6},{-4,0,4},{-4,1,3},{-4,2,2},{-2,-2,4},{-2,0,2}}));
}

int main(int argc, char** argv) {
    test_three_sum();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
