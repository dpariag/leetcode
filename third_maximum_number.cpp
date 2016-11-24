// Leetcode: https://leetcode.com/problems/third-maximum-number/ 
// Given a non-empty array of integers, return the third maximum number in this array. 
// If it does not exist, return the maximum number. The time complexity must be in O(n).

// Brute Force: Sort the array and return the 3rd entry, if it exists. O(n*logn) time, O(1) space.
// Better: Scan the array once, tracking the largest, second largest, and third largest entries.
// O(n) time and O(1) space. Process duplicates carefully.

#include <vector>
#include <limits>
#include <iostream>
#include <assert.h>

// Accepted. 6ms. Beats 58.49% of submissions, ties 30.74% of submissions
class Solution {
public:
    int thirdMax(std::vector<int>& nums) {
        int num_distinct = 0;
        int64_t max, second_max, third_max;
        max = second_max = third_max = std::numeric_limits<int64_t>::min();

        for (auto num : nums) {
            if (num > max) {
                third_max = second_max;
                second_max = max;
                max = num;
                ++num_distinct;
            } else if (num > second_max && num != max) {
                third_max = second_max;
                second_max = num;
                ++num_distinct;
            } else if (num > third_max && num != second_max && num != max) {
                third_max = num;
                ++num_distinct;
            }
        }
        if (nums.size() < 3 || num_distinct < 3) { return max; } 
        return third_max;
    }
};

bool test_third_max(std::vector<int> nums, int expected) {
    Solution soln;
    return soln.thirdMax(nums) == expected;    
}

void test_third_max() {
    assert(test_third_max({1,1,2}, 2));
    assert(test_third_max({3,2,1}, 1));
    assert(test_third_max({2,1}, 2));
    assert(test_third_max({2,2,3,1}, 1));
    assert(test_third_max({22,7,2,2,3,9,1}, 7));
}

int main(int argc, char** argv) {
    test_third_max();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
