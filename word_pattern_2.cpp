// Leetcode: https://leetcode.com/problems/word-pattern-ii/description/
// Given a pattern and a string str, find if str follows the same pattern.
// Example: pattern = "abab", string = "redblueredblue" then return true

// Brute Force: Generate all decompositions of str, and try to match to pattern. O(n*2^n) time.
// Better: Use backtracking to prune the search

#include <string>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <assert.h>

using CharMap = std::unordered_map<char, std::string>;
using Matched = std::unordered_set<std::string>;

// Accepted. 64ms. Beats 74.10% of cpp submissions.
class Solution {
public:
    bool search(const std::string& s, const std::string& pat, int i, int j, CharMap& char_map, Matched& matched) {
        if (i >= s.length() && j >= pat.length()) { return true; }
        if (i >= s.length() || j >= pat.length()) { return false; }

        auto ch = pat[j];
        auto found = char_map.find(ch);
        if (found != char_map.end()) {
            // ch has already been mapped to a fragment
            auto fragment = s.substr(i, found->second.length());
            if (fragment != found->second) return false;
            return search(s, pat, i+fragment.size(), j+1, char_map, matched);
        } else {
            // ch is unmapped
            for (int k = i; k < s.size(); ++k) {
                auto fragment = s.substr(i, k-i+1);
                // This fragment may have been mapped to another character!
                if (matched.count(fragment) != 0) continue;
                // We have an unmapped fragment
                matched.emplace(fragment);
                char_map[ch] = fragment;
                if (search(s, pat, k+1, j+1, char_map, matched)) return true;
                char_map.erase(ch);
                matched.erase(fragment);
            }
        }
        return false; 
    }

    bool wordPatternMatch(const std::string& pattern, const std::string& str) {
        CharMap char_map;
        Matched matched;
        return search(str, pattern, 0, 0, char_map, matched);
    }
};

bool test_pattern_match(std::string str, std::string pat, bool expected) {
    Solution soln;
    return soln.wordPatternMatch(pat, str) == expected;
}

void test_pattern_match() {
    assert(test_pattern_match("ab", "aa", false));
    assert(test_pattern_match("redblueredblue", "abab", true));
    assert(test_pattern_match("redbluxredblue", "abab", false));
    assert(test_pattern_match("asdasdasdasd", "aaaa", true));
    assert(test_pattern_match("asdasdasdsd", "aaaa", false));
    assert(test_pattern_match("xyzabcxzyabc", "aabb", false));
}

int main(int argc, char** argv) {
    test_pattern_match();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
