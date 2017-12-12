// Leetcode: https://leetcode.com/problems/evaluate-reverse-polish-notation/description/
// Evaluate the value of an arithmetic expression in Reverse Polish Notation.
// Valid operators are +, -, *, /. Each operand may be an integer or another expression.
// ["2", "1", "+", "3", "*"] -> ((2 + 1) * 3) -> 9
// ["4", "13", "5", "/", "+"] -> (4 + (13 / 5)) -> 6

// Brute Force:
// Better:

#include <stack>
#include <vector>
#include <string>
#include <iostream>
#include <assert.h>

// Accepted. 9ms. Beats 31.24% of submissions, ties 66.41% of submissions.
class Solution {
public:
    inline void eval(std::stack<int>& stack, char op) {
        auto right = stack.top();
        stack.pop();
        auto left = stack.top();
        stack.pop();

        switch (op) {
            case '+':
                stack.push(left + right);
                break;
            case '-':
                stack.push(left - right);
                break;
            case '*':
                stack.push(left * right);
                break;
            case '/':
                stack.push(left / right);
                break;
            default:
                assert(false);
        } 
    }

    int evalRPN(const std::vector<std::string>& tokens) {
        std::stack<int> stack;
        for (auto& token : tokens) {
            if (token == "+" || token == "-" || token == "*" || token == "/") {
                eval(stack, token[0]);
            } else {
                // Token should be a number
                stack.push(std::stol(token));
            }
        }
        return stack.top();       
    }
};

void test_rpn() {
    Solution soln;

    assert(soln.evalRPN({"2", "1", "/", "3", "6", "*", "+"}) == 20);
    assert(soln.evalRPN({"2", "1", "+", "3", "*"}) == 9);
    assert(soln.evalRPN({"4", "13", "5", "/", "+"}) == 6);
}

int main(int argc, char** argv) {
    test_rpn();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
