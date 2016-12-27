// Leetcode: https://leetcode.com/problems/find-peak-element/
// A peak element is one that is greater than its neighbors. Given an array where num[i] != num[i+1]
// return the index of any peak element. The array may contain multiple peaks - return the index to 
// any one. Pretend that num[-1] = num[n] = -infinity. 
// Example: Given num = [1, 2, 3, 1], 3 is a peak element and your function should its index (2).

// Brute Force: Scan the array from left to right looking for an element that is greater than its
// neighbors. Treat first and last elements specially. O(n) time and O(1) space.

#include <vector>
#include <iostream>
#include <assert.h>

// Accepted. 6ms. Beats 14.08% of submissions and ties 72.09% of submissions.
class Solution {
public:
    int findPeakElement(const std::vector<int>& nums) {
        if (nums.size() <= 1) { return 0; }
        if (nums[0] > nums[1]) { return 0; }
        int last = nums.size() - 1;
        if (nums[last] > nums[last-1]) { return last; }

        for (auto i = 1; i < nums.size() - 1; ++i) {
            if (nums[i] > nums[i-1] && nums[i] > nums[i+1]) { return i; }
        }
        return -1;
    }
};

void test_is_peak() {
    Solution soln;
    
    assert(soln.findPeakElement({1,2,3,1}) == 2);
    assert(soln.findPeakElement({1}) == 0);
    assert(soln.findPeakElement({1,100,99,88,77}) == 1);
    assert(soln.findPeakElement({1,100,99,88,77}) == 1);
    assert(soln.findPeakElement({1,10,99,88,77}) == 2);
}

int main(int argc, char** argv) {
    test_is_peak();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
