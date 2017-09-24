// Leetcode: https://leetcode.com/problems/power-of-four/description/
// Given an integer (signed 32 bits), determine if it is a power of 4.

// Brute Force: Repeatedly divide the number by four, checking for remainders. O(log(num)).
// Better: Precompute powers of four, and compare against them.

#include <vector>
#include <iostream>
#include <assert.h>

// Accepted. 3ms. Ties 71.86% of submissions, ties 28.14% of submissions.
class Solution {
public:
    bool isPowerOfFour(int num) {
        return num == 1 << 0 || num == 1 << 2  || num == 1 << 4  || num == 1 << 6  || 
               num == 1 << 8  || num == 1 << 10 || num == 1 << 12 || num == 1 << 14 || 
               num == 1 << 16 || num == 1 << 18 || num == 1 << 20 || num == 1 << 22 || 
               num == 1 << 24 || num == 1 << 26 || num == 1 << 28 || num == 1 << 30;
    }
};

void test_power_of_four() {
    Solution soln;
    
    assert(soln.isPowerOfFour(0));
    assert(soln.isPowerOfFour(4));
    assert(soln.isPowerOfFour(8));
    assert(soln.isPowerOfFour(16));
    assert(soln.isPowerOfFour(64));
    assert(soln.isPowerOfFour(256));
    assert(soln.isPowerOfFour(1024));
    
    assert(!soln.isPowerOfFour(1));
    assert(!soln.isPowerOfFour(3));
    assert(!soln.isPowerOfFour(10));

}

int main(int argc, char** argv) {
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
