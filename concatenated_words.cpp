// Leetcode: https://leetcode.com/problems/concatenated-words/#/description
// Given a dictionary, return all concatenated words from the list of words. A concatenated word is 
// one that is a concatenation of two or more shorter words in the dictionary. 
// Example:
// Input: ["cat","cats","catsdogcats","dog","dogcatsdog","hippopotamuses","rat","ratcatdogcat"]
// Output: ["catsdogcats","dogcatsdog","ratcatdogcat"]
//
// Brute Force:
// Better:

#include <vector>
#include <iostream>
#include <unordered_set>
#include <algorithm>
#include <assert.h>

using Words = std::vector<std::string>;
using Dict = std::unordered_set<std::string>;

// Accepted. 342ms. Beats 57.34% of submissions and ties 0.5% of submissions.
class Solution {
public:
    bool is_concatenation(const std::string& word, const Dict& dict) {
        //std::cout << "Word = " << word << std::endl;
        std::vector<bool> is_prefix(word.size(), false);
        std::string prefix;
        prefix.reserve(word.size());

        for (int i = 0; i < word.size(); ++i) {
            prefix.append(1, word[i]);
            is_prefix[i] = (i < word.size() - 1) && dict.count(prefix) > 0;
            //std::cout << "word[" << i << "] = " << is_prefix[i] << std::endl;

            if (!is_prefix[i]) {
                for (int j = 0; j < i; ++j) {
                    if (is_prefix[j]) {
                        //std::cout << "found prefix " << word.substr(0, j+1) << std::endl;
                        //std::cout << "trying " << word.substr(j+1, i-j) << std::endl;
                        if (dict.count(word.substr(j+1, i-j)) > 0) {
                            is_prefix[i] = true;
                            break;
                        }
                    }
                }
            }
        }
        return is_prefix.back();
    }

    Words findAllConcatenatedWordsInADict(const Words& words) {
        Words concatenations;
        Dict dict(words.begin(), words.end());
        for (const auto& w : words) {
            if (is_concatenation(w, dict)) {
                concatenations.emplace_back(w);
                //std::cout << w << " is a concatenation" << std::endl;
            }
        }
        return concatenations;
    }
};

bool test_concatenated_words(const Words& words, Words expected_concatenations) {
    Solution soln;

    auto concatenations = soln.findAllConcatenatedWordsInADict(words);
    std::sort(concatenations.begin(), concatenations.end());
    std::sort(expected_concatenations.begin(), expected_concatenations.end());
    for (int i = 0; i < concatenations.size(); ++i) {
        //std::cout << "Got: " << concatenations[i] << " expected " << expected_concatenations[i] << std::endl;
    }
    return concatenations == expected_concatenations;
}

void test_concatenated_words() {
    assert(test_concatenated_words({"a", "b", "abc", "ab", "abb"}, {"ab", "abb"}));
    assert(test_concatenated_words({"a", "b", "abc", "ab", "aba"}, {"ab", "aba"}));
    assert(test_concatenated_words({"a", "b", "abc", "bc", "aba"}, {"abc", "aba"}));
    assert(test_concatenated_words({"a", "b", "aaaa", "bbbb", "abba"}, {"aaaa", "bbbb", "abba"}));
    assert(test_concatenated_words({"abb", "bba", "abba", "abbba", "abbbba"}, {"abbbba"}));
    assert(test_concatenated_words({"cat", "dog", "catdog"}, {"catdog"}));
    assert(test_concatenated_words({"cat","cats","catsdogcats","dog","dogcatsdog","hippopotamuses",
                                    "rat","ratcatdogcat"},
                                   {"catsdogcats","dogcatsdog","ratcatdogcat"}));
}

int main(int argc, char** argv) {
    test_concatenated_words();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
