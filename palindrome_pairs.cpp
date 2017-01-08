// Leetcode: https://leetcode.com/problems/palindrome-pairs/
// Given a list of unique words, find all pairs of distinct indices (i, j), such that the 
// concatenation of the two words (words[i] + words[j]) is a palindrome.

// Brute Force: Construct all O(n^2) concatenations, check if each is a palindrome. O(n^3*m) time.
// Better: Construct a trie containing all n words. For each word, search the trie for a reversed 
// suffix of that word such that the remaining prefix is a palindrome.
// Example: words = {"lls", "sssll"}. The suffix "sll" can be found in reverse (i.e., "lls") in 
// the trie and the remaining prefix "ss" is a palindrome. O(n*m) to construct the trie. O(n*m)
// to search each word. O(n*m) time and space. 
// Something similar can be done using hash tables with or without a rolling (incrementally updated)
// hash key.

#include <vector>
#include <iostream>
#include <unordered_map>
#include <assert.h>

using Words = std::vector<std::string>;
using Pair = std::vector<int>;          // leetcode represents pairs this way
using Indices = std::vector<Pair>;
using Dictionary = std::unordered_map<std::string, int>; // string --> index

// Accepted. 449ms. Beats 47.61% of submissions
class Solution {
public:
    inline bool is_palindrome(const std::string& s, int start, int end) {
        while (start < end) {
            if (s[start] != s[end]) { return false; }
            ++start; --end;
        }
        return true;
    }

    Indices palindromePairs(const Words& words) {
        Indices result;
        Dictionary dict, reversed;
        // Store words, and reversed words in separate dictionaries
        for (auto i = 0; i < words.size(); ++i) {
            dict.emplace(words[i],i);
            std::string reversed_word(words[i]);
            std::reverse(reversed_word.begin(), reversed_word.end());
            reversed.emplace(reversed_word, i);
        }
        
        auto empty_string = dict.find(""); 
        for (auto i = 0; i < words.size(); ++i) {
            auto word = words[i];
            // Special case of a palindromic word and the empty string
            if (is_palindrome(word, 0, int(word.length() - 1)) && empty_string != dict.end() &&
                empty_string->second != i) {
                result.emplace_back(Pair({i, empty_string->second}));
                result.emplace_back(Pair({empty_string->second, i}));
            } 

            // Check every suffix, to see if the suffix is in the dictionary
            // and the remaining prefix is a palindrome 
            std::string suffix;
            for (int index = (word.length() - 1); index >= 0; --index) {
                suffix.push_back(word[index]);
                auto found = dict.find(suffix);
                if (found != dict.end() && found->second != i && 
                    is_palindrome(word, 0, index-1)) {
                    result.emplace_back(Pair({found->second,i}));
                }
            }

            // Check every prefix, to see if the prefix is in the reversed dictionary
            // and the remaining suffix is a palindrome
            std::string prefix;
            for (int index = 0; index < int(word.length() - 1); ++index) {
                prefix.push_back(word[index]);
                auto found = reversed.find(prefix);
                if (found != reversed.end() && found->second != i && 
                    is_palindrome(word, index+1, word.length() - 1)) {
                    result.emplace_back(Pair({i, found->second}));
                }
            }
        }
        return result;
    }
};

void print(const Indices& indices) {
    for (auto& i : indices) {
        for (auto j : i) { 
            std::cout << j << " ";
        }
        std::cout << std::endl;
    }
}

bool test_palindrome_pairs(const Words& words, Indices expected) {
    Solution soln;
    auto indices = soln.palindromePairs(words);
    std::sort(expected.begin(), expected.end());
    std::sort(indices.begin(), indices.end());
    return indices == expected;
}

void test_palindrome_pairs() {
    assert(test_palindrome_pairs({},{}));
    assert(test_palindrome_pairs({"a", ""}, Indices({Pair({0,1}), Pair({1,0})})));
    assert(test_palindrome_pairs({"xyz","zyx"},Indices({Pair({0,1}),Pair({1,0})})));
    assert(test_palindrome_pairs({"xyz","zyx", "xy"},
        Indices({Pair({0,1}),Pair({1,0}),Pair({2,1})})));
    assert(test_palindrome_pairs({"xyz","zyx", "yx"},
        Indices({Pair({0,1}),Pair({1,0}),Pair({0,2})})));
    assert(test_palindrome_pairs({"xyz","zyx", "yx", "xy", "q", "abc"},
        Indices({Pair({0,1}),Pair({1,0}),Pair({0,2}),Pair({2,3}),
                 Pair({3,1}),Pair({3,2})})));
}

int main(int argc, char** argv) {
    test_palindrome_pairs();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
