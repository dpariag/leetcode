// Leetcode: https://leetcode.com/problems/output-contest-matches/description/

// Approach: Start with all teams in an ordered array. Repeatedly matchup the 
// winners of the leftmost and rightmost matches until only one match remains.

#include <string>
#include <vector>
#include <iostream>
#include <assert.h>

using Strings = std::vector<std::string>;

// Accepted. 6ms. Beats 7.14% of submissions, ties 25.60% of submissions.
class Solution {
public:
    std::string findContestMatch(int n) {
        Strings prev, next;
        for (int i = 1; i <= n; ++i) {
            next.emplace_back(std::to_string(i));
        }

        while (next.size() > 1) {
            prev = next;
            next.clear();

            int left = 0, right = prev.size() - 1;
            while (left < right) {
                auto match = "(" + prev[left] + "," + prev[right] + ")";
                next.emplace_back(std::move(match));
                ++left, --right;
            }
        }
        return next.front();
    }
};

void test_find_contest_match() {
    Solution soln;

    assert(soln.findContestMatch(1) == "1");
    assert(soln.findContestMatch(2) == "(1,2)");
    assert(soln.findContestMatch(4) == "((1,4),(2,3))");
    assert(soln.findContestMatch(8) == "(((1,8),(4,5)),((2,7),(3,6)))");
}

int main(int argc, char** argv) {
    test_find_contest_match();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
