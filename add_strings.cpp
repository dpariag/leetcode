// Leetcode: https://leetcode.com/problems/add-strings/description/
// Given two non-negative integers num1 and num2 represented as strings, return their sum.

// Method: Grade school addition. Iterate right to left, converting each character to an integer
// between 0-9. Sum digits, maintain the carry. O(n) time.

#include <vector>
#include <iostream>
#include <assert.h>

// Accepted. 6ms. Beats 79.73% of submissions, ties 19.03% of submissions.
class Solution {
public:
    std::string addStrings(std::string num1, std::string num2) {
        std::string result;
        result.reserve(std::max(num1.size(), num2.size())+1);
        int i = num1.size() - 1, j = num2.size() - 1;
        int carry = 0;

        while (i >= 0 || j >= 0) {
            int num1_digit = (i >= 0) ? (num1[i] - '0') : 0;
            int num2_digit = (j >= 0) ? (num2[j] - '0') : 0;
            int digit_sum = num1_digit + num2_digit;
            digit_sum += carry;
            carry = digit_sum / 10;
            digit_sum = digit_sum % 10;
            result.push_back('0' + digit_sum);
            --i; --j;
        }
        if (carry > 0) { result.push_back('0' + carry); }
        std::reverse(result.begin(), result.end());
        return result;
    }
};

void test_add_strings() {
    Solution soln;
    assert(soln.addStrings("99", "0") == "99");
    assert(soln.addStrings("0", "0") == "0");
    assert(soln.addStrings("10", "20") == "30");
    assert(soln.addStrings("100", "20") == "120");
    assert(soln.addStrings("209", "20") == "229");
    assert(soln.addStrings("99", "21") == "120");
    assert(soln.addStrings("99", "99") == "198");
    assert(soln.addStrings("928247", "9394302") == "10322549");
}

int main(int argc, char** argv) {
    test_add_strings();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
