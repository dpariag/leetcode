// Leetcode: 
// Given a string of parens and some letters, remove the minimum number of parens to make the 
// input string balanced (ignoring letters). Return all possible balanced strings.

// Brute Force:
// Better:

#include <vector>
#include <stack>
#include <algorithm>
#include <unordered_set>
#include <iostream>
#include <assert.h>

using Strings = std::vector<std::string>;

class Solution {
public:
    Strings removeInvalidParentheses(std::string& s) {
        Strings result;
        remove_invalid(s, 0, 0, result);
        return result;
    }

    void remove_invalid(std::string& s, int start, int last_replace, Strings& result) {
        int num_left = 0, num_right = 0;
        std::cout << std::endl;
        std::cout << "s = " << s << std::endl;
        std::cout << "start = " << start << " last_replace = " << last_replace << std::endl;

        for (int i = start; i < s.size(); ++i) {
            if (s[i] == '(') { ++num_left; }
            else if (s[i] == ')') { ++num_right; }

            std::cout << "i = " << i << " and s = " << s << std::endl;
            if (num_right > num_left) {
                std::cout << "left = " << num_left << " right = " << num_right << std::endl;
                std::cout << "last replace = " << last_replace << std::endl;
                for (int j = last_replace; j < i; ++j) {
                    if (s[j] == ')' && (j == 0 || (j > 0 && s[j-1] != ')'))) {
                        std::cout << "j = " << j << std::endl;
                        auto temp = s;
                        temp.erase(j, 1);
                        remove_invalid(temp, i, j, result);
                        last_replace = j+1;
                    }
                }
            }
        }
        if (num_left == num_right) {
            result.emplace_back(s);
            std::cout << "**" << s << std::endl;
        }
        std::cout << std::endl;
    }
};

bool test_remove_invalid(std::string s, Strings expected) {
    Solution soln;
    auto balanced = soln.removeInvalidParentheses(s);
    
    std::sort(balanced.begin(), balanced.end());
    std::sort(expected.begin(), expected.end());
    return balanced == expected;
}

void test_remove_invalid() {
    assert(test_remove_invalid("()())()", {"(())()", "()()()"}));
    assert(test_remove_invalid("()))", {"()"}));
    assert(test_remove_invalid(")", {""}));
    //assert(test_remove_invalid(")d))", {"d"}));
    return;
    assert(test_remove_invalid("()((", {"()"}));
    assert(test_remove_invalid("()(((((((()", {"()()"}));
    assert(test_remove_invalid("((()()", {"()()", "(())"}));
    assert(test_remove_invalid("()())()", {"(())()", "()()()"}));
    assert(test_remove_invalid("(((", {""}));
    assert(test_remove_invalid("()()(()", {"()()()"}));
    assert(test_remove_invalid(")(f", {"f"}));
    assert(test_remove_invalid("()((()(())", {"()()(())", "()((()))"}));
    //assert(test_remove_invalid("(()(()", {"()()"}));
    //assert(test_remove_invalid("", {"", ""}));
}

int main(int argc, char** argv) {
    test_remove_invalid();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
