// Leetcode: https://leetcode.com/problems/non-decreasing-array/description/
// Given an integer array, determine if it could become non-decreasing by modifying at most 1 element.

// Approach: Scan the array from left to right, looking for decreasing elements. If such an element
// is found, determine which of (prev, next) should be modified (i.e., decrease prev, or 
// increase next). Prefer prev if it is possible. O(n) time and O(1) space.

#include <vector>
#include <iostream>
#include <assert.h>

class Solution {
public:
    bool checkPossibility(const std::vector<int>& nums) {
        int prev = nums.front();
        bool mismatch = false;
        for (int i = 1; i < nums.size(); ++i) {
            if (nums[i] < prev) {
                if (!mismatch) {
                    if (i == 1 || (i > 1 && nums[i-2] <= nums[i])) {
                        prev = nums[i];
                    } else {
                        prev = nums[i-1];
                    }
                    mismatch = true;
                    continue;
                } else {
                    return false;
                }
            }
            prev = nums[i];
        }
        return true;
    }
};

void test_check_possibility() {
    Solution soln;

    assert(soln.checkPossibility({1}) == true);
    assert(soln.checkPossibility({1,2}) == true);
    assert(soln.checkPossibility({4,2,3}) == true);
    assert(soln.checkPossibility({1,2,3,4,5}) == true);
    assert(soln.checkPossibility({1,2,4,3,5}) == true);
    assert(soln.checkPossibility({1,5,4,3,5}) == false);
    assert(soln.checkPossibility({5,2,5,5,5}) == true);
    assert(soln.checkPossibility({5,2,5,2,5}) == false);
    assert(soln.checkPossibility({5,2,2,5,5}) == true);
}

int main(int argc, char** argv) {
    test_check_possibility();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
