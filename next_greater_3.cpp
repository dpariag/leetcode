// Leetcode: https://leetcode.com/problems/next-greater-element-iii/description/
// Given a positive 32-bit integer n, find the smallest 32-bit integer consisting of the same
// digits, which is greater than n. Return -1 if no such digit exists.

// Brute Force: Count up from given integer, checking if digits are the same.
// Better: Peel off and store least significant digits until a digit which is smaller than 
// it's predecessor is found. Replace that digit with the smallest stored digit which is larger
// then reapply remaining digits in ascending order. O(d) where d is the number of digits.
// Be careful to handle overflow!

#include <vector>
#include <iostream>
#include <assert.h>

// Accepted. 0ms. Beats 62.11% of submissions, ties 37.89% of submissions.
class Solution {
public:
    int nextGreaterElement(int n) {
        int original = n;
        std::vector<int> digits;
        digits.reserve(10);

        // Strip digits while they are non-decreasing
        digits.emplace_back(n % 10);
        n = n / 10;
        while (n > 0) {
            auto digit = n % 10;
            if (digit >= digits.back()) {
                digits.emplace_back(digit);
                n = n / 10;
            } else { break; }
        }
        if (n == 0) { return -1; } // never found a non-increasing digit

        int to_replace = n % 10;
        int i = 0;
        // Find smallest digit larger than to_replace
        for (; i < digits.size(); ++i) {
            if (digits[i] > to_replace) {
                std::swap(to_replace, digits[i]);
                break;
            }
        }
        if (i == digits.size()) { return -1; }  // never found a greater digit

        n = n / 10;
        n = (n*10) + to_replace;
        for (i = 0; i < digits.size(); ++i) {
            n = (n*10) + digits[i];
        }
        return (n > original) ? n : -1;
    }
};

void test_next_greater() {
    Solution soln;
    assert(soln.nextGreaterElement(23415) == 23451);
    assert(soln.nextGreaterElement(687112) == 687121);
    assert(soln.nextGreaterElement(12345) == 12354);
    assert(soln.nextGreaterElement(684361) == 684613);
    assert(soln.nextGreaterElement(54321) == -1);
    assert(soln.nextGreaterElement(9999) == -1);
    assert(soln.nextGreaterElement(824961) == 826149);
    assert(soln.nextGreaterElement(12222333) == 12223233);
    assert(soln.nextGreaterElement(1999999999) == -1);
}

int main(int argc, char** argv) {
    test_next_greater();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
