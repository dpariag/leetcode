// Leetcode: https://leetcode.com/problems/valid-parenthesis-string/description/
// Given a string consisting of '(', ')' and '*' characters, determine if it represents a string
// of balanced parentheses. The '*' character can be treated as a '(', ')' or the empty string.

// Brute Force:
// Better:

#include <vector>
#include <iostream>
#include <assert.h>

// Start time: 12:28pm
// Done my testing at 12:38pm
// Accepted. 266ms. Beats 20.98% of submissions, ties < 1% of submissions.
class Solution {
public:
    bool check_balanced(const std::string&s, int i, int balanced) {

        for (; i < s.size(); ++i) {
            if (s[i] == '(') {
                ++balanced;
            } else if (s[i] == ')') {
                --balanced;
                if (balanced < 0) { return false; }
            } else if (s[i] == '*') {
                return (check_balanced(s, i+1, balanced+1) ||
                        (balanced > 0 && check_balanced(s, i+1, balanced-1)) ||
                        check_balanced(s, i+1, balanced));
            }
        }
        return balanced == 0;
    }

    bool checkValidString(const std::string& s) {
        int balanced = 0;
        return check_balanced(s, 0, balanced);
    }
};

void test_valid_string() {
    Solution soln;
    assert(soln.checkValidString("") == true);
    assert(soln.checkValidString("()") == true);
    assert(soln.checkValidString("(*)") == true);
    assert(soln.checkValidString("()*") == true);
    assert(soln.checkValidString("*()") == true);
    assert(soln.checkValidString("*()*") == true);
    assert(soln.checkValidString("*(()*") == true);
    assert(soln.checkValidString("(()**)") == true);
    assert(soln.checkValidString(")(()**)") == false);
    assert(soln.checkValidString("(()**))))") == false);
}

int main(int argc, char** argv) {
    test_valid_string();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
