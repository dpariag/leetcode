// Leetcode: https://leetcode.com/problems/rotate-array/
// Given a non-negative integer represented as a non-empty array (digits), add one to the integer.
// Assume digits does not have leading zeroes, and the most significant digit is at digits[0].

// Approach: Grade school addition with a carry. O(n) time and O(1) space.

#include <vector>
#include <algorithm>
#include <iostream>
#include <assert.h>

using Numbers = std::vector<int>;

// Accepted. 3ms. Beats 9.89% of submissions, ties 90.11% of submissions.
class Solution {
public:
    std::vector<int> plusOne(std::vector<int>& digits) {
        std::vector<int> result;
        int carry = 1;
        for (int i = digits.size()-1; i >= 0; --i) {
            auto sum = digits[i] + carry;
            result.emplace_back(sum % 10);
            carry = sum / 10;
        }
        if (carry > 0) { result.emplace_back(carry); }
        std::reverse(result.begin(), result.end());
        return result;
    }
};

bool test_plus_one(std::vector<int> digits, std::vector<int> expected) {
    Solution soln;
    auto answer = soln.plusOne(digits);
    return (answer == expected); 
}

void test_plus_one() {
    assert(test_plus_one({0}, {1}));
    assert(test_plus_one({1}, {2}));
    assert(test_plus_one({1,1}, {1,2}));
    assert(test_plus_one({1,9}, {2,0}));
    assert(test_plus_one({9,9,9}, {1,0,0,0}));
}

int main(int argc, char** argv) {
    test_plus_one();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
