// Leetcode: https://leetcode.com/problems/valid-triangle-number/description/
// Given an integer array, find all triples whose values could represent the sides of a triangle.:w

// Brute Force: Generate all triples and check the triangle inequalities (there are 3 of them). O(n^3) time.
// Better: Sort the array. For i < j and j < k then if nums[i] + nums[j] > nums[k] then we have a triangle,
// because the two other inequalities will also hold. Iteration order is important...choose a k then sweep
// i and j from the left and right. This is analogous to the two sum problem. O(n^2) time.

#include <iostream>
#include <vector>
#include <algorithm>
#include <assert.h>

// Accepted. 8ms. Beats 100% of submissions.
class Solution {
public:
    int triangleNumber(std::vector<int>& nums) {
        int num_triangles = 0;
        std::sort(nums.begin(), nums.end());

        for (int k = nums.size()-1; k > 1; --k) {
            int i = 0, j = k-1;
            while (i < j) {
                if (nums[i] + nums[j] > nums[k]) {
                    num_triangles += (j-i);
                    --j;
                } else {
                    ++i;
                }
            }
        }
        return num_triangles; 
    }
};

bool test_triangles(std::vector<int> nums, int expected) {
    Solution soln;
    return soln.triangleNumber(nums) == expected; 
}

void test_triangles() {
    assert(test_triangles({2,2,3,4}, 3));    
}

int main(int argc, char** argv) {
    test_triangles(); 
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
