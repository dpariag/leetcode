// Leetcode: https://leetcode.com/problems/interleaving-string/ 
// Given strings s1, s2, s3, determine whether s3 can be formed by an interleaving of s1 and s2.
// Example: s1 = "aabcc", s2 = "dbbca",
// s3 = "aadbbcbcac" ==> return true.  s3 = "aadbbbaccc" ==> return false.

// Brute Force: Recursively compute all possible interleavings. Compare each to s3. O(2^(m+n)) time.
// Better: Table driven, dynamic programming. O(m*n) time and space.

#include <string>
#include <vector>
#include <iostream>
#include <assert.h>

using Table = std::vector<std::vector<bool>>;

// Accepted. 3ms. Beats 35.80% of submissions and ties 57.25% of submissions
class Solution {
public:
    bool isInterleave(const std::string& s1, const std::string& s2, const std::string& s3) {
        if (s3.length() != s1.length() + s2.length()) { return false; }
        if (s1.empty()) { return s2 == s3; }
        if (s2.empty()) { return s1 == s3; }

        Table table(s1.size()+1, std::vector<bool>(s2.size()+1, false));

        table[0][0] = true;
        for(auto i = 1; i <= s1.size(); ++i) { 
            table[i][0] = table[i-1][0] && s3[i-1] == s1[i-1];
        }
        for (auto j = 1; j <= s2.size(); ++j) {
            table[0][j] = table[0][j-1] && s3[j-1] == s2[j-1];
        }

        for(auto i = 1; i <= s1.size(); ++i) { 
            for (auto j = 1; j <= s2.size(); ++j) {
                table[i][j] = (table[i][j-1] && s3[i+j-1] == s2[j-1]) ||
                              (table[i-1][j] && s3[i+j-1] == s1[i-1]);
            }
        }
        return table.back().back();
    }
};

void test_interleaved() {
    Solution soln;
    assert(soln.isInterleave("", "", ""));
    assert(soln.isInterleave("aa", "", "aa"));
    assert(soln.isInterleave("", "aaa", "aaa"));
    assert(soln.isInterleave("aa", "bbb", "aabbb"));
    assert(soln.isInterleave("aabcc", "dbbca", "aadbbcbcac"));
    assert(soln.isInterleave("aabcc", "dbbca", "aadbbbaccc") == false);
}

int main(int argc, char** argv) {
    test_interleaved();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
