// Leetcode: https://leetcode.com/problems/total-hamming-distance/description/
// The Hamming distance between two integers is the number of corresponding bits which differ.
// Find the total Hamming distance between all integer pairs in an array.

// Brute Force: Generate all pairs of integers, compute their Hamming distance. O(n^2) time.
// Better: For each bit, count the number of integers with the bit set vs. unset. The Hamming
// distance due to that bit is (num_set * num_unset). Repeat for remaining bits. O(n) time.

#include <vector>
#include <iostream>
#include <assert.h>

// Accepted. 63ms. Beats 68.33% of submissions, ties 6.06% of submissions.
class Solution {
public:
    int totalHammingDistance(const std::vector<int>& nums) {
        int total_distance = 0;
        int mask = 1;
        int size = int(nums.size());

        while (mask != 0 && mask <= max) {
            int num_with_bit_set = 0;
            for (auto num : nums) {
                if (num & mask) { ++num_with_bit_set; }
            }
            total_distance += (num_with_bit_set * (size - num_with_bit_set));
            mask = mask << 1;
        }
        return total_distance;
    }
};

void test_total_hamming_distance() {
    Solution soln;

    assert(soln.totalHammingDistance({}) == 0);
    assert(soln.totalHammingDistance({1,2,3,4}) == 11);
}


int main(int argc, char** argv) {
    test_total_hamming_distance();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
