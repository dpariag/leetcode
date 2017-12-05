// Leetcode: https://leetcode.com/problems/sort-transformed-array/description/
// Given a sorted array of integers and integers a, b and c, apply a quadratic function 
// f(x) = ax^2 + bx + c to each element x in the array. Return the array in sorted order

// Brute Force:
// Better:

#include <vector>
#include <iostream>
#include <assert.h>

const int cINT_MAX = std::numeric_limits<int>::max();

// Accepted. 9ms. Beats 16.46% of submissions, ties 58.23% of submissions.
class Solution {
public:
    inline int f(int x, int a, int b, int c) {
        return a*x*x + b*x + c;
    }

    std::vector<int> sortTransformedArray(std::vector<int>& nums, int a, int b, int c) {
        std::vector<int> result(nums.size(), 0);

        if (a > 0) {
            int min_index = 0, k = 0, min = cINT_MAX;
            while (k < nums.size()) { 
                auto val = f(nums[k], a, b, c);
                if (val < min) {
                    min_index = k;
                    min = val;
                }
                ++k;
            }
            int left = min_index-1, right = min_index;
            int i = 0;
            while (i < nums.size()) {
                auto left_val = left >= 0 ? f(nums[left], a, b, c) : cINT_MAX;
                auto right_val = right < nums.size() ? f(nums[right], a, b, c) : cINT_MAX;
                if (left_val < right_val) {
                    result[i] = left_val;
                    --left;
                } else {
                    result[i] = right_val;
                    ++right;
                }
                ++i;
            }
        } else if (a < 0) {
            int i = 0, left = 0, right = nums.size() - 1;
            while (i < nums.size()) {
                auto left_val = f(nums[left], a, b, c); 
                auto right_val = f(nums[right], a, b, c);
                if (left_val < right_val) {
                    result[i] = left_val;
                    ++left;
                } else {
                    result[i] = right_val;
                    --right;
                }
                ++i;
            }
        } else if (b >= 0) {
            // a == 0
            for (int i = 0; i < nums.size(); ++i) {
                result[i] = f(nums[i], a, b, c);
            }
        } else if (b < 0) {
            // a == 0
            int i = 0;
            for (int j = nums.size()-1; j >= 0; --j) {
                result[i] = f(nums[j], a, b, c);
                ++i;
            }
        }
        return result;
    }
};

int main(int argc, char** argv) {
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
