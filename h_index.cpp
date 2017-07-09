// Leetcode: https://leetcode.com/problems/h-index/#/description
// Given an array A, where A[i] is the # of citations for a researcher's i'th paper,  write a 
// function to compute the researcher's h-index. A scientist has index h if h of her N papers 
// have at least h citations, and the other N − h papers h or fewer citations."

// Brute Force: For h = n-1..0, iterate the array to calculate if h is a valid h-index. O(n^2) time.
// Better: Sort the array, then iterate. At each iteration, partition the array into two subarrays.
// Check if left subarray has <= h citations, and right subarray has h items with >= h citations.
// O(n*logn) time and O(n) space.

#include <vector>
#include <algorithm>
#include <iostream>
#include <assert.h>

class Solution {
public:
    int hIndex(std::vector<int>& citations) {
        int size = citations.size();
        std::sort(citations.begin(), citations.end());
        for (int i = 0; i < size; ++i) {
            int h = size - i; // # of items ahead incl. citations[i]
            if (citations[i] >= h) {
                // h items of at least h, N-h items at most h
                return h;
            }
        }
        return 0;
    }
};

bool test_h_index(std::vector<int> citations, int expected) {
    Solution soln;
    return (soln.hIndex(citations) == expected);
}

void test_h_index() {
    assert(test_h_index({}, 0));
    assert(test_h_index({0}, 0));
    assert(test_h_index({0,0,0,0}, 0));
    assert(test_h_index({1}, 1));
    assert(test_h_index({11}, 1));
    assert(test_h_index({0,1,1}, 1));
    assert(test_h_index({0,1,3,3,3}, 3));
    assert(test_h_index({0,2,3,3,3}, 3));
    assert(test_h_index({0,3,3,3,3}, 3));
    assert(test_h_index({3,3,3,3,3}, 3));
    assert(test_h_index({0,5,5,5,5}, 4));
    assert(test_h_index({5,5,5,5,5}, 5));
    assert(test_h_index({5,5,5,5,5,6}, 5));
    assert(test_h_index({100,100}, 2));
    assert(test_h_index({3,0,6,1,5}, 3));
    assert(test_h_index({0,0,0,0,2,2}, 2));
    assert(test_h_index({0,0,0,0,2,2,3}, 2));
    assert(test_h_index({0,0,0,0,3,4,5}, 3));
}

int main(int argc, char** argv) {
    test_h_index();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
