// Leetcode: https://leetcode.com/problems/delete-operation-for-two-strings/description/
// Given two words, find the minimum number of steps required to make word1 and word2 the same, 
// where in each step you can delete one character in either string.

// Brute Force: Recursive enumeration. O(n^n) time.
// Better: Table-driven DP. O(n^2) time.

#include <vector>
#include <iostream>
#include <assert.h>

// Accepted. 35ms. Beats 49.84% of submissions, ties 11.2% of submissions.
class Solution {
public:
    int minDistance(std::string word1, std::string word2) {
        std::vector<std::vector<int>> table(word1.size()+1, std::vector<int>(word2.size()+1, 0));
        
        for (int row = 1; row <= word1.size(); ++row) {
            for (int col = 1; col <= word2.size(); ++col) {
                table[row][col] = std::max({table[row-1][col], table[row][col-1], 
                        int(word1[row-1] == word2[col-1]) + table[row-1][col-1]});
            }
        }
        return (word1.size() - table.back().back()) + (word2.size() - table.back().back());
    }
};

void test_min_distance() {
    Solution soln;
    assert(soln.minDistance("sea", "eat") == 2);
    assert(soln.minDistance("costa", "coast") == 2);
    assert(soln.minDistance("coast", "costa") == 2);
    assert(soln.minDistance("coastal", "costa") == 2);
    assert(soln.minDistance("costa", "costa") == 0);
    assert(soln.minDistance("costa", "cost") == 1);
    assert(soln.minDistance("character", "char") == 5);
    assert(soln.minDistance("floor", "poor") == 3);
}

int main(int argc, char** argv) {
    test_min_distance();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
