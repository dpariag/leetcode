// Leetcode: https://leetcode.com/problems/subsets-ii/description/
// Given a collection of integers that might contain duplicates, nums, return all possible subsets (the power set).

// Brute Force: Generate all subsets, but use a hash map to filter out duplicates.
// Better: Sort the input set, and if a number is not chosen, skip past all duplicates. O(2^n) time and space.

#include <vector>
#include <algorithm>
#include <iostream>
#include <assert.h>

using Set = std::vector<int>;
using Sets = std::vector<Set>;

// Accepted. 6ms. Beats 76.38% of submissions, ties 23.62% of submissions.
class Solution {
public:
    void generate_sets(std::vector<int>& nums, int index, Set& cur, Sets& result) {
        if (index >= nums.size()) {
            result.emplace_back(cur);
            return;
        }

        // Include nums[index]
        cur.emplace_back(nums[index]);
        generate_sets(nums, index+1, cur, result);

        // Don't include nums[index], or it's duplicates
        cur.pop_back();
        auto skip = nums[index++];
        while (index < nums.size() && nums[index] == skip) { ++index; }
        generate_sets(nums, index, cur, result);
    }

    Sets subsetsWithDup(std::vector<int>& nums) {
        Sets result;
        Set cur;

        std::sort(nums.begin(), nums.end());
        generate_sets(nums, 0, cur, result);
        return result;
    }
};

bool test_subsets_with_dup(std::vector<int> nums, Sets expected) {
    Solution soln;
    auto result = soln.subsetsWithDup(nums);

    for (auto& set : result) { std::sort(set.begin(), set.end()); }
    for (auto& e : expected) { std::sort(e.begin(), e.end()); }

    std::sort(result.begin(), result.end());
    std::sort(expected.begin(), expected.end());
    return result == expected;
}

void test_subsets_with_dup() {
    assert(test_subsets_with_dup({}, {{}}));
    assert(test_subsets_with_dup({1}, {{},{1}}));
    assert(test_subsets_with_dup({1,2}, {{},{1},{2},{1,2}}));
    assert(test_subsets_with_dup({1,2,2}, {{},{1},{2},{1,2},{2,2}, {1,2,2}}));
}

int main(int argc, char** argv) {
    test_subsets_with_dup();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
