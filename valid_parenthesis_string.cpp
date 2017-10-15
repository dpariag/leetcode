// Leetcode: https://leetcode.com/problems/valid-parenthesis-string/description/
// Given a string consisting of '(', ')' and '*' characters, determine if it represents a string
// of balanced parentheses. The '*' character can be treated as a '(', ')' or the empty string.

// Brute Force: Use a counter to track balanced parens. On '*', recurse treating star as each of ')'
// '(' and ''. O(3^n) time.
// Better: Use separate counters for parens and '*'s. In the event of an imbalance on ')', see if
// there are '*'s occurring earlier in the string. At the end, '*'s can be used to balance
// unmatched '('s, provided the stars occur AFTER the '('

#include <vector>
#include <iostream>
#include <assert.h>

// Accepted. 3ms. Beats 38.12% of submissions, ties 51.19% of submissions. 1:43pm.
class Solution {
public:
    bool checkValidString(const std::string& s) {
        int balanced = 0, num_stars = 0;
        int closing_stars = 0;

        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == '(') {
                ++balanced;
            } else if (s[i] == ')') { 
                --balanced;
                if (balanced < 0) {
                    // Use a star if it occurred earlier
                    if (num_stars > 0) { 
                        --num_stars, ++balanced;
                    } else {
                        return false;
                    }
                }
                // Stars used to match '(' can be no more than balanced - discard extras.
                closing_stars = std::min(closing_stars, balanced);
            } else if (s[i] == '*') {
                ++num_stars;
                if (balanced > 0) {
                    ++closing_stars;
                }
            }
        }
        return balanced >= 0 && closing_stars >= balanced;
    }
};

void test_valid_string() {
    Solution soln;
    assert(soln.checkValidString("") == true);
    assert(soln.checkValidString("()") == true);
    assert(soln.checkValidString("(*)") == true);
    assert(soln.checkValidString("(*))") == true);
    assert(soln.checkValidString("()*") == true);
    assert(soln.checkValidString("*()") == true);
    assert(soln.checkValidString("*()*") == true);
    assert(soln.checkValidString("*(()*") == true);
    assert(soln.checkValidString("(()**)") == true);
    assert(soln.checkValidString(")(()**)") == false);
    assert(soln.checkValidString("(()**))))") == false);
    assert(soln.checkValidString("(())(())(((()*()()()))()((()()(*()())))(((*)()") == false);
    assert(soln.checkValidString("(())((())()()(*)(*()(())())())()()((()())((()))(*") == false);
}

int main(int argc, char** argv) {
    test_valid_string();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
