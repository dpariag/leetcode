// Leetcode: https://leetcode.com/problems/basic-calculator-ii/description/
// Implement a calculator to evaluate an expression string.
// The expression contains non-negative integers, +, -, *, / operators and empty spaces.

// Approach: Process string left to right parsing <integer><op><integer> elements.
// Use a stack to collect integers to be summed in a second pass.
// Multiplication and division are evaluated in the first pass and pushed onto the stack.
// Addition and subtraction operands are pushed onto the stack (subtraction operands are negated)
// The second pass sums all results. O(n) time and space.

#include <vector>
#include <iostream>
#include <assert.h>

// Accepted. 13ms. Beats 53.16% of submissions, ties 27.48% of submissions.
class Solution {
public:
    // Parse an integer from s, starting at offset i and consuming surrounding whitespace.
    inline int parse_int(const std::string& s, int& i) {
        while (std::isspace(s[i])) { ++i; }
        int result = 0;
        while (i < s.size() && std::isdigit(s[i])) {
            result = (result * 10) + (s[i] - '0');
            ++i;
        }
        while (std::isspace(s[i])) { ++i; }
        return result;
    }

    int calculate(const std::string& s) {
        std::vector<int> stack;
        int result = 0, left = 0, right = 0, i = 0;
        char last_op = '\0';
        left = parse_int(s, i);

        while (i < s.size()) {
            auto op = s[i++];
            right = parse_int(s, i);

            if (op == '+') {
                left = last_op == '-'? -left : left;
                stack.push_back(left);
                left = right;
                last_op = '+';
            } else if (op == '-') {
                left = last_op == '-'? -left : left;
                stack.push_back(left);
                left = right;
                last_op = '-';
            } else if (op == '*') {
                left = left * right;
            } else if (op == '/') {
                left = left / right;
            }
        }
        left = last_op == '-'? -left : left;
        stack.push_back(left);

        for (auto item : stack) {
            result += item;
        }
        return result;
    }
};

void test_calculator() {
    Solution soln;

    assert(soln.calculate(" 10  /5-2   *2  /4+ 5 ") == 6);
    assert(soln.calculate("10/5-2*2/4+5") == 6);
    assert(soln.calculate("10-1*2/4+5") == 15);
    assert(soln.calculate("10-1*2*4+5") == 7);
    assert(soln.calculate("10-1*2*4") == 2);
    assert(soln.calculate("1-1*2") == -1);
    assert(soln.calculate("1-1-2") == -2);
    assert(soln.calculate("1+1-2") == 0);
    assert(soln.calculate("1+1+2") == 4);
    assert(soln.calculate("1+1") == 2);
    assert(soln.calculate("1") == 1);
}

int main(int argc, char** argv) {
    test_calculator();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
