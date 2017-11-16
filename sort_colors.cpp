// Leetcode: https://leetcode.com/problems/sort-colors/ 
// Given an array with n objects colored red, white or blue, sort them so that objects of the 
// same color are adjacent, with the colors in the order red, white and blue.
// We use the integers 0, 1, and 2 to represent the red, white, and blue respectively.

// Brute Force: Sort the array, e.g., using quicksort of mergesort. O(n*logn) time.
// Better: Use a quicksort-style partition algorithm. O(n) time and O(1) space.

#include <vector>
#include <iostream>
#include <algorithm>
#include <assert.h>

static const int Red = 0;
static const int White = 1;
static const int Blue = 2;

using Colors = std::vector<int>;

// Accepted. 3ms. Beats 12.96% of submissions, and ties 86.99% of submissions.
class Solution {
public:
    void sortColors(std::vector<int>& colors) {
        if (colors.empty()) { return; }
        int next_red = 0, next_white = 0, next_blue = colors.size() - 1;
        int i = 0;

        while (i <= next_blue) {
            if (colors[i] == Red) {
                std::swap(colors[next_red], colors[i]);
                ++next_red;
                ++next_white;
                ++i;
            } else if (colors[i] == White) {
                ++next_white;
                ++i;
            } else if (colors[i] == Blue) {
                std::swap(colors[i], colors[next_blue]);
                --next_blue;
            }
        }
    }
};

bool test_sort_colors(Colors colors) {
    Colors copy(colors);
    std::sort(copy.begin(), copy.end());
    
    Solution soln;
    soln.sortColors(colors);
    return colors == copy;
}

void test_sort_colors() {
    assert(test_sort_colors({1,0,2}));
    assert(test_sort_colors({1,1,2,0,0}));
    assert(test_sort_colors({2,1,2,0,0}));
    assert(test_sort_colors({2,2,0,1,0,1}));
    assert(test_sort_colors({2,2,0,0,1,1}));
    assert(test_sort_colors({0,0,1,1,2,2,2}));
    assert(test_sort_colors({1,0,2,1,0,1,2,0}));
}


int main(int argc, char** argv) {
    test_sort_colors();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
