// Leetcode: https://leetcode.com/problems/wildcard-matching/description/
// Implement wildcard pattern matching with support for '?' and '*'.
// '?' Matches any one char and '*' matches any sequence of chars (possibly empty).
// The matching should cover the entire input string (not partial).

// Brute Force: Use recursion with backtracking to match the string and pattern.
// Better: Use DP. table[i][j] is true if p[0..i] matches s[0..j].

#include <string>
#include <vector>
#include <iostream>
#include <assert.h>

using Table = std::vector<std::vector<bool>>;

// Accepted. 64ms. Beats 37.57% of submissions, ties < 1% of submissions.
class Solution {
public:
    bool is_match_dp(const std::string& s, const std::string& p) {
        if (p.empty()) { return s.empty(); }

        Table table(1+p.size(), std::vector<bool>(1+s.size(), false)); // Leave space for empty string and empty pattern
        table[0][0] = true;

        // Fill in first column
        for (int i = 1; i < table.size(); ++i) {
            if (p[i-1] == '*') { table[i][0] = (i == 1) ? true: table[i-1][0]; }
        }

        for (int i = 1; i < table.size(); ++i) {
            for (int j = 1; j < table[0].size(); ++j) {
                if (p[i-1] == '*') {
                    table[i][j] = table[i-1][j] || table[i][j-1] || table[i-1][j-1];
                } else if (p[i-1] == '?') {
                    table[i][j] = table[i-1][j-1];
                } else {
                    table[i][j] = (p[i-1] == s[j-1]) && table[i-1][j-1];
                }
            }
        }
        return table.back().back();
    }

    bool isMatch(const std::string& s, const std::string& p) {
        std::string pattern;
        for (auto ch: p) {
            if (pattern.empty()) {
                pattern.append(1, ch); 
            } else {
                if (pattern.back() == '*' && ch == '*') { continue; }
                pattern.append(1, ch);
            }
        }
        return is_match_dp(s, pattern);
    }
};

void test_is_match() {
    Solution soln;

    assert(soln.isMatch("", "*") == true);
    assert(soln.isMatch("ho", "ho****") == true);
    assert(soln.isMatch("ho", "ho**") == true);
    assert(soln.isMatch("ab", "ab*") == true);
    assert(soln.isMatch("ab", "a*") == true);
    assert(soln.isMatch("ab", "*") == true);
    assert(soln.isMatch("ab", "ab*?") == false);
    assert(soln.isMatch("ab", "ab*x") == false);
    assert(soln.isMatch("aa", "a") == false);
    assert(soln.isMatch("", "a") == false);
    assert(soln.isMatch("aa", "aa") == true);
    assert(soln.isMatch("aaa", "aa") == false);
    assert(soln.isMatch("aa", "*") == true);
    assert(soln.isMatch("aa", "a*") == true);
    assert(soln.isMatch("ab", "?*") == true);
    assert(soln.isMatch("aab", "c*a*b") == false);
    assert(soln.isMatch("zzzxxxyyabcd", "z*xx?y?a*d") == true);
    assert(soln.isMatch("zzzxxxyyabcd", "*xxx??a*cd") == true);
}

int main(int argc, char** argv) {
    test_is_match();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}