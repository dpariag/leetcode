// Leetcode: https://leetcode.com/problems/maximum-product-of-three-numbers/description/
// Given an integer array, find 3 numbers whose product is maximum.

// Brute Force: Generate all triples, calculate their product, tracm max. O(n^3) time.
// Better: Find the 3 largest and 2 smallest numbers. The max product must come from either
// the 3 largest, or if the two smallest are negative then the two smallest and the largest.

#include <vector>
#include <limits>
#include <iostream>
#include <assert.h>

// Accepted. 46ms. Beats 87.27% of submissions, ties 9.24% of submissions.
class Solution {
public:
    int maximumProduct(const std::vector<int>& nums) {
        int min1, min2, max1, max2, max3;
        min1 = min2 = std::numeric_limits<int>::max();
        max1 = max2 = max3 = std::numeric_limits<int>::min();

        for (int i = 0; i < nums.size(); ++i) {
            auto num = nums[i];
            if (num <= min1) {
                min2 = min1, min1 = num;
            } else if (num < min2) {
                min2 = num;
            }

            if (num >= max1) {
                max3 = max2, max2 = max1, max1 = num;
            } else if (num >= max2 ) {
                max3 = max2, max2 = num;
            } else if (num > max3) {
                max3 = num;
            }
        }
        return std::max(min1*min2*max1, max3*max2*max1);
    }
};

void test_max_product() {
    Solution soln;

    assert(soln.maximumProduct({1,2,3}) == 6);
    assert(soln.maximumProduct({-1,-2,1,1,3}) == 6);
    assert(soln.maximumProduct({-1,-2,-3,-4,-5}) == -6);
}

int main(int argc, char** argv) {
    test_max_product();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
