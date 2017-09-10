// Leetcode: https://leetcode.com/problems/trapping-rain-water/description/
// Given an integer array representing a histogram with bars of width 1, compute how much water is 
// trapped after rainfall.

// Brute Force: For each bar, scan to find the highest bar to the left and right. Water trapped is 
// min(max_left, max_right) - bar.height. O(n^2) time.
// Better: Scan the array left to right, recording highest bar so far. Repeat right to left.
// Last scan calculates water trapped as min(highest_left, highest_right) - bar.height. O(n) time.

#include <vector>
#include <iostream>
#include <assert.h>

// Accepted. Beats 57.56% of submissions, ties 35.28% of submissions.
class Solution {
public:
    int trap(const std::vector<int>& height) {
        std::vector<int> highest_to_left(height.size(), 0);
        std::vector<int> highest_to_right(height.size(), 0);

        // Find the highest bar to the left of each position
        int highest = 0; 
        for (int i = 0; i < height.size(); ++i) {
            highest_to_left[i] = highest;
            highest = std::max(highest, height[i]);
        }

        // Find the highest bar to the right of each position
        highest = 0;
        for (int i = height.size() - 1; i >= 0; --i) {
            highest_to_right[i] = highest;
            highest = std::max(highest, height[i]);
        }
   
        // Water is trapped iff the bar is enclosed by higher bar to the right and left. 
        int trapped = 0;
        for (int i = 0; i < height.size(); ++i) {
            if (highest_to_left[i] > height[i] && highest_to_right[i] > height[i]) {
                trapped += std::min(highest_to_left[i], highest_to_right[i]) - height[i];
            }
        }
        return trapped;
    }
};

void test_trap() {
    Solution soln;
    
    assert(soln.trap({}) == 0);
    assert(soln.trap({1}) == 0);
    assert(soln.trap({1,1}) == 0);
    assert(soln.trap({1,0,1}) == 1);
    assert(soln.trap({0,1,0,2,1,0,1,3,2,1,2,1}) == 6);
    assert(soln.trap({2,3,4,1,4,3,3,3,4,2,3,2,1}) == 7);
}

int main(int argc, char** argv) {
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
