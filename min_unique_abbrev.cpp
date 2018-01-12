// Leetcode: https://leetcode.com/problems/minimum-unique-word-abbreviation/description/

// Approach: Use bitmasks to represent abbreviations of the target word.
// Generate all bitmasks and sort them by abbreviation length.
// Iterate masks in sorted order and return the first one that does produce any dictionary word.
// O(2^m*logm + m*n)

#include <vector>
#include <limits>
#include <algorithm>
#include <iostream>
#include <assert.h>

struct Mask {
    int mask;
    int len = 0;
};

using Masks = std::vector<Mask>;
using Strings = std::vector<std::string>;

// Accepted. 353ms. Beats 12.86% of submissions, ties < 1% of submissions.
class Solution {
public:
    inline bool produces(std::string& abbrev, std::string& word) {
        int i = 0, j = 0;
        while (i < abbrev.size() && j < word.size()) {
            if (std::isalpha(abbrev[i])) {
                if (abbrev[i] != word[j]) { return false; }
                ++i, ++j;
            } else if (std::isdigit(abbrev[i])) {
                int digit = 0;
                while (i < abbrev.size() && std::isdigit(abbrev[i])) {
                    digit = (digit*10) + (abbrev[i] - '0');
                    ++i;
                }
                j += digit;
                if (j > word.size()) { return false; }
            }
        }
        return (i == abbrev.size() && j == word.size());
    }

    // shift gives the leftmost bit possible in mask
    inline int get_mask_len(int shift, int mask) {
        int bit = (1 << shift);
        int len = 0;
        while (bit > 0) {
            bool ones = false;
            while (bit > 0 && (bit&mask) != 0) { bit >>= 1; ones = true; }
            len += ones ? 1 : 0;
            while (bit > 0 && (bit&mask) == 0) { bit >>= 1; ++len; }
        }
        return len;
    }

    std::string gen_abbrev(const std::string& target, int mask) {
        std::string abbrev;
        if (target.empty()) { return abbrev; }

        abbrev.reserve(target.size());
        int bit = (1 << (target.size() - 1));
        int index = 0, span = 0;
        while (bit > 0 && index < target.size()) {
            if (bit & mask) {
                // Skip char
                ++span;
            } else {
                if (span > 0) {
                    abbrev.append(std::to_string(span));
                    span = 0;
                }
                abbrev.append(1, target[index]);
            }
            ++index;
            bit >>= 1;
        }
        
        if (span > 0) { 
            abbrev.append(std::to_string(span));
        }
        return abbrev;
    }

    std::string minAbbreviation(std::string& target, Strings& dictionary) {
        Strings words;
        words.reserve(dictionary.size());        
        for (auto& word : dictionary) {
            if (word.size() == target.size()) { words.emplace_back(word); }
        }

        int sz = target.size();
        int value = (1 << sz) - 1;
        Masks masks(1 << sz);
        for (auto& m : masks) {
            m.mask = value--;
            m.len = get_mask_len(sz-1, m.mask);
        }
        std::sort(masks.begin(), masks.end(), [](const Mask& m1, const Mask& m2) { return m1.len < m2.len; });

        for (auto& m : masks) {
            auto abbrev = gen_abbrev(target, m.mask);
            bool conflicts = false;
            for (auto& w : words) {
                if (produces(abbrev, w)) {
                    // Conflicts!
                    conflicts = true;
                    break;
                }
            }
            if (!conflicts) {
                return abbrev;
            }
        }
        return "";
    }
};

bool test_min_abbrev(std::string target, Strings words, std::string expected_abbrev) {
    Solution soln;
    return soln.minAbbreviation(target, words) == expected_abbrev;
}

void test_min_abbrev() {
    assert(test_min_abbrev("apple", {"blade", "plain", "amber"}, "2p2"));
    assert(test_min_abbrev("apple", {"blade"}, "a4"));
}

int main(int argc, char** argv) {
    test_min_abbrev();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
