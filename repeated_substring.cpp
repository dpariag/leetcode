// Leetcode: 
// Given a non-empty string s, determine if s can be constructed by repeatedly appending a substring
// of s to itself. Example: "abcabc" --> true, "abcdabc" --> false.

// Brute Force: Try substrings of length 1,2,3,.... O(n^2) time.
// Better: Prune the search space by checking if the string's length is divisible by i first.
// Stil O(n^2) though (e.g., a string of length n!). KMP could make it O(n).

#include <string>
#include <iostream>
#include <assert.h>

// Accepted. 32ms. Beats 76.81% of submissions, ties 12.84% of submissions.
class Solution {
public:
    bool repeatedSubstringPattern(const std::string& s) {
        const int len = s.length();
        for (int i = 1; i <= len / 2; ++i) {
            if (len % i != 0) { continue; }
            bool match = true;
            int num_substrs = len / i;
            for (int j = 1; j < num_substrs; ++j) {
                int offset = j * i;
                for (int k = 0; k < i; ++k) {
                    if (s[offset+k] != s[k]) {
                        match = false;
                        break;
                    }
                }
                if (!match) { break; }
            }
            if (match) { return true; }
        }
        return false;
    }
};

void test_repeated_substring() {
    Solution soln;
    assert(!soln.repeatedSubstringPattern("a"));
    assert(soln.repeatedSubstringPattern("aa"));
    assert(soln.repeatedSubstringPattern("aaa"));
    assert(!soln.repeatedSubstringPattern("aba"));
    assert(soln.repeatedSubstringPattern("aaaa"));
    assert(soln.repeatedSubstringPattern("abab"));
    assert(soln.repeatedSubstringPattern("abcabc"));
    assert(!soln.repeatedSubstringPattern("abcabcd"));
    assert(soln.repeatedSubstringPattern("abcabcdabcabcd"));
    assert(soln.repeatedSubstringPattern("abczyabczyabczy"));
    assert(soln.repeatedSubstringPattern("abczaabczaabcza"));
    assert(soln.repeatedSubstringPattern("abczaaaabczaaaabczaaa"));
    assert(!soln.repeatedSubstringPattern("abczaaaxabczaaayabczaaaz"));
    assert(!soln.repeatedSubstringPattern("ababababc"));
    assert(soln.repeatedSubstringPattern("ababababcababababc"));
    assert(soln.repeatedSubstringPattern("abbbabbbabbb"));
    assert(soln.repeatedSubstringPattern("abaababaab"));
}

int main(int argc, char** argv) {
    test_repeated_substring();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
