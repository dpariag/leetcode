// Leetcode: https://leetcode.com/problems/bitwise-and-of-numbers-range/description/
// Given a range [m, n] where 0 <= m <= n <= 2147483647, return the bitwise AND of all numbers in 
// the range, inclusive.
// Example: given the range [5, 7], you should return 4

// Brute Force: Iterate the range, to compute the result. O(S) where S is the range's size.
// Better: Determine the bits which do not change as the range is iterated. All other bits end up
// zeroed. O(n) where n is the number of bits, in this case n is fixed, so constant time.

#include <vector>
#include <iostream>
#include <assert.h>

// Accepted. 25ms. Beats 86.77% of submissions, ties 13.23% of submissions.
class Solution {
public:
    int rangeBitwiseAnd(int m, int n) {
        int mask = (1 << 30);
        int result = 0;

        while (mask > 0) {
            if ((mask & m) == (mask & n)) {
                result |= (mask & n);
            } else { break; }
            mask = mask >> 1;
        }
        return result;
    }
};

void test_range_bitwise_and() {
    Solution soln;

    assert(soln.rangeBitwiseAnd(5,7) == 4);
    assert(soln.rangeBitwiseAnd(0,7) == 0);
    assert(soln.rangeBitwiseAnd(1,7) == 0);
    assert(soln.rangeBitwiseAnd(0,0) == 0);
    assert(soln.rangeBitwiseAnd(7,7) == 7);
    assert(soln.rangeBitwiseAnd(7,8) == 0);
}

int main(int argc, char** argv) {
    test_range_bitwise_and();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
