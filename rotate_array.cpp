// Leetcode: https://leetcode.com/problems/rotate-array/ 
// Rotate an array of n elements to the right by k steps.
// Example: Given A = [1,2,3,4,5,6,7] and k = 3, the result is A' = [5,6,7,1,2,3,4].

// Brute Force: 
// 1) Rotate the array by one element k times. O(n*k) time and O(1) space.
// 2) Use a temporary array to copy items appropriately. O(n) time and space.
// Better: Reverse the array, then reverse the first k items and the last (n-k) items separately.
// O(n) time and O(1) space.

#include <vector>
#include <algorithm>
#include <iostream>
#include <assert.h>

using Numbers = std::vector<int>;

// Accepted. 19ms. Beats 40.41% of submissions, ties 46.39% of submissions.
class Solution {
public:
    void rotate(Numbers& nums, int k) {
        if (nums.empty() || k < 0) { return; }
        k = k % (nums.size());
        std::reverse(nums.begin(), nums.end());
        std::reverse(nums.begin(), nums.begin() + k);
        std::reverse(nums.begin() + k, nums.end());
    }
};

bool test_rotate(Numbers nums, int k, const Numbers& expected) {
    Solution soln;
    soln.rotate(nums, k);
    return (nums == expected); 
}

void test_rotate() {
    assert(test_rotate({}, 1, {}));
    assert(test_rotate({}, 5, {}));
    assert(test_rotate({7}, 5, {7}));
    assert(test_rotate({1,2,3,4,5,6,7}, 1, {7,1,2,3,4,5,6}));
    assert(test_rotate({1,2,3,4,5,6,7}, 2, {6,7,1,2,3,4,5}));
    assert(test_rotate({1,2,3,4,5,6,7}, 3, {5,6,7,1,2,3,4}));
    assert(test_rotate({1,2,3,4,5,6,7}, 4, {4,5,6,7,1,2,3}));
    assert(test_rotate({1,2,3,4,5,6,7}, 5, {3,4,5,6,7,1,2}));
    assert(test_rotate({1,2,3,4,5,6,7}, 6, {2,3,4,5,6,7,1}));
    assert(test_rotate({1,2,3,4,5,6,7}, 7, {1,2,3,4,5,6,7}));
    assert(test_rotate({1,2,3,4,5,6,7}, 8, {7,1,2,3,4,5,6}));
    assert(test_rotate({1,2,3,4,5,6,7}, 9, {6,7,1,2,3,4,5}));
}

int main(int argc, char** argv) {
    test_rotate();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
