// Leetcode: https://leetcode.com/problems/flip-game/description/
// Given a string of '+' and '-' characters, you can flip two consecutive "++" into "--". 
// Write a function to compute all possible states of the string after flip.

// Approach: Scan the string looking for consecutive "++" substrings. O(n) time.

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <assert.h>

using Strings = std::vector<std::string>;

// Accepted. 0ms. Beats 66.06% of submissions, ties 33.94% of submissions.
class Solution {
public:
    Strings generatePossibleNextMoves(std::string& s) {
        Strings result;

        int i = 0;
        while (i+1 < int(s.size())) {
            if (s[i] == '+' && s[i+1] == '+') {
                s[i] = s[i+1] = '-';
                result.emplace_back(s);
                s[i] = s[i+1] = '+';
            }
            i += (s[i+1] == '-' ? 2 : 1);
        }
        return result;
    }
};

bool test_next_moves(std::string s, Strings expected) {
    Solution soln;

    auto next_moves = soln.generatePossibleNextMoves(s);
    std::sort(next_moves.begin(), next_moves.end());
    std::sort(expected.begin(), expected.end());
    return next_moves == expected;
}

void test_next_moves() {
    assert(test_next_moves("", {}));
    assert(test_next_moves("+", {}));
    assert(test_next_moves("++", {"--"}));
    assert(test_next_moves("+++", {"--+", "+--"}));
    assert(test_next_moves("++++", {"--++", "+--+", "++--"}));
}

int main(int argc, char** argv) {
    test_next_moves();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}