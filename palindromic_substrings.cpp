// Leetcode: https://leetcode.com/problems/palindromic-substrings/description/ 
// Given a string, your task is to count how many palindromic substrings in this string.

// Brute Force: Generate all substrings, count how many are palindromes. O(n^3) time.
// Better: Table-driven DP. table[i][j] = true iff s[i..j] is a palindrome.
// table[i][j] = (s[i] == s[j] && table[i+1][j-1]). O(n^2)time/space

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <assert.h>

using Table = std::vector<std::vector<bool>>;

// Accepted. 22ms. Beats 19.25% of submissions, ties 2.72% of submissions
class Solution {
public:
    int countSubstrings(std::string s) {
        if (s.empty()) { return 0; }

        int count = 0;
        Table table(s.size(), std::vector<bool>(s.size(), false));

        for (int len = 1; len <= s.size(); ++len) {
            for (int start = 0; start < s.size()-len+1; ++start) {
                int end = std::min(start + len - 1, int(s.size()-1)); // inclusive
                bool middle = (start+1) <= (end-1) ? table[start+1][end-1] : true;
                table[start][end] = (s[start] == s[end]) && middle; 
                if (table[start][end]) ++count;
            }
        }
        return count;
    }
};

bool test_count_substrings(std::string s, int expected) {
    Solution soln;
    return soln.countSubstrings(s) == expected;
}

void test_count_substrings() {
    assert(test_count_substrings("", 0));
    assert(test_count_substrings("x", 1));
    assert(test_count_substrings("abc", 3));
    assert(test_count_substrings("aab", 4));
    assert(test_count_substrings("aaa", 6));
    assert(test_count_substrings("aabbaa", 11));
}

int main(int argc, char** argv) {
    test_count_substrings();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}