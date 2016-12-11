// Leetcode: https://leetcode.com/problems/move-zeroes/
// Given an array, nums, move all 0's to the end of it maintaining the order of all other elements.
// Example: nums = [0, 1, 0, 3, 12] --> [1, 3, 12, 0, 0]. Do it in place.

// Brute Force: Iterate the array, removing zeroes and shuffling elements left. O(n^2) time.
// Better: Count the number of zeroes. Move all non-zero elements left, and pad with correct 
// number of zeroes.

#include <vector>
#include <iostream>
#include <assert.h>

// Accepted. 16ms. Beats 37.31% of submissions, ties 52.05% of submissions.
class Solution {
public:
    void moveZeroes(std::vector<int>& nums) {
        auto num_zeroes = 0;
        for (auto n : nums) { 
            num_zeroes += (n == 0) ? 0 : 1; 
        }
        
        int j = 0;
        for (auto i = 0; i < nums.size(); ++i) {
            if (nums[i] != 0) {
                nums[j] = nums[i];
                ++j;
            }
        }

        for (auto i = j; i < nums.size(); ++i) {
            nums[i] = 0;
        }
    }
};

bool test_move_zeroes(std::vector<int> nums, const std::vector<int>& expected) {
    Solution soln;
    soln.moveZeroes(nums);
    return nums == expected;
}

void test_move_zeroes() {
    assert(test_move_zeroes({}, {}));
    assert(test_move_zeroes({0}, {0}));
    assert(test_move_zeroes({7}, {7}));
    assert(test_move_zeroes({0,0,0}, {0,0,0}));
    assert(test_move_zeroes({0,1,0,3,12}, {1,3,12,0,0}));
    assert(test_move_zeroes({0,0,3,12,1}, {3,12,1,0,0}));
    assert(test_move_zeroes({3,12,1}, {3,12,1}));
}

int main(int argc, char** argv) {
    test_move_zeroes();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
