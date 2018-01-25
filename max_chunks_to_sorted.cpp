// Leetcode: https://leetcode.com/problems/max-chunks-to-make-sorted/description/
// Given an array arr that is a permutation of [0, 1, ..., n-1],  we can split the 
// array into subarrays, and sort each one. After concatenating them, the array is sorted.
// What is the max number of subarrays that we can have to obtain a sorted final array.

// Approach: In a sorted array, arr[i] == i. An if arr[i] > i, then the subarray 
// arr[i..arr[i]] is a chunk that must be sorted. Scan the array looking for arr[i] > i
// and growing the region-to-be-sorted. Multiple such regions may exist.

#include <vector>
#include <iostream>
#include <assert.h>

// Accepted. 3ms. No runtime distribution data available.
class Solution {
public:
    int maxChunksToSorted(const std::vector<int>& arr) {
        int i = 0, num_chunks = 0;
        int end = 0;
        while (i < arr.size()) {
            if (arr[i] > i) {
                end = std::max(end, arr[i]);
            } else if (i == end) {
                ++num_chunks;
            } else if (i > end && arr[i] == i) {
                ++num_chunks;
            }
            ++i;
        }
        return num_chunks;
    }
};

void test_max_chunks() {
    Solution soln;

    assert(soln.maxChunksToSorted({1,0,2,3,4}) == 4);
    assert(soln.maxChunksToSorted({0,4,2,3,1}) == 2);
    assert(soln.maxChunksToSorted({1,4,0,2,3}) == 1);
}

int main(int argc, char** argv) {
    test_max_chunks();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
