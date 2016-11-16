// Leetcode: https://leetcode.com/problems/word-break-ii/
// Given a string s and a dictionary of words dict, add spaces in s to construct a sentence where 
// each word is a valid dictionary word. Return all such possible sentences.
//
// Example: s = "catsanddog", dict = ["cat", "cats", "and", "sand", "dog"].
// A solution is ["cats and dog", "cat sand dog"].

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
using Sentences = std::vector<std::string>;
// WordIndices[i] holds starting indices of words that end at i
using WordIndices = std::vector<std::vector<int>>; 

class Solution {
public:
    Sentences wordBreak(const std::string& s, Dictionary& dict) {
        Sentences sentences;
        WordIndices word_indices(s.size()); // holds starting indices of words ending at index i
        std::string substring;
       
        for (int i = 0; i < s.size(); ++i) {
            //std::cout << "i = " << i << std::endl;
            substring.push_back(s[i]);
            if (dict.find(substring) != dict.end()) {
                // s[k+1..i] is a word, so s[0..i] has a valid decomposition
                word_indices[i].emplace_back(i - substring.size() + 1);
                //std::cout << substring << " is a word" << std::endl;
                substring.clear();
            } else if (dict.find(s.substr(0,i+1)) != dict.end()) {
                // s[0..i] is a word
                word_indices[i].emplace_back(0);
                substring.clear();
            } 
            //std::cout << "*i = " << i << std::endl;
            for (int j = i - 1; j >= 0; --j) {
                auto& indices = word_indices[j];
                for (auto k = 0; k < indices.size(); ++k) {
                    //std::cout << "indices = " << indices[k] << "," << i << std::endl;
                    auto word = s.substr(indices[k], (i - indices[k] + 1));
                    //std::cout << "Word: " << word << "?";
                    if (dict.find(word) != dict.end()) {
                        //std::cout << " yes!" << std::endl;
                        word_indices[i].emplace_back(i - word.size() + 1);
                        substring.clear();
                    } //else { std::cout << " no!" << std::endl; }

                    word = s.substr(j, i - j + 1);
                    if (dict.find(word) != dict.end()) {
                        word_indices[i].emplace_back(j);
                    }
                }
            }
        }

        if (word_indices.back().empty()) { return sentences; }

        std::cout << std::endl;
        for (int i = 0; i < word_indices.size(); ++i) {
            std::cout << i << " : ";
            for (auto j = 0; j < word_indices[i].size(); ++j) {
                std::cout << word_indices[i][j] << " ";
            }
            std::cout << std::endl;
        }
        return sentences;
    }
};

void test_word_break() {
    Dictionary dict({"bed", "bat", "bath", "hand", "and", "beyond"});
    Solution soln;
    soln.wordBreak("bedbathandbeyond", dict);
}

int main(int argc, char** argv) {
    test_word_break();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
