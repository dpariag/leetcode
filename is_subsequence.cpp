// Leetcode: 
// Given strings s and t, check if s is subsequence of t. t may be very long (length ~= 500,000) 
// while s is a short string (<=100).

// Brute Force: Generate all subsequences of t, and compare to s.
// Better: Scan t, matching the next unmatched character in s. O(n) time.

#include <vector>
#include <iostream>
#include <assert.h>

// Accepted. 73ms. Beats 66.39% of submissions, ties 4% of submissions.
class Solution {
public:
    bool isSubsequence(const std::string& s, const std::string& t) {
        if (s.size() > t.size()) { return false; }

        int to_match = 0, next = 0;
        while (next < t.size() && to_match < s.size()) {
            if (s[to_match] == t[next++]) {
                ++to_match;
            }
        }
        return to_match == s.size();
    }
};

void test_is_subsequence() {
    Solution soln;

    assert(soln.isSubsequence("abc", "abc"));
    assert(soln.isSubsequence("abc", "abcd"));
    assert(soln.isSubsequence("abc", "axbxcx"));
    assert(soln.isSubsequence("abc", "abx") == false);
    assert(soln.isSubsequence("abc", "bbc") == false);
    assert(soln.isSubsequence("abcd", "abcxxxdxxx"));
    assert(soln.isSubsequence("", "abcxx"));
}

int main(int argc, char** argv) {
    test_is_subsequence();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
