// Leetcode: https://leetcode.com/problems/merge-sorted-array/description/
// Given two sorted integer arrays nums1 and nums2, merge nums2 into nums1 as one sorted array.

// Brute Force: Allocate a third array to hold the result of the merge, then copy it back to nums1.
// Better: Shift elements of nums1 to the right by n spots, then merge arrays into space created.
// Be careful to handle the case of either array being empty.

#include <vector>
#include <iostream>
#include <assert.h>

// Accepted. 3ms. Beats 37.56% of submissions, ties 62.44 of submissions.
class Solution {
public:
    void merge(std::vector<int>& nums1, int m, std::vector<int>& nums2, int n) {
        if (nums2.empty()) { return; }
        int last = m + n - 1;

        for (int to_copy = m-1; to_copy >= 0; --to_copy) {
            nums1[last--] = nums1[to_copy];
        }

        int i = n, j = 0, dest = 0;
        while (i < m+n && j < nums2.size() && dest < nums1.size()) {
            nums1[dest++] = nums1[i] < nums2[j] ? nums1[i++] : nums2[j++];
        }
        while (j < nums2.size() && dest < nums1.size()) { nums1[dest++] = nums2[j++]; }
    }
};

using Numbers = std::vector<int>;
bool test_merge(Numbers nums1, int capacity, Numbers nums2, Numbers expected) {
    Solution soln;
    int m = nums1.size(), n = nums2.size();
    while (nums1.size() < capacity) { nums1.emplace_back(0); }
    soln.merge(nums1, m, nums2, n);
    return  nums1 == expected;
}

void test_merge() {
    assert(test_merge({},0,{},{}));
    assert(test_merge({1},1,{},{1}));
    assert(test_merge({},1,{1},{1}));
    assert(test_merge({1,2,3},4,{1},{1,1,2,3}));
    assert(test_merge({1,2,3},6,{1,2,3},{1,1,2,2,3,3}));
    assert(test_merge({1,2,3},6,{4,5,6},{1,2,3,4,5,6}));
    assert(test_merge({4},2,{1},{1,4}));
    assert(test_merge({4,5},3,{1},{1,4,5}));
    assert(test_merge({4,5,6},4,{1},{1,4,5,6}));
    assert(test_merge({4,5,6},5,{1,2},{1,2,4,5,6}));
    assert(test_merge({4,5,6},6,{1,2,3},{1,2,3,4,5,6}));
}

int main(int argc, char** argv) {
    test_merge();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}