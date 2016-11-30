// Leetcode: https://leetcode.com/problems/number-of-1-bits/ 
// Given an unsigned integer, return the number of bits that are set (aka the Hamming weight).
// Example: 11 has binary representation 00000000000000000000000000001011 => return 3.

// Brute Force: Iterate the bits in the integer (e.g., right to left) testing each bit.
// O(n) time where n is the number of bits, but realy O(1) on 32 and 64-bit representations.
// Better: Use bit-masking tricks to test fewer bits (e.g., x & (x-1) clears the LSB that is set)
// Could also use a lookup table to count bits in each nibble, byte, or 2-byte half-word. 

#include <iostream>
#include <assert.h>

// Accepted. 3ms. Beats 22.22% of solutions, ties 77.78% of solutions.
class Solution {
public:
    int hammingWeight(uint32_t n) {
        int num_bits = 0;
        while (n > 0) {
            n = n & (n - 1);
            ++num_bits;
        }
        return num_bits;
    }
};

void test_hamming_weight() {
    Solution s;
    assert(s.hammingWeight(0) == 0);
    assert(s.hammingWeight(5) == 2);
    assert(s.hammingWeight(25) == 3);
    assert(s.hammingWeight(30934) == 9);
    assert(s.hammingWeight(4294967295) == 32);
}

int main(int argc, char** argv) {
    test_hamming_weight();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
