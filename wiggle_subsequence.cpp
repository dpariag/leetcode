// Leetcode: https://leetcode.com/problems/wiggle-subsequence/description/
// In a wiggle sequence, the differences between successive numbers alternates between positive and negative.
// Given an array, find the longest subsequence which is a wiggle subsequence.

// Brute Force: Generate all subsequences, check if each is a wiggle subsequence. O(n*2^n) time.
// Better: Solve as an instance of longest increasing subsequence problem. O(n^2) time.
// Best: Compare A[i] to A[i-1] and possibly grow a subsequence involving A[i-1]. O(n) time/space.

#include <vector>
#include <iostream>
#include <assert.h>

struct Length {
    int bigger_len = 1;
    int smaller_len = 1;
};
using Lengths = std::vector<Length>;

// Accepted. 3ms. Beats 71.70% of submissions.
class Solution {
public:
    int wiggleMaxLength(std::vector<int>& nums) {
        if (nums.size() < 2) { return nums.size(); }
        Lengths lens(nums.size());

        for (int i = 1; i < nums.size(); ++i) {
            if (nums[i] > nums[i-1]) {
                lens[i].bigger_len = std::max(lens[i-1].smaller_len + 1, lens[i-1].bigger_len);
                lens[i].smaller_len = lens[i-1].smaller_len;
            } else if (nums[i] < nums[i-1]) {
                lens[i].smaller_len = std::max(lens[i-1].bigger_len + 1, lens[i-1].smaller_len);
                lens[i].bigger_len = lens[i-1].bigger_len;
            } else {
                // Equal
                lens[i] = lens[i-1];
            }
        }
        return std::max(lens.back().bigger_len, lens.back().smaller_len);
    }
};

bool test_max_wiggle_len(std::vector<int> nums, int expected) {
    Solution soln;
    return soln.wiggleMaxLength(nums) == expected;
}

void test_max_wiggle_len() {
    assert(test_max_wiggle_len({}, 0));
    assert(test_max_wiggle_len({1}, 1));
    assert(test_max_wiggle_len({1,1}, 1));
    assert(test_max_wiggle_len({1,2}, 2));
    assert(test_max_wiggle_len({1,17,5,10,13}, 4));
    assert(test_max_wiggle_len({1,7,4,9,2,5}, 6));
    assert(test_max_wiggle_len({1,17,5,10,13,15,10,5,16,8}, 7));
    assert(test_max_wiggle_len({1,2,3,4,5,6,7,8,9}, 2));
}

int main(int argc, char** argv) {
    test_max_wiggle_len();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
