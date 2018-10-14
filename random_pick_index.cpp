// Leetcode: https://leetcode.com/problems/random-pick-index/description/
// Given an array of integers with possible duplicates, randomly output the index of a given 
// target number. You can assume that the given target number must exist in the array.

// Brute Force: Store indices of each number in a hash map of vectors. 
// Then, given a target, return a random index. O(n) time/space
// Better: Sweep the list twice, once to count instances of target, then again
// to return a random one.

#include <vector>
#include <iostream>
#include <assert.h>

// Accepted. 88ms. Beats 79.67% of submissions, ties 1.10% of submissions.
class Solution {
public:
    Solution(std::vector<int> nums): m_nums(nums) {}
    
    int pick(int target) {
        int count = 0;
        for (int i = 0; i < m_nums.size(); ++i) {
            if (m_nums[i] == target) ++count;
        }

        int n = 1 + (std::rand() % count);    // Generate a number between 1..n

        int j = 0;
        for (int i = 0; i < m_nums.size(); ++i) {
            if (m_nums[i] == target) ++j;
            if (j == n) { return i; }
        }
        return -1;
    }
private:
    std::vector<int> m_nums;
};

int main(int argc, char** argv) {
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
