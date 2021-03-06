// Leetcode: https://leetcode.com/problems/reverse-integer/
// Reverse digits of an integer. Return 0 if the reversed integer overflows.
// Example: given x = 123, return 321 given x = -123, return -321

// Brute Force: Convert the integer to a string, reverse it, and convert back to an integer.
// Better: Extract the rightmost digit, and append it to a new integer. Repeat. O(d) time.

#include <iostream>
#include <limits>
#include <assert.h>

// Accepted. 16ms. Beats 41.19% of submissions, ties 8.3% of submissions
class Solution {
public:
    int reverse(int x) {
        const int overflow_limit = std::numeric_limits<int>::max() / 10;
        int result = 0;
        bool negative = (x < 0);
        x = (negative ? -x : x);

        while (x > 0) {
            if (result > overflow_limit) { return 0; }
            result = (result*10) + (x % 10);
            x = x / 10;
        }
        return (negative ? -result : result);
    }
};

void test_reverse() {
    Solution soln;
    assert(soln.reverse(1534236469) == 0);
    assert(soln.reverse(0) == 0);
    assert(soln.reverse(2) == 2);
    assert(soln.reverse(-2) == -2);
    assert(soln.reverse(123) == 321);
    assert(soln.reverse(-123) == -321);
    assert(soln.reverse(1000000009) == 0);
}

int main(int argc, char** argv) {
    test_reverse();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
