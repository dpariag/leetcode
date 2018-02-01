// Leetcode: https://leetcode.com/problems/count-numbers-with-unique-digits/description/
// Given a non-negative integer n, count all numbers with unique digits, x, where 0 ≤ x < 10^n.

// Brute Force: Enumerate all numbers between 0 and 10^n, check which ones have unique digits. O(10^n)
// Better: For n > 2, there are 9 choices for the 1st digit, 9 choices for the 2nd, 8 for the 3rd,
// 7 for the 4th and so on. Codify this sequence. O(n) time.

#include <vector>
#include <iostream>
#include <assert.h>

// Accepted. 2ms. Beats 16.27% of submissions, ties 12.48% of submissions.
class Solution {
public:
    int countNumbersWithUniqueDigits(int n) {
        if (n == 0) { return 1; }
        if (n == 1) { return n*10; }

        // Can't have leading zeroes, so n = 1 --> 9 numbers, with 9 available digits remaining
        int total = 10, count = 81, available = 8;
        for (int num_digits = 2; num_digits <= n; ++num_digits) {
            total += count;
            count *= available;
            --available;            
        }
        return total;
    }
};

void test_unique_digits() {
    Solution soln;

    assert(soln.countNumbersWithUniqueDigits(0) == 1);
    assert(soln.countNumbersWithUniqueDigits(1) == 10);
    assert(soln.countNumbersWithUniqueDigits(2) == 91);
    assert(soln.countNumbersWithUniqueDigits(3) == 739);
}

int main(int argc, char** argv) {
    test_unique_digits();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}