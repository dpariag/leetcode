// Leetcode: https://leetcode.com/problems/longest-continuous-increasing-subsequence/description/
// Given an unsorted array of integers, find the length of longest continuous increasing subsequence (subarray).

// Brute Force: Generate all subarrays and determine which is the longest increasing. O(n^3) time.
// Better: Scan the subarray comparing each element to it's predecessor. O(n) time

#include <vector>
#include <iostream>
#include <assert.h>

// Accepted. 15ms. Beats 54.22% of submissions, ties 2.26% of submissions.
class Solution {
public:
    int findLengthOfLCIS(const std::vector<int>& nums) {
        if (nums.empty()) { return 0; }

        int longest = 1, cur = 1;
        for (int i = 1; i < nums.size(); ++i) {
            if (nums[i] > nums[i-1]) {
                ++cur;
                longest = std::max(longest, cur);
            } else {
                cur = 1;
            }
        }
        return longest;
    }
};

void test_lcis() {
    Solution soln;
    assert(soln.findLengthOfLCIS({}) == 0);
    assert(soln.findLengthOfLCIS({11}) == 1);
    assert(soln.findLengthOfLCIS({11,12}) == 2);
    assert(soln.findLengthOfLCIS({11,9}) == 1);
    assert(soln.findLengthOfLCIS({11,9,10,12}) == 3);
    assert(soln.findLengthOfLCIS({11,9,8,7,6}) == 1);
    assert(soln.findLengthOfLCIS({11,9,18,19,20}) == 4);
    assert(soln.findLengthOfLCIS({11,9,18,18,18}) == 2);
}

int main(int argc, char** argv) {
    test_lcis();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}