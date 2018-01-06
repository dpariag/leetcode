// Leetcode: https://leetcode.com/problems/sentence-similarity-ii/description/
// Given two sentences, and a list of similar word pairs pairs, determine if two sentences are similar.
// Word similarity is symmetric and transitive and a word is similar to itself.
// Sentences are similar if and only if the i'th words of each sentence are similar.

// Brute Force:
// Better:

#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <assert.h>

using Words = std::vector<std::string>;
using WordPair = std::pair<std::string, std::string>;
using WordPairs = std::vector<WordPair>;
using SimilarityMap = std::unordered_map<std::string, Words>;

class Solution {
public:
    bool produces(const std::string& word, const std::string& target, const SimilarityMap& similar) {
        std::queue<std::string> q;
        std::unordered_set<std::string> visited;
        
        q.emplace(word);
        visited.emplace(word);
        while (!q.empty()) {
            auto cur_word = q.front();
            q.pop();

            if (cur_word == target) { return true; }

            auto found = similar.find(cur_word);
            if (found == similar.end()) { continue; }

            //const auto& next_words = similar[cur_word];
            for (const auto& next : found->second) {
                if (visited.count(next) == 0) {
                    visited.emplace(next);
                    q.emplace(next);
                }
            }            
        }
        return false;
    }

    bool areSentencesSimilarTwo(Words& words1, Words& words2, WordPairs& pairs) {
        SimilarityMap similar;

        for (const auto& p : pairs) {
            similar[p.first].emplace_back(p.second);
            similar[p.second].emplace_back(p.first);
        }

        if (words1.size() != words2.size()) { return false; }
        for (int i = 0; i < words1.size(); ++i) {
            if (!produces(words1[i], words2[i], similar)) { return false; }
        }
        return true;
    }
};

int main(int argc, char** argv) {
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
