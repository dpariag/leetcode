// Leetcode: https://leetcode.com/problems/longest-valid-parentheses/
// Given a string containing only '(' and ')', find the length of the longest, well-formed substring.
// Example: "(()", ==> return 2, ")()())" ==> return 4.

// Brute Force: Form all possible substrings, determine if each is well-formed, track max. 
// O(n^3) time and O(n) space.
// Better: Dynamic programming. Build a table of booleans, where table[i][j] is true iff
// s[i..j] is a well-formed substring. Table can be built in O(n^2) time and space.

#include <vector>
#include <string>
#include <iostream>
#include <assert.h>

using Table = std::vector<std::vector<bool>>;

class Solution {
public:
    int longestValidParentheses(const std::string& s) {
        if (s.size() <= 1) { return 0; }
        int longest = 0;
        Table table(s.size(), std::vector<bool>(s.size(), false)); // all false

        for (int len = 2; len <= s.size(); len += 2) {
            for (int i = 0; i + (len - 1) < s.size(); ++i) {
                int start = i, end = (i+len-1);
                std::cout << "start = " << start << " end = " << end << std::endl;
                if (len == 2) {
                    table[start][end] = (s[start] == '(' && s[end] == ')');
                } else {
                    table[start][end] = table[start+1][end-1] && (s[i] == '(' && s[end] == ')');
                }

                std::cout << "table[" << start << "][" << end << "] = " << table[start][end] << std::endl;
                if (table[start][end]) {
                    longest = std::max(longest, end - start + 1);
                }
            }
        }
        return longest;
    }
};

void test_longest_valid_parens() {
    Solution soln;
    assert(soln.longestValidParentheses(")()())") == 4);
    assert(soln.longestValidParentheses("(()") == 2);
}

int main(int argc, char** argv) {
    test_longest_valid_parens();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
