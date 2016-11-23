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
//#include <chrono>

struct Word {
    int start = 0;  // index of first character in a word
    int end = 0;    // index of last character in a word
    Word(int s, int e): start(s), end(e) {}
};

using Dictionary = std::unordered_set<std::string>;
using Sentences = std::vector<std::string>;
using Words = std::vector<Word>; // starting and ending indices of words

void print(const Words& words) {
    for (auto i = 0; i < words.size(); ++i) {
        std::cout << words[i].start << "," << words[i].end << std::endl;
    }
    std::cout << std::endl;
}

// Accepted. 103ms. Beats 0.76% of submissions.
class Solution {
public:
    Sentences wordBreak(const std::string& s, Dictionary& dict) {
        Sentences sentences;
        Words words; 
        std::string substring;
        
        for (int i = 0; i < s.size(); ++i) {
            //std::cout << std::endl << "i = " << i << std::endl;
            Dictionary new_words;
            substring.push_back(s[i]);
            if (dict.find(substring) != dict.end() && new_words.find(substring) == new_words.end()) {
                //std::cout << "1. word = " << substring << std::endl;
                // s[k+1..i] is a word, so s[0..i] has a valid decomposition
                new_words.emplace(substring);
                words.emplace_back(Word(int(i - substring.size() + 1), i));
                substring.clear();
            } 
            for (int j = words.size() - 1; j >= 0; --j) {
                // Try to concatenate suffix with an earlier word
                auto word = s.substr(words[j].start, (i - words[j].start + 1));
                //std::cout << "2. word = " << word << std::endl;
                if (dict.find(word) != dict.end() && new_words.find(word) == new_words.end()) {
                    words.emplace_back(Word(int(i - word.size() + 1), i));
                    //std::cout << "2. " << words.back().start << "," << words.back().end << std::endl;
                    new_words.emplace(word);
                    substring.clear();
                }
                if (i <= words[j].end + 1) { continue; }
                // Check suffix following words[j].end
                word = s.substr(words[j].end + 1, i - words[j].end);
                //std::cout << "3. word = " << word << std::endl;
                if (dict.find(word) != dict.end() && new_words.find(word) == new_words.end()) {
                    words.emplace_back(Word(words[j].end + 1, int(words[j].end + word.size())));
                    //std::cout << "3. " << words.back().start << "," << words.back().end << std::endl;
                    new_words.emplace(std::move(word));
                    substring.clear();
                    break;
                }
            }
        }
        if (words.empty() || words.back().end != s.size() - 1) { return sentences; }
        //print(words); 
        generate_sentences(s, s.size() -1, words, words.size() - 1, "", sentences);
        return sentences;
    }

    void generate_sentences(const std::string& s, int s_index, 
                            const Words& words, int w_index, 
                            std::string sentence, Sentences& sentences) {
        if (s_index < 0) { 
            sentence.pop_back(); // remove last space
            sentences.emplace_back(std::move(sentence)); 
            return;
        }
        
        for (auto i = w_index; i >= 0;  --i) {
            if (words[i].end < s_index) { break; }
            if (words[i].end == s_index) {
                auto word = s.substr(words[i].start, words[i].end - words[i].start + 1);
                word.append(1, ' ');
                word.append(sentence);
                generate_sentences(s, words[i].start - 1, words, i-1, word, sentences);
            }
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
    //for (auto& s : sentences) { std::cout << s << std::endl; }
    //std::cout << std::endl;
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
    //auto start = std::chrono::high_resolution_clock::now();
    test_word_break();
    //auto end = std::chrono::high_resolution_clock::now();
    //std::chrono::duration<double> elapsed = (end - start);
    //std::cout << "Elapsed: " << elapsed.count() << std::endl;
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
