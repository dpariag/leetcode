// Leetcode: https://leetcode.com/problems/4sum/description/
// Given an integer array S, find all unique quadruplets in the array which sum to a given target.

// Brute Force: Generate all quadruplets, check sum against target, filter duplicates. O(n^4) time.
// Better: Reduce to the 2Sum problem. Sort the array, then generate all unique pairs and calculate 
// their sum. Use the 2Sum problem to find another pair with the complementary sum. O(n^3)

#include <vector>
#include <algorithm>
#include <iostream>
#include <assert.h>

using Quadruplet = std::vector<int>;
using Quadruplets = std::vector<Quadruplet>;

// Accepted. 23ms. Beats 76.50% of submissions, ties 1.76% of submissions.
class Solution {
public:
    Quadruplets fourSum(std::vector<int>& nums, int target) {
        Quadruplets result;
        std::sort(nums.begin(), nums.end()); 
        int i = 0, j = 0;

        while (i < nums.size()) {
            j = i + 1;
            while (j < nums.size()) {
                auto sum = nums[i] + nums[j];
                auto complement = target - sum;
                int left = j+1, right = int(nums.size()) - 1;
                while (left < right) {
                    auto cur_sum = nums[left] + nums[right];
                    if (cur_sum < complement) {
                        ++left;
                    } else if (cur_sum > complement) {
                        --right;
                    } else if (cur_sum == complement) {
                        result.emplace_back(Quadruplet({nums[i], nums[j], nums[left], nums[right]}));
                        auto cur = nums[left];
                        ++left;
                        while (left < right && nums[left] == cur) { ++left; }
                        cur = nums[right];
                        --right;
                        while (left < right && nums[right] == cur) { --right; }
                    }
                }
                auto cur = nums[j];
                ++j;
                while (j < nums.size() && nums[j] == cur) { ++j; }
            }
            auto cur = nums[i];
            ++i;
            while (i < nums.size() && nums[i] == cur) { ++i; }
        }
        return result;
    }
};

bool test_4_sum(std::vector<int> nums, int target, Quadruplets expected) {
    Solution soln;
    auto result = soln.fourSum(nums, target);
    for (auto& quadruplet : result) {
        std::sort(quadruplet.begin(), quadruplet.end());
    }
    std::sort(expected.begin(), expected.end());
    std::sort(result.begin(), result.end());
    return (result == expected);
}

void test_4_sum() {
    assert(test_4_sum({}, 0, {}));
    assert(test_4_sum({0,0,0,0}, 0, {{0,0,0,0}}));
    assert(test_4_sum({1,0,-1,0,-2,2}, 0, {{-2,0,0,2},{-2,-1,1,2},{-1,0,0,1}}));
    assert(test_4_sum({1,2,10,15,4,0}, 20, {{0,1,4,15}}));
}

int main(int argc, char** argv) {
    test_4_sum();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
