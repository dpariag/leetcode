// Leetcode: https://leetcode.com/problems/container-with-most-water/#/description
// Given a histogram, represented as an integer array, find the pair of lines which together with 
// the x-axis traps the most water.

// Brute Force: Examine all pairs of lines, calculating the trapped water. Track max. O(n^2)
// Better: Iterate the array from both ends. At each iteration, discard the shorter line in
// the pair advancing that endpoint inward. Track the max. O(n) time and O(1) space.

#include <vector>
#include <iostream>
#include <assert.h>

// Accepted. 19ms. Beats 42.63% of submissions, ties 45.98% of submissions.
class Solution {
public:
    int maxArea(const std::vector<int>& lines) {
        int max_area = 0;
        int i = 0, j = lines.size() - 1; 

        while (i < j) {
            int area = (j - i) * std::min(lines[i], lines[j]);
            max_area = std::max(area, max_area);

            if (lines[i] < lines[j]) {
                ++i;
            } else if (lines[i] > lines[j]) {
                --j;
            } else {
                ++i; --j;
            }
        }
        return max_area;
    }
};

void test_max_area() {
    Solution soln;
    assert(soln.maxArea({1,2,5,4,0,5}) == 15);
    assert(soln.maxArea({20,20,5,4,0,5}) == 25);
    assert(soln.maxArea({50,50,5,4,0,5}) == 50);
    assert(soln.maxArea({5,5,5,4,0,5}) == 25);
}

int main(int argc, char** argv) {
    test_max_area();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
