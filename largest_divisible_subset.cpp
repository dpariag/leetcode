// Leetcode: https://leetcode.com/problems/largest-divisible-subset/description/
// Given a set of distinct positive integers, find the largest subset such that every pair (Si, Sj) 
// of elements in this subset satisfies: Si % Sj = 0 or Sj % Si = 0.

// Brute Force: Generate all subsets, check for divisibility. O(2^n) time and space.
// Better: Sort the array (nums) so that each entries possible divisors precede it.
// For each nums[i], track its divisors in a separate array (e.g., divisors[i])
// For each nums[i] find the largest divisors[j] where nums[j] divides nums[i]. Update divisors[i].
// O(n^2) time and space.

#include <vector>
#include <algorithm>
#include <iostream>
#include <assert.h>

// Accepted. 33ms. Beats 58.45% of submissions, ties 23.97% of submissions
class Solution {
public:
    std::vector<int> largestDivisibleSubset(std::vector<int>& nums) {
        if (nums.empty()) { return std::vector<int>(); }

        std::vector<std::vector<int>> divisors(nums.size(), std::vector<int>());
        std::sort(nums.begin(), nums.end());
        int largest_index = 0;
        divisors[0].emplace_back(nums[0]);

        for (int i = 1; i < nums.size(); ++i) {
            int max_divisors = -1, max_index = 0;
            for (int j = 0; j < i; ++j) {
                if (nums[i] % nums[j] == 0 && int(divisors[j].size()) > max_divisors) {
                    max_divisors = divisors[j].size();
                    max_index = j;
                }
            }
            if (max_divisors > 0) {
                divisors[i] = divisors[max_index];
            }
            divisors[i].emplace_back(nums[i]);
            if (int(divisors[i].size()) > divisors[largest_index].size()) {
                largest_index = i;
            }
        }
        return divisors[largest_index];
    }
};

bool test_largest_divisible(std::vector<int> nums, std::vector<int> expected) {
    Solution soln;
    auto set = soln.largestDivisibleSubset(nums);
    std::sort(set.begin(), set.end());
    return set == expected;
}

void test_largest_divisible() {
    assert(test_largest_divisible({}, {}));
    assert(test_largest_divisible({1,2,3}, {1,2}));
    assert(test_largest_divisible({2,5,10,12,15,150}, {2,10,150}));
    assert(test_largest_divisible({2,8,11,20,24,33}, {2,8,24}));
    assert(test_largest_divisible({3,6,8,24}, {3,6,24}));
}

int main(int argc, char** argv) {
    test_largest_divisible();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
