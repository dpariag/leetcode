// Leetcode: https://leetcode.com/problems/isomorphic-strings/
// Given equal-length strings s and t, determine if the chars in s can be replaced to get t.
// All occurrences of a character must be replaced with another character while preserving character 
// ordering. No two characters may map to the same character but a character may map to itself.
// Example: {"egg","add"} => true, {"foo", "bar"} => false  {"paper", "title"} => true.

// Brute Force: Attempt to perform the isomorphism, replacing/mapping chars in t. O(n^2) time.
// Better: Simply build the character mapping, aborting if a many-to-one mapping is detected,
// or if an inverse mapping is not possible. O(n) time and O(1) space

#include <string>
#include <vector>
#include <iostream>
#include <assert.h>

using CharMapping = std::vector<char>;

// Accepted. 9ms. Beats 65.74% of solutions, ties 10% of solutions.
class Solution {
public:
    bool isIsomorphic(const std::string& s, const std::string& t) {
        CharMapping mapping(255,'\0'), inverse(255, '\0');

        for (auto i = 0; i < s.size(); ++i) {
            if (mapping[s[i]] != '\0' && mapping[s[i]] != t[i]) { return false; }
            mapping[s[i]] = t[i];

            if (inverse[t[i]] != '\0' && inverse[t[i]] != s[i]) { return false; }
            inverse[t[i]] = s[i];
        }
        return true;
    }
};

void test_isomorphic_strings() {
    Solution soln;

    assert(soln.isIsomorphic("", "") == true);
    assert(soln.isIsomorphic("a", "b") == true);
    assert(soln.isIsomorphic("b", "b") == true);
    assert(soln.isIsomorphic("aaaaa", "aaaaa") == true);
    assert(soln.isIsomorphic("aaaaa", "bbbbb") == true);
    assert(soln.isIsomorphic("egg", "add") == true);
    assert(soln.isIsomorphic("foo", "bar") == false);
    assert(soln.isIsomorphic("paper", "title") == true);
    assert(soln.isIsomorphic("title", "paper") == true);
    assert(soln.isIsomorphic("bear", "care") == true);
    assert(soln.isIsomorphic("bear", "carr") == false);
    assert(soln.isIsomorphic("aabcdeefgg", "aazyxwwvuu") == true);
    assert(soln.isIsomorphic("aabcdeefgg", "aazyxwwvaa") == false);
}

int main(int argc, char** argv) {
    test_isomorphic_strings();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
