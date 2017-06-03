// Leetcode: https://leetcode.com/problems/longest-harmonious-subsequence/#/description 
// In a harmonious subsequence, the difference between the maximum value and the minimum value is one.
// Given an integer array, find the length of its longest harmonious subsequence.

// Brute Force: For each A[i], compute the longest harmonious sequence starting at i. O(n^2) time.
// Better: Use a hash map to store the length of the longest harmonious subsequence beginning at i

#include <vector>
#include <unordered_map>
#include <iostream>
#include <assert.h>

// Accepted. 95ms. Beats 82.67% of submissions, ties 5.5% of submissions.
class Solution {
public:
    int findLHS(const std::vector<int>& nums) {
        std::unordered_map<int, int> counts(nums.size() * 2);
        for (auto n : nums) {
            ++counts[n];
        }
        
        int max_len = 0;
        for (auto iter = counts.begin(); iter != counts.end(); ++iter) {
            auto plus_one = counts.find(iter->first + 1);
            if (plus_one != counts.end()) {
                max_len = std::max(max_len, iter->second + plus_one->second);
            }

            auto minus_one = counts.find(iter->first - 1);
            if (minus_one != counts.end()) {
                max_len = std::max(max_len, iter->second + minus_one->second);
            }
        }
        return max_len;
    }
};

void test_longest_harmonious() {
    Solution soln;
    assert(soln.findLHS({1}) == 0);
    assert(soln.findLHS({1,2,1,2,1,2,1,2}) == 8);
    assert(soln.findLHS({10,1,2,1,2,1,2,1,2}) == 8);
    assert(soln.findLHS({10,1,2,1,2,8,1,2,1,2}) == 8);
    assert(soln.findLHS({10,1,2,1,2,8,1,2,1,2,11}) == 8);
    assert(soln.findLHS({1,1,1,1,1,1,1,1,1}) == 0);
    assert(soln.findLHS({1,3,4,3,3,1,2,4,5}) == 5);
    assert(soln.findLHS({1,2,3,4,5,6,7,8,9}) == 2);
    assert(soln.findLHS({1,3,2,2,5,2,3,7}) == 5);
}

int main(int argc, char** argv) {
    test_longest_harmonious();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
