// Leetcode: https://leetcode.com/problems/implement-magic-dictionary/description/

// Approach: Use an unordered_set to store words, lookup every character alteration of the given word.
// Using a trie would be faster in the average case, but is probably overkill for this problem.

#include <vector>
#include <iostream>
#include <unordered_set>
#include <assert.h>

// Accepted. 4ms. Beats 12.78% of submissions, ties < 1% of submissions.
class MagicDictionary {
public:
    MagicDictionary() {}
    
    void buildDict(const std::vector<std::string>& dict) {
        for (auto& word : dict) {
            m_dict.emplace(word);
            m_lengths.emplace(word.size());
        }
    }
    
    bool search(std::string& word) {
        if (m_lengths.count(word.size()) == 0) { return false; }

        for (int i = 0; i < word.size(); ++i) {
            char orig = word[i];
            for (char ch = 'a'; ch <= 'z'; ++ch) {                
                if (ch != orig) {
                    word[i] = ch;
                    if (m_dict.count(word)) { return true; }
                }
            }
            word[i] = orig;
        }
        return false;
    }
private:
    std::unordered_set<std::string> m_dict;
    std::unordered_set<size_t> m_lengths;
};

int main(int argc, char** argv) {
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}