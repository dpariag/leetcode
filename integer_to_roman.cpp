// Leetcode: https://leetcode.com/problems/integer-to-roman/description/
// Given an integer between 1 and 3999, convert it to a roman numeral.

// Approach: Store a sorted (descending order) table mapping integer values to their roman equivalents.
// Repeatedly subtract the highest value possible, appending the roman equivalent to the result. O(n) time.

#include <vector>
#include <iostream>
#include <assert.h>

struct Numeral {
    int number = 0;
    std::string roman;
};

// Accepted. 91ms. Beats 58.55% of submissions.
class Solution {
public:
    std::string intToRoman(int num) {
        static const Numeral numerals[13] = {{1000, "M"},{900, "CM"},{500, "D"},{400, "CD"}, 
                                             {100, "C"},{90, "XC"},{50, "L"},{40, "XL"},
                                             {10, "X"},{9, "IX"},{5, "V"},{4, "IV"},{1, "I"}};
        std::string result;
        result.reserve(20);
        int start_idx = 0;
        while (num > 0) {
            for (int i = start_idx; i < 13; ++i) {
                if (numerals[i].number <= num) {
                    result.append(numerals[i].roman);
                    num -= numerals[i].number;
                    start_idx = i;
                    break;
                }
            }
        }
        return result;
    }
};

void test_roman() {
    Solution soln;

    assert(soln.intToRoman(1) == "I");
    assert(soln.intToRoman(3) == "III");
    assert(soln.intToRoman(4) == "IV");
    assert(soln.intToRoman(5) == "V");
    assert(soln.intToRoman(6) == "VI");
    assert(soln.intToRoman(9) == "IX");
    assert(soln.intToRoman(10) == "X");
    assert(soln.intToRoman(23) == "XXIII");
    assert(soln.intToRoman(760) == "DCCLX");
    assert(soln.intToRoman(967) == "CMLXVII");
    assert(soln.intToRoman(2789) == "MMDCCLXXXIX");
    assert(soln.intToRoman(3088) == "MMMLXXXVIII");
}

int main(int argc, char** argv) {
    test_roman();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
