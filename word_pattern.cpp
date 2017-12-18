// Leetcode: https://leetcode.com/problems/word-pattern/description/
// Given a pattern and a string str, find if str follows the same pattern (i.e., there is a bijection
// between each letter in pattern and a non-empty word in str).

// Brute Force: For every char encountered in pattern, scan str and vice versa. O(n*m) time.
// Better: Use two hash maps to construct the bijection. O(n+m) time.

#include <vector>
#include <unordered_map>
#include <iostream>
#include <assert.h>

using CharMap = std::unordered_map<char, std::string>;
using StringMap = std::unordered_map<std::string, char>;

// Accepted. 0ms. Beats 33.33% of submissions, ties 66.67% of submissions.
class Solution {
public:
    bool wordPattern(const std::string& pattern, const std::string& str) {
        CharMap char_map(pattern.size()*2);
        StringMap word_map(pattern.size()*2);
        int i = 0, pos = 0;
        
        while (i < pattern.size() && pos < str.size()) {
            int next = str.find(' ', pos);
            if (next == std::string::npos) { next = str.size(); }
            
            auto word = str.substr(pos, next-pos);
            auto ch = pattern[i];

            auto found_char = char_map.find(ch);
            auto found_word = word_map.find(word);
            if (found_char == char_map.end() && found_word == word_map.end()) {
                char_map[ch] = word;
                word_map[word] = ch;
            } else if (found_char != char_map.end() && found_word != word_map.end()) {
                if (found_char->second != word || found_word->second != ch) { return false; }
            } else {
                return false;
            }
            ++i;
            pos = next+1;
        }
        return i >= pattern.size() && pos >= str.size();
    }
};

void test_word_pattern() {
    Solution soln;

    assert(soln.wordPattern("", "") == true);
    assert(soln.wordPattern("abba", "dog cat cat dog") == true);
    assert(soln.wordPattern("abba", "dog cat cat fish") == false);
    assert(soln.wordPattern("aaaa", "dog cat cat dog") == false);
    assert(soln.wordPattern("abba", "dog dog dog dog") == false);
    assert(soln.wordPattern("abbac", "dog cat cat dog") == false);
    assert(soln.wordPattern("abba", "dog cat cat dog cat") == false);
    assert(soln.wordPattern("abbac", "dog cat cat dog cat") == false);
    assert(soln.wordPattern("abbac", "dog cat cat dog fish") == true);
}

int main(int argc, char** argv) {
    test_word_pattern();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
