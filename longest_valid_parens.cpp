// Leetcode: https://leetcode.com/problems/longest-valid-parentheses/
// Given a string containing only '(' and ')', find the length of the longest, well-formed substring.
// Example: "(()", ==> return 2, ")()())" ==> return 4.

// Brute Force: Form all possible substrings, determine if each is well-formed, track max. 
// O(n^3) time and O(n) space.
// Better: Use a stack to track the index of the last matched '('. Iterate the string, pushing
// indices of '(' and unmatched ')' characters. If a match is possible, calculate the length
// of the matched string using stack.top(). O(n) time and space.

#include <stack>
#include <string>
#include <iostream>
#include <assert.h>

// Accepted. 9ms. Beats 43.94% of submissions, ties 39.25% of submissions.
class Solution {
public:
    int longestValidParentheses(const std::string& s) {
        int max_length = 0;
        std::stack<int> indices;

        for (int i = 0; i < s.size(); ++i) {
            auto ch = s[i];
            if (ch == '(') {
                indices.push(i);
            } else {
                // ch == ')'
                if (!indices.empty() && s[indices.top()] == '(') {
                    indices.pop();
                    int start = indices.empty() ? -1 : indices.top();
                    max_length = std::max(max_length, i - start);
                } else {
                    indices.push(i);
                }
            }
        }
        return max_length;
    }
};

void test_longest_valid_parens() {
    Solution soln;
    assert(soln.longestValidParentheses("()(()") == 2);
    assert(soln.longestValidParentheses("(()") == 2);
    assert(soln.longestValidParentheses(")()())") == 4);
    assert(soln.longestValidParentheses("((()))()()(())") == 14);
    assert(soln.longestValidParentheses("((())))()()(())") == 8);
    assert(soln.longestValidParentheses("((()))()(()(())") == 8);
    assert(soln.longestValidParentheses(")((()))()(()(())") == 8);
    assert(soln.longestValidParentheses(")((()))()(()(())(") == 8);
    assert(soln.longestValidParentheses("))((") == 0);
    assert(soln.longestValidParentheses("))((()") == 2);
    assert(soln.longestValidParentheses("()()))((()()()") == 6);
}

int main(int argc, char** argv) {
    test_longest_valid_parens();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
