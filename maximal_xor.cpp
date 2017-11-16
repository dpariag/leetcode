// Leetcode: https://leetcode.com/problems/maximum-xor-of-two-numbers-in-an-array/
// Given a non-empty array of non-negative integers, find the maximum result of a[i]^a[j]
// for 0 <= i,j < n. Example: A = {3,10,5,25,2,8} the maximal xor is 25^5 = 28
// {00010, 01010, 00101, 11001, 00010, 01000}

// Brute Force: Compute the XOR of all pairs of integers, track max. O(n^2) time and O(1) space.
// Better: Iterate over the bits of the integer, from most significant to least significant.
// The maximal XOR is obtained by choosing a pair with the most significant bit set (if possible).
// So, divide the array into a sub-array of numbers with that bit set, and a sub-array of numbers
// without that bit set. The maximal XOR will use one number from each sub-array (if possible).
// Repeat this partitioning for each successively lower bit. O(n) time and O(n) space.

#include <vector>
#include <iostream>
#include <algorithm>
#include <assert.h>
//#include "bits.h"
//#include "numbers.h"

// Accepted. 49ms. Beats 96.74% of submissions, ties < 1% of submissions.
class Solution {
public:
    // Partition nums into two sets of integers: those with the given bit set,
    // and those with it cleared. Remove entries with the bit cleared from nums
    // and return them in a separate vector.
    std::vector<int> partition(std::vector<int>& nums, int bit) {
        std::vector<int> without_bit;
        int i = 0;

        while (i < nums.size()) {
            if ((nums[i] & bit) == 0) {
                without_bit.emplace_back(nums[i]);
                std::swap(nums[i], nums.back());
                nums.pop_back();
                continue;
            }
            ++i;
        }
        return without_bit;
    }

    inline int max_xor(const std::vector<int>& nums, int value) {
        int max = 0;
        for (auto n : nums) {
            max = std::max(max, n ^ value);
        }
        return max;
    }

    int find_maximal_xor(std::vector<int>& with_bit, std::vector<int>& without_bit, int next_bit) {
        if (with_bit.empty() || without_bit.empty()) { return 0; }

        if (next_bit == 0) {
            assert(!with_bit.empty() && !without_bit.empty());
            return with_bit.back() ^ without_bit.back();
        } else if (with_bit.size() == 1) {
            return max_xor(without_bit, with_bit.back());
        } else if (without_bit.size() == 1) {
            return max_xor(with_bit, without_bit.back());
        }

        auto with_no_next = partition(with_bit, next_bit);
        auto without_no_next = partition(without_bit, next_bit);
        auto max_1 = find_maximal_xor(with_bit, without_no_next, next_bit >> 1);
        auto max_2 = find_maximal_xor(without_bit, with_no_next, next_bit >> 1);
        auto max_3 = find_maximal_xor(with_no_next, without_no_next, next_bit >> 1);
        auto max_4 = find_maximal_xor(with_bit, with_no_next, next_bit >> 1);
        auto max_5 = find_maximal_xor(with_bit, without_bit, next_bit >> 1);
        return std::max({max_1, max_2, max_3, max_4, max_5});
    }

    int findMaximumXOR(std::vector<int>& nums) {
        int max = *(std::max_element(nums.begin(), nums.end()));
        int bit = (1 << 30);

        while (bit > 0 && (max & bit) == 0) { bit = bit >> 1; }

        std::vector<int> without_bit;
        while (without_bit.empty() && bit > 0) {
            without_bit = partition(nums, bit);
            bit = bit >> 1;
        }
        return find_maximal_xor(nums, without_bit, bit);
    }
    
    // A brute force O(n^2) solution for comparison 
    int brute_force(const std::vector<int>& nums) {
        int max = 0;
        for (auto i = 0; i < nums.size(); ++i) {
            for (auto j = i+1; j < nums.size(); ++j) {
                if ((nums[i] ^ nums[j]) > max) {
                    max = nums[i]^nums[j];
                }
            }
        }
        return max;
    }
};

bool test_maximal_xor(std::vector<int> nums, int expected_max) {
    Solution soln;
    return soln.brute_force(nums) == expected_max &&
           soln.findMaximumXOR(nums) == expected_max;
}

void test_maximal_xor() {
    assert(test_maximal_xor({14},0));
    assert(test_maximal_xor({0},0));
    assert(test_maximal_xor({14,15,9,3,2}, 13));
    assert(test_maximal_xor({4,6,7}, 3));
    assert(test_maximal_xor({8,9,1,2}, 11));
    assert(test_maximal_xor({8,1,2}, 10));
    assert(test_maximal_xor({8,1,9}, 9));
    assert(test_maximal_xor({8,7,6,5}, 15));
    assert(test_maximal_xor({8,9,10,1,2,3}, 11));
    assert(test_maximal_xor({9,10,11,8,3,5}, 15));
    assert(test_maximal_xor({3,10,5,25,2,8}, 28));
    assert(test_maximal_xor({14,70,53,83,49,91,36,80,92,51,66,70}, 127));
    assert(test_maximal_xor({8,9,1,4,3}, 13));
}

int main(int argc, char** argv) {
    test_maximal_xor();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
