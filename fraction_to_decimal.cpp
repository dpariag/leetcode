// Leetcode: https://leetcode.com/problems/fraction-to-recurring-decimal/description/
// Given two integers representing the numerator and denominator of a fraction, return the fraction in string format.
// If the fractional part is repeating, enclose the repeating part in parentheses.

// Approach: Figure out integer portion (left of decimal point), then compute the fraction (right of decimal point)
// Fraction is computed by multiplying the numerator by 10 and dividing by the denominator.
// The remainder is the next numerator. Detect recurring decimals using a hash map from numerator -> index in result.

#include <string>
#include <limits>
#include <unordered_map>
#include <iostream>
#include <assert.h>

using DigitMap = std::unordered_map<int, int>; // Map a numerator to the digit it produced in result

// Accepted. 0ms. Beats 46.47% of submissions, ties 53.53% of submissions.
class Solution {
public:
    std::string fractionToDecimal(int n, int d) {
        if (d == 0) { return "NaN"; }
        int64_t numerator = n, denominator = d;
        DigitMap digit_map;
        std::string result;

        if ((numerator < 0 && denominator > 0) || (denominator < 0 && numerator > 0)) {
            result.append(1, '-');
        }
        numerator = std::abs(numerator);
        denominator = std::abs(denominator);
        result.append(std::to_string(numerator/denominator));
        numerator = numerator % denominator;

        if (numerator != 0) { result.append(1, '.'); }
        
        while (numerator != 0) {
            auto found = digit_map.find(numerator);
            if (found != digit_map.end()) {
                result.insert(found->second, 1, '(');
                result.append(1, ')');
                return result;
            } else {
                auto orig_numerator = numerator;
                numerator = numerator * 10;
                auto digit = numerator / denominator;
                result.append(std::to_string(digit));
                digit_map[orig_numerator] = result.size() - 1;
                numerator = numerator % denominator;
            }
        }
        return result;
    }
};

static const int MAX_INT = std::numeric_limits<int>::max();
static const int MIN_INT = std::numeric_limits<int>::min();

void test_fraction_to_decimal() {
    Solution soln;

    assert(soln.fractionToDecimal(2,0) == "NaN");
    assert(soln.fractionToDecimal(0,2) == "0");
    assert(soln.fractionToDecimal(2,1) == "2");
    assert(soln.fractionToDecimal(2,-1) == "-2");
    assert(soln.fractionToDecimal(-2,1) == "-2");
    assert(soln.fractionToDecimal(-2,-1) == "2");
    assert(soln.fractionToDecimal(1,2) == "0.5");
    assert(soln.fractionToDecimal(1,3) == "0.(3)");
    assert(soln.fractionToDecimal(2,3) == "0.(6)");
    assert(soln.fractionToDecimal(2,11) == "0.(18)");
    assert(soln.fractionToDecimal(2,-11) == "-0.(18)");
    assert(soln.fractionToDecimal(1,4) == "0.25");
    assert(soln.fractionToDecimal(2, 1000) == "0.002");
    assert(soln.fractionToDecimal(4,11) == "0.(36)");
    assert(soln.fractionToDecimal(MIN_INT,-1) == "2147483648");
    assert(soln.fractionToDecimal(MIN_INT, MIN_INT) == "1");
    assert(soln.fractionToDecimal(MAX_INT, MAX_INT) == "1");

}

int main(int argc, char** argv) {
    test_fraction_to_decimal();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
