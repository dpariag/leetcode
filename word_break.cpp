// Leetcode: https://leetcode.com/problems/word-break/
// Given a string s and a dictionary of words dict, determine if s can be segmented into a 
// space-separated sequence of one or more dictionary words. Example: s = "leetcode",
// dict = ["leet", "code"], Return true because "leetcode" can be segmented as "leet code".

// Brute Force: Generate all 2^n decompositions of s, and check if each decomposition is composed
// of dictionary words. O(n*2^n) time. Can be improved by pruning any decomposition containing
// an invalid word. This leads to a straightforward recursive solution, but still O(2^n) time.
//
// Better: Dynamic programming - solve the general problem of determining if s[0..i] has a
// valid decomposition. For every i, there are three cases:
// Let k be the index of the first character following the last valid decomposition.
// 1) The suffix s[k..i] is a word => s[0..i] has a valid decomposition.
// 2) The suffix s[k..i] can be appended to word suffixes of S[0..k-1] to form a valid decomposition.
// 3) No valid decomposition can end in s[k..i]
// O(n^3) time and O(n) space.

#include <string>
#include <vector>
#include <unordered_set>
#include <iostream>
#include <assert.h>

using Dictionary = std::unordered_set<std::string>;

// Accepted. 6ms runtime. Beats 65.99% of solutions, and ties 22.68% of submissions.
class Solution {
public:
    bool wordBreak(const std::string& s, Dictionary& dict) {
        std::vector<int> valid_decomps; // indices such that s[0..i] is a valid decomposition
        std::string substring;
       
        // For exposition, let k = valid_decomps.back() or 0 if valid_decomps.empty()
        for (int i = 0; i < s.size(); ++i) {
            substring.push_back(s[i]);
            if (dict.find(substring) != dict.end()) {
                // s[k+1..i] is a word, so s[0..i] has a valid decomposition
                valid_decomps.emplace_back(i);
                substring.clear();
            } else {
                if (dict.find(s.substr(0,i+1)) != dict.end()) {
                    // s[0..i] is a word
                    valid_decomps.emplace_back(i);
                    substring.clear();
                } else {
                    // Can s[k+1..i] be appended to a word suffix from valid_decomps to form a word?
                    for (int j = valid_decomps.size() - 1; j >= 0; --j) {
                        std::string word = s.substr(valid_decomps[j]+1, (i - valid_decomps[j]));
                        if (dict.find(word) != dict.end()) {
                            valid_decomps.emplace_back(i);
                            substring.clear();
                            break;
                        }
                    }
                }
            } 
        }
        return !valid_decomps.empty() && valid_decomps.back() == (s.length() - 1);
    }
};

void test_word_break() {
    Dictionary dict({"leet","code","let","bet","be","fed","fellow","head","red","re","he","et"});
    Solution soln;

    assert(soln.wordBreak("leet", dict) == true);
    assert(soln.wordBreak("leetcode", dict) == true);
    assert(soln.wordBreak("headfed", dict) == true);
    assert(soln.wordBreak("codeheheadred", dict) == true);
    assert(soln.wordBreak("heheheheadhecodereredbet", dict) == true);
    assert(soln.wordBreak("heheheheaxxdhecodereredbet", dict) == false);
    assert(soln.wordBreak("letleetbebet", dict) == true);
    assert(soln.wordBreak("letleetbebetbeet", dict) == true);
    assert(soln.wordBreak("bebebebebebe", dict) == true);
    assert(soln.wordBreak("betbebetbebetbet", dict) == true);
    assert(soln.wordBreak("xbetbebetbebetbet", dict) == false);
    assert(soln.wordBreak("betbebetbebetbex", dict) == false);
    assert(soln.wordBreak("betbebetbebetbetx", dict) == false);
}

void test_word_break_prefixes() {
    Dictionary dict({"aa","aaa","aab"});
    Solution soln;

    assert(soln.wordBreak("a", dict) == false);
    assert(soln.wordBreak("aa", dict) == true);
    assert(soln.wordBreak("aaa", dict) == true);
    assert(soln.wordBreak("aaaa", dict) == true);
    assert(soln.wordBreak("aaaab", dict) == true);
}

int main(int argc, char** argv) {
    test_word_break();
    test_word_break_prefixes();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
