// Leetcode: https://leetcode.com/problems/regular-expression-matching/description/ 
// Implement regular expression matching with support for '.' and '*'.

// Brute Force:
// Better:

#include <vector>
#include <iostream>
#include <assert.h>

// Accepted. 26ms. Beats 35.93% of submissions, ties 0.3% of submissions
class Solution {
public:
    bool is_match(const std::string& s, int i, const std::string& expr, int j) {
        if (i >= s.size() && j >= expr.size()) { return true; }
        if (i < s.size() && j >= expr.size()) { return false; }

        char expr_cur = expr[j];
        char expr_next = (j+1 < expr.size()) ? expr[j+1] : '\0';

        if (expr_cur == '.') {
            if (expr_next == '*') {
                int k = i;
                while (k <= s.size()) {
                    if (is_match(s, k, expr, j+2)) { return true; }
                    ++k; 
                }
                return false;
            }
            return i < s.size() && is_match(s, i+1, expr, j+1);
        }

        // Current regex char is not a dot
        if (expr_next == '*') {
            int k = i;
            while (k <= s.size()) {
                if (k == i) {
                   if (is_match(s, k, expr, j+2)) { return true; }
                   else if (k < s.size() && s[k] == expr_cur) {
                       if (is_match(s, k+1, expr, j+2)) { return true; }
                   } else { return false; }
                } else if (k != i) {
                    if (k < s.size() && j < expr.size() && s[k] == expr[j]) {
                        if (is_match(s, k+1, expr, j+2)) { return true; }
                    } else {
                        return false;
                    }
                }
                ++k;
            }
            return false;
        } 
        return i < s.size() && j < expr.size() && s[i] == expr[j] && is_match(s, i+1, expr, j+1);
    }

    bool isMatch(const std::string& s, const std::string& expr) {
        int i = 0, j = 0;
        return is_match(s, i, expr, j);
    }
};

void test_regex() {
    Solution soln;

    assert(soln.isMatch("abb", "b*") == false);
    assert(soln.isMatch("aaba", "ab*a*c*a*") == false);
    assert(soln.isMatch("bb", "b*b") == true);
    assert(soln.isMatch("aaa", "ab*a*c*a") == true);
    assert(soln.isMatch("aaa", "aaa") == true);
    assert(soln.isMatch("aaa", "aab") == false);
    assert(soln.isMatch("aab", "aab") == true);
    assert(soln.isMatch("aabx", "aab") == false);
    assert(soln.isMatch("aab", "aabz") == false);
    assert(soln.isMatch("aaa", "a*") == true);
    assert(soln.isMatch("aaa", "aaab*") == true);
    assert(soln.isMatch("aaa", "aaa.*") == true);
    assert(soln.isMatch("aaabbb", "aaa.*") == true);
    assert(soln.isMatch("aaabbb", "aaab*") == true);
    assert(soln.isMatch("aaabbbx", "aaab*") == false);
    assert(soln.isMatch("aaabbbx", ".*") == true);
    assert(soln.isMatch("xyz", "...") == true);
    assert(soln.isMatch("", ".*") == true);
    assert(soln.isMatch("xyz", "..") == false);
    assert(soln.isMatch("xyz", "....") == false);
    assert(soln.isMatch("aaabbbcccddd", "a*b*c*d*") == true);
    assert(soln.isMatch("bbbcccddd", "a.*") == false);
    assert(soln.isMatch("aaabbbcccddd", "a.*") == true);
    assert(soln.isMatch("aaabbbcccddd", "aaabbb.*ddd") == true);
    assert(soln.isMatch("aaabbbcccddd", "aaaccc.*") == false);
}

int main(int argc, char** argv) {
    test_regex();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
