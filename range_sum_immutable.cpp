// Leetcode: https://leetcode.com/problems/range-sum-query-immutable/description/
// Given an integer array nums, find the sum of the elements between indices i and j (i ≤ j), inclusive.

// Brute Force: Sweep A[i] to A[j] inclusive and calculate the range sum. O(n) time.
// Better: Pre-compute prefix and suffix sums of the array. The range sum then takes O(1) time.

#include <vector>
#include <iostream>
#include <assert.h>

// Accepted. 180ms. Beats 51.41% of submissions.
class NumArray {
public:
    NumArray(const std::vector<int>& nums): total(0), prefix_sums(nums.size(),0), suffix_sums(nums.size(), 0) {
        int last = nums.size() - 1;
        for (int i = 0; i < nums.size(); ++i,--last) {
            total += nums[i];
            prefix_sums[i] = nums[i];
            suffix_sums[last] = nums[last];

            if (i > 0) { prefix_sums[i] += prefix_sums[i-1]; }
            if (last < nums.size() - 1) { suffix_sums[last] += suffix_sums[last+1]; }
        }
    }
    
    int sumRange(int i, int j) {
        int prefix = (i > 0) ? prefix_sums[i-1] : 0;
        int suffix = (j < suffix_sums.size() - 1) ? suffix_sums[j+1] : 0;
        return total - prefix - suffix;
    }

private:
    int total;
    std::vector<int> prefix_sums;
    std::vector<int> suffix_sums;
};

bool test_num_array(const std::vector<int>& nums, int i, int j, int expected) {
    NumArray num_array(nums);
    return num_array.sumRange(i, j) == expected;
}

void test_num_array() {
    assert(test_num_array({1,2,3,4}, 0, 0, 1));
    assert(test_num_array({1,2,3,4}, 0, 1, 3));
    assert(test_num_array({1,2,3,4}, 0, 2, 6));
    assert(test_num_array({1,2,3,4}, 0, 3, 10));
    assert(test_num_array({1,2,3,4}, 1, 1, 2));
    assert(test_num_array({1,2,3,4}, 1, 2, 5));
    assert(test_num_array({1,2,3,4}, 2, 3, 7));
    assert(test_num_array({1,2,3,4}, 3, 3, 4));    
}

int main(int argc, char** argv) {
    test_num_array();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}