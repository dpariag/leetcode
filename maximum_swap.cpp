// Leetcode: https://leetcode.com/problems/maximum-swap/description/
// Given a non-negative integer, return the largest number that can be obtained by swapping 
// two digits at most once.

// Brute Force: Perform all possible single swaps, and track the max.
// Better: Scan the digits right to left looking for the leftmost swap that yields a larger number.

#include <vector>
#include <iostream>
#include <algorithm>
#include <assert.h>

// Accepted. 3ms. Beats 13.91% of submissions, ties 84.05% of submissions.
class Solution {
public:
    int maximumSwap(int num) {
        if (num == 0) { return 0; }
        // Extract the digits of num
        std::vector<int> digits;
        while (num != 0) {
            digits.push_back(num % 10);
            num /= 10;
        }
        
        // Find the largest digit
        int max = std::numeric_limits<int>::min();
        int max_index = -1, left = -1, right = -1;
        for (int i = 0; i < digits.size(); ++i) {
            if (max > digits[i]) { left = i, right = max_index; }
            if (digits[i] > max) {
                max = digits[i];
                max_index = i;
            }
        }
        
        // Swap if we found two digits to swap
        if (left != -1) {
            std::swap(digits[left], digits[right]);
        }

        int max_swap = 0;
        for (int i = digits.size() - 1; i >= 0; --i) {
            max_swap *= 10;
            max_swap += digits[i];
        }
        return max_swap;
    }
};

void test_max_swap() {
    Solution soln;
    assert(soln.maximumSwap(1) == 1);
    assert(soln.maximumSwap(10) == 10);
    assert(soln.maximumSwap(109) == 901);
    assert(soln.maximumSwap(199) == 991);
    assert(soln.maximumSwap(2736) == 7236);
    assert(soln.maximumSwap(77787) == 87777);
    assert(soln.maximumSwap(98368) == 98863);
    assert(soln.maximumSwap(975318) == 985317);
}

int main(int argc, char** argv) {
    test_max_swap();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
