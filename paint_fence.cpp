// Leetcode: https://leetcode.com/problems/wiggle-sort/description/
// Given a fence with n (n >= 0) posts, each post can be painted with one of the k (k >= 0)colors.
// Return the total number of ways the fence can be painted if no more than two adjacent posts
// can have the same color

// Brute Force: Recursive enumeration. Can memoize to get O(n*k) time and space.
// Better: Derive a recurrence for O(n) time and O(1) space.
// Assume there are ways_i different ways to paint i posts.
// Of those, some have the same last 2 colours, other have different last 2 colours.
// The i+1'th post can be painted in: ways_i = (diff)*k + same*(k-1). Must recalculate same and diff.

#include <vector>
#include <iostream>
#include <assert.h>

// Accepted. 0ms. Beats 23.24% of submissions, ties 76.76% of submissions.
class Solution {
public:
    int numWays(int n, int k) {
        // Special cases
        if (n == 0 || k == 0) { return 0; }
        if (n == 1) { return k; }
        if (k == 1) { return (n <= 2) ? 1 : 0; }

        int ways = k * k, same = k; // n == 2
        int diff = ways - same;
        for (int i = 3; i <= n; ++i) {
            // If last 2 are different, then k valid choices for next (diff * k)
            // If last 2 are the same then k-1 valid choics for next (same*(k-1))
            ways = (diff*k) + same*(k-1);
            same = diff;            // i-1'th and i-2'th were different. Added k colours (diff*k). 
                                    // diff of those end up with last 2 same.
            diff = ways - same;
        }
        return ways;
    }
};

void test_num_ways() {
    Solution soln;

    assert(soln.numWays(3,2) == 6);
    assert(soln.numWays(3,3) == 24);
    assert(soln.numWays(4,3) == 66);
}


int main(int argc, char** argv) {
    test_num_ways();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
