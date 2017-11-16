// Leetcode: https://leetcode.com/problems/longest-word-in-dictionary-through-deleting/description/
// Given a string s and a dictionary d, find the longest string in the d that can be formed by 
// deleting some characters of s. If tied, return the smallest lexicographically. Return the 
// empty string if no string in d is a subsequence of s.

// Brute Force: Iterate strings in d, determine if each is a subsequence of s. Store the longest and
// lexicographically smallest restult. O(n*m) time.
// Better: Sort strings by length, then lexicographical ordering. Same worst case,better expected.

#include <vector>
#include <iostream>
#include <algorithm>
#include <assert.h>

// Accepted. 105ms. Beats 57.80% of submissions, ties 6.61% of submisssions.
class Solution {
public:
    bool is_subsequence(const std::string& s, const std::string t) {
        int i = 0, j = 0;
        while (i < s.size() && j < t.size()) {
            if (s[i] == t[j]) {
                ++j;
            }
            ++i;
        }
        return j == t.size();
    }

    std::string findLongestWord(const std::string& s, std::vector<std::string>& d) {
        std::string result;
        std::sort(d.begin(), d.end(), 
                [](const std::string& a, const std::string& b) {
                if (a.size() == b.size()) { return a < b; }
                return a.size() > b.size(); });

        for (const auto& elem : d) {
            if (is_subsequence(s, elem)) {
                return elem;
            }
        }
        return result;
    }
};

void test_find_longest_word() {
    Solution soln;
    std::vector<std::string> dict = {"ale", "apple", "monkey", "plea", "flatter", "x", "y", "z"};
    assert(soln.findLongestWord("abpcplea", dict) == "apple");
    assert(soln.findLongestWord("aleappleflattermonkey", dict) == "flatter");
    assert(soln.findLongestWord("flaapptteler", dict) == "flatter");
    assert(soln.findLongestWord("flaateer", dict) == "");
    assert(soln.findLongestWord("flaaxyz", dict) == "x");
}

int main(int argc, char** argv) {
    test_find_longest_word();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
