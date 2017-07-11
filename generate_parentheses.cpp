// Leetcode: https://leetcode.com/problems/generate-parentheses/#/description
// Given n, write a function to generate all combinations of well-formed parentheses.
// Example: Given n = 3, return: ["((()))","(()())","(())()","()(())","()()()"]

// Brute Force: Generate all 2^n combos of n parens, then check which are balanced. O(n*2^n)
// Better: Recursively generate balanced parens (i.e., only add ')' if there is a '(' to match).

#include <vector>
#include <iostream>
#include <assert.h>

// Accepted. 3ms. Beats 13.75% of submissions, ties 83.86% of submissions.
class Solution {
public:

    void generate_parens(int remaining_open, int remaining_closed, 
                         std::string& in_progress, std::vector<std::string>& completed) {

        if (remaining_open == 0 && remaining_closed == 0) {
            completed.emplace_back(in_progress);
            return;
        }

        if (remaining_open > 0) {
            in_progress.push_back('(');
            generate_parens(remaining_open - 1, remaining_closed, in_progress, completed);
            in_progress.pop_back();
        }

        if (remaining_closed > 0 && remaining_closed > remaining_open) {
            in_progress.push_back(')');
            generate_parens(remaining_open, remaining_closed - 1, in_progress, completed);
            in_progress.pop_back();
        }
    }

    std::vector<std::string> generateParenthesis(int n) {
        std::vector<std::string> balanced_parens;
        std::string in_progress;

        generate_parens(n, n, in_progress, balanced_parens);
        return balanced_parens;
    }
};

void test_generate_parens() {
    Solution soln;

    auto parens = soln.generateParenthesis(3);
    std::sort(parens.begin(), parens.end());
    assert(parens == std::vector<std::string>({"((()))","(()())", "(())()", "()(())", "()()()"}));
}

int main(int argc, char** argv) {
    test_generate_parens();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
