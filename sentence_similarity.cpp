// Leetcode: https://leetcode.com/problems/sentence-similarity/description/

// Brute Force:
// Better:

#include <vector>
#include <algorithm>
#include <unordered_map>
#include <iostream>
#include <assert.h>

using Sentence = std::vector<std::string>;
using Pairs = std::vector<std::pair<std::string, std::string>>;
using WordMap = std::unordered_map<std::string, std::vector<std::string>>;

// Accepted. 9ms. Beats 10.91% of submissions, ties 53.34% of submissions.
class Solution {
public:
    bool areSentencesSimilar(const Sentence& s1, const Sentence& s2, const Pairs& pairs) {
        if (s1.size() != s2.size()) { return false; }
        
        WordMap word_map(pairs.size()*2);
        for (const auto& p : pairs) {
            word_map[p.first].emplace_back(p.second);
            word_map[p.second].emplace_back(p.first);
        }

        for (int i = 0; i < s1.size(); ++i) {
            if (s1[i] == s2[i]) { continue; } // self-similar

            const auto& similar = word_map[s1[i]];
            auto found = std::find(similar.begin(), similar.end(), s2[i]);
            if (found == similar.end()) {
                return false;
            }
        }
        return true;
    }
};

void test_similar_sentences() {
    Solution soln;

    assert(soln.areSentencesSimilar({},{},{{}}) == true);
    assert(soln.areSentencesSimilar({"hello"},{"hello"},{{}}) == true);
    assert(soln.areSentencesSimilar({"hello", "world"},{"hello"},{{}}) == false);
    assert(soln.areSentencesSimilar({"hello", "world"},{"hello", "everyone"},{{"world", "everyone"}}) == true);
    assert(soln.areSentencesSimilar({"hello", "world", "bye!"},{"hi", "everyone", "bye!"},
                                    {{"hi", "hello"},{"world", "everyone"}}) == true);
}

int main(int argc, char** argv) {
    test_similar_sentences();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
