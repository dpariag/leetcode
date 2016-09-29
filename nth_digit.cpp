// Leetcode: https://leetcode.com/problems/nth-digit/
// Find the nth digit of the infinite integer sequence 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, ...
// where 0 < n <= 2^31.
// Example: n = 3 ==> return 3. n = 11 ==> return 0 (0 from the number 10, is the 11th digit) 

// Idea: Map n to a tuple (number, digit_index). For example, 30 maps to (20,0) which means
// return the 0'th digit of 20, where digits are numbered left to right.
// Note that there are 9 numbers with one digit (1-9), 90 numbers with two digits (10-99),
// 900 numbers with 3 digits (100-999), etc.

#include <iostream>
#include <assert.h>

// Runtime 0ms. Beats 26.16% of submissions, and ties 73.84% of submissions
class Solution {
public:
    int findNthDigit(int n) {
        // Find the range that n lies in (e.g., 1-9, 10-99, 100-999, etc.)
        uint64_t number_start = 1, range_start = 1, range_end = 9, range_size = 9;
        uint64_t num_digits = 1;

        while (range_end < n) {
            range_start += (range_size * num_digits);
            range_size  *= 10;
            number_start *= 10;
            ++num_digits;
            range_end += (range_size * num_digits);
        }

        // Map n to a number in the range. 
        // For example, the 100th digit in the sequence comes from the number 55
        int number = number_start + ((n - range_start) / num_digits);
        int digit = (n - range_start) % num_digits; 
        int digit_index = num_digits - 1;
        int cur_digit = number % 10;
       
        // Extract the appropriate digit of the number 
        while (digit_index > digit) {
            --digit_index;
            number = number / 10;
            cur_digit = number % 10;
        }
        return cur_digit;
    }
};

void test_nth_digit() {
    Solution soln;
    assert(soln.findNthDigit(1) == 1);
    assert(soln.findNthDigit(5) == 5);
    assert(soln.findNthDigit(10) == 1);     // '1' from 10
    assert(soln.findNthDigit(15) == 2);     // '2' from 12
    assert(soln.findNthDigit(30) == 2);     // '2' from 20 
    assert(soln.findNthDigit(31) == 0);     // '0' from 20 
    assert(soln.findNthDigit(100) == 5);    // '5' from 55
    assert(soln.findNthDigit(190) == 1);    // '1' from 100 
    assert(soln.findNthDigit(191) == 0);    // first '0' from 100 
    assert(soln.findNthDigit(192) == 0);    // last '0' from 100 
    assert(soln.findNthDigit(195) == 1);    // last '1' from 101 
    assert(soln.findNthDigit(2998) == 1);   // '1' from 1027
    assert(soln.findNthDigit(2999) == 0);   // '0' from 1027
    assert(soln.findNthDigit(3000) == 2 );  // '2' from 1027
    assert(soln.findNthDigit(3001) == 7);   // '7' from 1027
    assert(soln.findNthDigit(1000000000) == 1);    // from leetcode 
}

int main(int argc, char** argv) {
    test_nth_digit();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
