// Leetcode: https://leetcode.com/problems/reorganize-string/description/

// Brute Force:
// Better:

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <assert.h>

static const int NUM_CHARS = 26;
using CharCounts = int[NUM_CHARS];

// Accepted. 4ms. Beats 94.53% of submissions.
class Solution {
public:

    inline char find_next(const CharCounts counts, char avoid) {
        int max = 0;
        char max_char = '\0';
        
        for (int i = 0; i < NUM_CHARS; ++i) {
            char cur = 'a' + i;
            if (counts[i] > max && cur != avoid) {
                max = counts[i];
                max_char = cur;                
            }
        }
        return max_char;
    }

    std::string reorganizeString(const std::string& s) {
        std::string result;
        result.reserve(s.size());
        CharCounts counts = {0};
        
        for (auto ch : s) {
            ++counts[ch-'a'];
        }

        char avoid = '\0';
        while (result.size() < s.size()) {
            auto ch = find_next(counts, avoid);
            if (ch == '\0') return std::string();
            result.push_back(ch);
            --counts[ch-'a'];
            avoid = ch;
        }
        return result;
    }
};

using Strings = std::vector<std::string>;

bool test_reorganize_string(std::string s, Strings expected) {
    Solution soln;
    std::string result = soln.reorganizeString(s);

    auto found = std::find(expected.begin(), expected.end(), result);
    return found != expected.end();
}

void test_reorganize_string() {
    assert(test_reorganize_string("aaab", {""}));
    assert(test_reorganize_string("ab", {"ab", "ba"}));
    assert(test_reorganize_string("aaabb", {"ababa"}));
    assert(test_reorganize_string("aaabbb", {"ababab", "bababa"}));
    assert(test_reorganize_string("abc", {"abc", "acb", "bca", "bac", "cab", "cba"}));
}

int main(int argc, char** argv) {
    test_reorganize_string();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}