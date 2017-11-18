// Leetcode:
// Given two non-negative integers represented as strings, return their product

// Approach: Grade school multiplication with a carry. O(m*n) time

#include <vector>
#include <iostream>
#include <assert.h>

// Accepted. 13ms. Beats 25.59% of submissions, ties 3% of submissions
class Solution {
public:
    std::string add(const std::string& num1, const std::string& num2) {
        int carry = 0;
        int len1 = num1.size(), len2 = num2.size(), length = std::max(len1, len2);
        std::string result;
       
        for (int i = 0; i < length; ++i) {
            auto digit1 = (i < len1) ? int(num1[len1-i-1] - '0') : 0;
            auto digit2 = (i < len2) ? int(num2[len2-i-1] - '0') : 0;
            auto sum = digit1 + digit2 + carry;
            result.push_back(char('0' + sum % 10));
            carry = sum / 10;
        }

        if (carry) { result.push_back(char('0' + carry)); }
        std::reverse(result.begin(), result.end()); 
        return result;
    }

    std::string mult(const std::string& longer, const std::string& shorter) {
        if (longer == "0" || shorter == "0") { return "0"; }
        std::string product("0");
        for (int i = shorter.size() - 1; i >= 0; --i) {
            std::string temp;
            int carry = 0;
            auto s = int(shorter[i] - '0');
            auto num_zeroes = (shorter.size()-1) - i;
            for (int j = longer.size() - 1; j >= 0; --j) {
                auto l = int(longer[j] - '0');
                auto product = (s * l) + carry;
                temp.push_back('0' + (product % 10));
                carry = product / 10;
            }
            if (carry) { temp.push_back(char('0' + carry)); }
            std::reverse(temp.begin(), temp.end());
            temp.append(num_zeroes, '0');
            product = add(product, temp);
        }
        return product;
    }


    std::string multiply(const std::string& num1, const std::string& num2) {
        if (num1.size() < num2.size()) {
            return mult(num2, num1);
        }
        return mult(num1, num2);
    }
};

void test_multiply() {
    Solution soln;

    assert(soln.multiply("0", "0") == "0");
    assert(soln.multiply("1", "1") == "1");
    assert(soln.multiply("10", "1") == "10");
    assert(soln.multiply("10", "10") == "100");
    assert(soln.multiply("100", "10") == "1000");
    assert(soln.multiply("10", "100") == "1000");
    assert(soln.multiply("99", "9") == "891");
    assert(soln.multiply("99", "99") == "9801");
    assert(soln.multiply("29402", "10024") == "294725648");
    assert(soln.multiply("29402", "0") == "0");
}

void test_add() {
    Solution soln;
    assert(soln.add("0", "0") == "0");
    assert(soln.add("1", "1") == "2");
    assert(soln.add("1", "0") == "1");
    assert(soln.add("99", "9") == "108");
    assert(soln.add("99", "0") == "99");
    assert(soln.add("99", "99") == "198");
}

int main(int argc, char** argv) {
    test_add();
    test_multiply();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
