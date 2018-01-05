// Leetcode: https://leetcode.com/problems/hamming-distance/description/
// Given two integers x and y, calculate their Hamming distance.

// Brute Force: Iterate the integers looking for differing bits. O(n) time.
// Better: Use XOR to collect different bits. Count using a loookup table. O(n) time, but smaller constant.

#include <vector>
#include <limits>
#include <iostream>
#include <assert.h>

// Accepted. 3ms. Beats 23.73% of submissions, ties 76.27% of submissions
class Solution {
public:
    int hammingDistance(int x, int y) {
        int bit_counts[16] = {0,1,1,2,1,2,2,3,1,2,2,3,2,3,3,4}; // Number of bits set in 0-15        
        int different = x ^ y;
        int mask = 15;
        int distance = 0;

        distance += bit_counts[different & mask];
        distance += bit_counts[(different & (mask << 4)) >> 4];
        distance += bit_counts[(different & (mask << 8)) >> 8];
        distance += bit_counts[(different & (mask << 12)) >> 12];
        distance += bit_counts[(different & (mask << 16)) >> 16];
        distance += bit_counts[(different & (mask << 20)) >> 20];
        distance += bit_counts[(different & (mask << 24)) >> 24];
        distance += bit_counts[(different & (mask << 28)) >> 28];
        return distance;
    }
};

static const int MAX_INT = std::numeric_limits<int>::max();
void test_hamming_distance() {
    Solution soln;

    assert(soln.hammingDistance(MAX_INT,0) == 31);
    assert(soln.hammingDistance(0,0) == 0);
    assert(soln.hammingDistance(0,1) == 1);
    assert(soln.hammingDistance(1,0) == 1);
    assert(soln.hammingDistance(1,1) == 0);
    assert(soln.hammingDistance(2,1) == 2);
    assert(soln.hammingDistance(4,1) == 2);    
}

int main(int argc, char** argv) {
    std::cout << MAX_INT << std::endl;
    test_hamming_distance();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
