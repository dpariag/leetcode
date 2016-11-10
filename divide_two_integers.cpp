// Leetcode: https://leetcode.com/problems/divide-two-integers/
// Divide two integers without using multiplication, division and mod operator.
// If it is overflow, return MAX_INT.

// Note that addition, subtraction, and bitwise operations are permitted
// Brute Force: Add divisor to itself until it would exceed dividend. O(dividend/divisor)
// Better: Use bitshifting to compute divisor, divisor*2, divisor*4, etc, then find the sum of
// divisor multiples that yields dividend. O(log(dividend)) time and space.
// This is similar to computing the binary representation of a number (divisor = 2)

#include <vector>
#include <iostream>
#include <assert.h>
#include <limits>

const int c_max_int = std::numeric_limits<int>::max();
const int c_min_int = std::numeric_limits<int>::min();
const int c_half_min_int = std::numeric_limits<int>::min() >> 1;

// Accepted. 6ms. Beats 82.54% of submissions, ties 17.46% (with some variability)
class Solution {
public:
    int divide(int dividend, int divisor) {
        // Handle a few special cases
        if (divisor == 0) { return std::numeric_limits<int>::max(); }
        if (dividend == c_min_int && divisor == -1) { return c_max_int; }
        if (dividend == c_max_int && divisor == -1) { return c_min_int; }

        // Perform the calculation using negative numbers, because
        // std::abs(MIN_INT) = std::abs(MAX_INT) + 1, so avoids overflow
        bool negate_result = (dividend > 0 && divisor > 0) || (dividend < 0 && divisor < 0);
        if (dividend > 0) { dividend = -dividend; } 
        if (divisor > 0) { divisor = -divisor; }

        // Find the largest multiple of divisor that fits in dividend
        int multiple = divisor;
        int max_power = 1;
        while (multiple >= dividend && multiple >= c_half_min_int) {
            multiple = multiple << 1;
            ++max_power;
        }

        // Count the multiples of divisor that fit in dividend
        int result = 0;
        for (int i = max_power - 1; i >= 0; --i) {
            if (multiple >= dividend) {
                result += (-1 << i);
                dividend -= multiple;
            }
            multiple = multiple >> 1;
        }
        return negate_result ? -result : result;
    }
};

void test_divide() {
    Solution soln;
    assert(soln.divide(c_min_int, -1) == c_max_int);
    assert(soln.divide(1,0) == c_max_int);  // divide by zero
    assert(soln.divide(1,1) == 1);          // divide by one
    assert(soln.divide(1,-1) == -1);        // divide by -1
    assert(soln.divide(-1,1) == -1);        // negative dividend
    assert(soln.divide(-1,-1) == 1);
    assert(soln.divide(2,1) == 2);
    assert(soln.divide(12,3) == 4);
    assert(soln.divide(13,3) == 4);         // dividend % divisor != 0
    assert(soln.divide(14,3) == 4);
    assert(soln.divide(15,3) == 5);         // exact division
    assert(soln.divide(3,15) == 0);         // zero result
    assert(soln.divide(3,4) == 0);
    assert(soln.divide(3,3) == 1);
    assert(soln.divide(3,2) == 1);
    assert(soln.divide(3,1) == 3);
    assert(soln.divide(-6,3) == -2);
    assert(soln.divide(-593,3) == -197);
    assert(soln.divide(-593, -3) == 197);               // negative divisor
    assert(soln.divide(c_max_int, 1) == c_max_int);     // division of max int
    assert(soln.divide(c_max_int, 6) == c_max_int / 6);
    assert(soln.divide(c_max_int, 1024) == c_max_int / 1024);
    assert(soln.divide(c_max_int, -1024) == c_max_int / -1024);
    assert(soln.divide(c_max_int, c_max_int) == 1);
    assert(soln.divide(c_min_int, 2) == c_min_int / 2);
}

int main(int argc, char** argv) {
    test_divide();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
