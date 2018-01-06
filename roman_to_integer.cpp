// Leetcode: https://leetcode.com/problems/roman-to-integer/description/
// Given a roman numeral in the range [1,3999], convert it to an integer.

// Approach: Scan the roman numeral from left to right adding digit values, 
// unless the digit is followed by a larger one, in which case subtract the digit value.
// O(n) time.

#include <string>
#include <unordered_map>
#include <iostream>
#include <assert.h>

using NumeralMap = std::unordered_map<char, int>;

// Accepted. 65ms. Beats 77.27% of submissions, ties 5.14% of submissions.
class Solution {
public:
    int romanToInt(const std::string& s) {
        NumeralMap numeral_map = {{'I',1},{'V', 5},{'X',10},{'L',50},{'C',100},{'D',500},{'M',1000}};
        int value = 0, digit_value = numeral_map[s[0]], next_digit_value = 0;
        for (int i = 0; i < s.size(); ++i) {
            next_digit_value = i+1 < s.size() ? numeral_map[s[i+1]] : 0;
            if (digit_value < next_digit_value) {
                value -= digit_value;
            } else {
                value += digit_value;
            }
            digit_value = next_digit_value;
        }
        return value;
    }
};

void test_roman_to_int() {
    Solution soln;

    assert(soln.romanToInt("I") == 1);
    assert(soln.romanToInt("II") == 2);
    assert(soln.romanToInt("III") == 3);
    assert(soln.romanToInt("IV") == 4);
    assert(soln.romanToInt("V") == 5);
    assert(soln.romanToInt("VI") == 6);
    assert(soln.romanToInt("VII") == 7);
    assert(soln.romanToInt("VIII") == 8);
    assert(soln.romanToInt("IX") == 9);
    assert(soln.romanToInt("X") == 10);
    assert(soln.romanToInt("XI") == 11);
    assert(soln.romanToInt("XII") == 12);
    assert(soln.romanToInt("LI") == 51);
    assert(soln.romanToInt("CX") == 110);
    assert(soln.romanToInt("DCX") == 610);
    assert(soln.romanToInt("DX") == 510);
    assert(soln.romanToInt("MMMDCCCCXXXXXXXXXIX") == 3999);
}

int main(int argc, char** argv) {
    test_roman_to_int();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
