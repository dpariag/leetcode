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
#include <algorithm>
#include <iostream>
#include <assert.h>

using Dictionary = std::unordered_set<std::string>;
using Sentences = std::vector<std::string>;
// WordIndices[i] holds starting indices of words that end at i
using WordIndices = std::vector<std::vector<int>>; 

// Accepted. 96ms. Beats 0.76% of submissions.
class Solution {
public:
    Sentences wordBreak(const std::string& s, Dictionary& dict) {
        Sentences sentences;
        WordIndices word_indices(s.size()); // holds starting indices of words ending at index i
        std::string substring;
        std::vector<int> valid_indices;

        valid_indices.emplace_back(-1);
        for (int i = 0; i < s.size(); ++i) {
            Dictionary new_words;
            substring.push_back(s[i]);
            if (dict.find(substring) != dict.end() && new_words.find(substring) == new_words.end()) {
                // s[k+1..i] is a word, so s[0..i] has a valid decomposition
                new_words.emplace(substring);
                word_indices[i].emplace_back(i - substring.size() + 1);
                substring.clear();
                if (i != valid_indices.back()) { valid_indices.emplace_back(i); }
            } 
          
            for (int v  = valid_indices.size() - 1; v >= 1; --v) {
                auto j = valid_indices[v];
                auto& indices = word_indices[j];

                for (auto k = 0; k < indices.size(); ++k) {
                    auto word = s.substr(indices[k], (i - indices[k] + 1));
                    if (dict.find(word) != dict.end() && new_words.find(word) == new_words.end()) {
                        word_indices[i].emplace_back(i - word.size() + 1);
                        new_words.emplace(word);
                        substring.clear();
                        if (i != valid_indices.back()) { valid_indices.emplace_back(i); }
                    } 
                }
                auto word = s.substr(j, i - j + 1);
                if (dict.find(word) != dict.end() && new_words.find(word) == new_words.end()) {
                    word_indices[i].emplace_back(j);
                    new_words.emplace(std::move(word));
                    if (i != valid_indices.back()) { valid_indices.emplace_back(i); }
                    break;
                }
            }
        }
        if (word_indices.back().empty()) { return sentences; }
        generate_sentences(s, word_indices, word_indices.size() - 1, "", sentences);
        return sentences;
    }

    void generate_sentences(const std::string& s, const WordIndices& word_indices,
                            int index, std::string sentence, Sentences& sentences) {
        if (index < 0) { 
            sentence.pop_back(); // remove last space
            sentences.emplace_back(std::move(sentence)); 
            return;
        }

        for (auto i = 0; i < word_indices[index].size(); ++i) {
            auto word = s.substr(word_indices[index][i], index - word_indices[index][i] + 1);
            word.append(1, ' ');
            word.append(sentence);
            generate_sentences(s, word_indices, word_indices[index][i] - 1, word, sentences);
        }
    }
};

bool test_word_break(std::initializer_list<std::string>&& dict_words, const std::string& s,
                     std::vector<std::string> expected_sentences) {
    Dictionary dict(dict_words);
    Solution soln;
    auto sentences = soln.wordBreak(s, dict);
    std::sort(sentences.begin(), sentences.end());
    std::sort(expected_sentences.begin(), expected_sentences.end());
    return (sentences == expected_sentences);
}

void test_word_break() {
    assert(test_word_break({"cat", "cats", "and", "sand", "dog"}, "catsanddog",
                           {"cats and dog", "cat sand dog"}));
    assert(test_word_break({"aaaa","aaa","aa"}, "aaaaaaaa",
                           {"aaaa aaaa", "aa aa aaaa", "aaaa aa aa", "aa aa aa aa", 
                            "aaa aaa aa", "aa aaaa aa", "aaa aa aaa", "aa aaa aaa" }));

    assert(test_word_break({"aaaa","aaa"}, "aaaaaaa",
                           {"aaa aaaa", "aaaa aaa"}));
    assert(test_word_break({"a","abc","b","cd"}, "abcd", {"a b cd"}));

    assert(test_word_break({"a"}, "a", {"a"}));
    assert(test_word_break({"bed","bat","bath","hand","and","beyond", "be", "yond"}, 
                            "bedbathandbeyond",
                            {"bed bat hand be yond", "bed bat hand beyond",
                             "bed bath and be yond", "bed bath and beyond"}));
}

int main(int argc, char** argv) {
    test_word_break();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
