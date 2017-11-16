// Leetcode: https://leetcode.com/problems/increasing-triplet-subsequence/#/description 
// Given an unsorted array return true if there exists i, j, k 
// such that arr[i] < arr[j] < arr[k] given 0 ≤ i < j < k ≤ n-1 else return false.

// Brute Force: Generate all possible triples, check if any is increasing. O(n^3)
// Better: Scan the array, tracking:
//  1) min: the minimum element so far 
//  2) middle: smallest element larger than the current min 
//  3) first element  larger than middle
//  O(n) time and O(1) space

#include <vector>
#include <iostream>
#include <limits>
#include <assert.h>

// Accepted. 6ms. Beats 31.25% of submissions, ties 68.26% of submissions.
class Solution {
public:
    bool increasingTriplet(const std::vector<int>& nums) {
        if (nums.size() < 3) { return false; }
        int min = std::numeric_limits<int>::max();
        int middle = std::numeric_limits<int>::max();

        for (auto num : nums) {
            if (num <= min) {
                // New minimum (i.e., start a new triplet)
                // Don't reset middle, we may be able to complete the previous triplet.
                min = num;
            } else if (num <= middle) {
                // Larger than current min, smaller than current middle
                // A smaller middle makes it easier to commplete the triplet
                middle = num;
            } else {
                // Larger than min and larger than middle. Completes the triplet
                return true;
            }
        }
        return false;
    }
};

void test_increasing_triplet() {
    Solution soln;
    assert(soln.increasingTriplet({}) == false);
    assert(soln.increasingTriplet({1}) == false);
    assert(soln.increasingTriplet({1,2}) == false);
    assert(soln.increasingTriplet({1,2,3}) == true);
    assert(soln.increasingTriplet({0,1,2,3}) == true);
    assert(soln.increasingTriplet({1,0,2,3}) == true);
    assert(soln.increasingTriplet({1,2,0,3}) == true);
    assert(soln.increasingTriplet({1,2,3,0}) == true);
    assert(soln.increasingTriplet({5,4,3,1,2,3,0}) == true);
    assert(soln.increasingTriplet({1,2,3,0,5,3,3,1,1}) == true);
    assert(soln.increasingTriplet({1,2,3,0,1,1,1,1,1}) == true);
    assert(soln.increasingTriplet({1,2,0,1,1,3,1,1}) == true);
    assert(soln.increasingTriplet({1,0,20,1,19,10,11,12,0,1,1,0,1,0}) == true);
    assert(soln.increasingTriplet({1,0,18,19,20,1,19,12,0,1,1,0,1,0}) == true);
}

int main(int argc, char** argv) {
    test_increasing_triplet();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
