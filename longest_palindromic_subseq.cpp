// Leetcode: https://leetcode.com/problems/longest-palindromic-subsequence/description/
// Find the length of the longest palindromic subsequence in a string s. Assume len(s) <= 1000 

// Brute Force: Generate all subsequences of s, check which are palindromic. O(n!)
// Better: Use DP table[i][j] is the length of the longest palindromic subseq over s[i..j]
// Then check if s[i] == s[j] and calculate table[i][j] accordingly.

#include <vector>
#include <string>
#include <iostream>
#include <assert.h>

using Table = std::vector<std::vector<int>>;

// Accepted. 80ms. Beats 68.95% of submisssions.
class Solution {
public:
    int longestPalindromeSubseq(std::string& s) {
        Table table(s.size(), std::vector<int>(s.size(),0));
        // table[i][j] is the length of the longest palindromic subseq over s[i..j]
        int len = s.size();

        for (int row = len-1; row >= 0; --row) {
            for (int col = row; col < len; ++col) {
                if (row == col) {
                    table[row][col] = 1; // diagonal
                } else if (s[row] == s[col]) {
                    // Extend inner subsequence
                    table[row][col] = 2 + table[row+1][col-1];
                } else {
                    // Choose longer subseq from s[i][j-1] and s[i+1][j]
                    table[row][col] = std::max(table[row][col-1], table[row+1][col]);
                }
            }
        }
        return table.front().back();
    }
};

bool test_longest_palindromic(std::string s, int expected) {
    Solution soln;
    return soln.longestPalindromeSubseq(s) == expected;
}

void test_longest_palindromic() {
    assert(test_longest_palindromic("bbbab", 4));
    assert(test_longest_palindromic("cbbd", 2));
    assert(test_longest_palindromic("bbd", 2));
    assert(test_longest_palindromic("bb", 2));
    assert(test_longest_palindromic("b", 1));
    assert(test_longest_palindromic("abcddcba", 8));
    assert(test_longest_palindromic("xabcddcba", 8));
    assert(test_longest_palindromic("abcdxdxcba", 9));
    assert(test_longest_palindromic("xabxcdxdxcba", 9)); // abcdxdcba
    assert(test_longest_palindromic("xabxcdxdxcbaxxxx", 11));
}

int main(int argc, char** argv) {
    test_longest_palindromic();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}

//    b b b a b
//  b 1 
//  b   1 2 2 3
//  b     1 1 3
//  a       1 1
//  b         1
