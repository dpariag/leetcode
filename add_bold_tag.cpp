// Leetcode: https://leetcode.com/problems/add-bold-tag-in-string/description/
// Given a string S and a dictionary D, enclose any substring of S that exists in D in a pair of
// bold tags <b> and </b>. If two substrings overlap, enclose them in one pair of tags. 
// If two substrings are consecutive, combine them.

// Brute Force:
// Better:

#include <string>
#include <vector>
#include <map>
#include <unordered_set>
#include <iostream>
#include <assert.h>

using Dictionary = std::unordered_set<std::string>;

struct Range {
    int start = 0;
    int end = 0;
    Range(int s, int e) : start(s), end(e) {}
};

using Ranges = std::vector<Range>;
using OrderedRanges = std::multimap<int, int>; // start -> end of a substring

// Accepted. 69ms. Beats 43.51% of submissions, ties 0.35% of submissions.
class Solution {
public:
    std::string addBoldTag(const std::string s, const std::vector<std::string>& words) {
        if (s.empty()) { return s; }
        Dictionary dict(words.size()*2);
        std::unordered_set<int> lengths(words.size());

        for (auto& word : words) {
            if (word.empty()) continue;
            dict.emplace(word);
            lengths.emplace(int(word.size()));
        }       
 
        OrderedRanges ranges;
        for (auto length : lengths) {
            for (int i = 0; i <= (int(s.size()) - length); ++i) {
                std::string sub = s.substr(i, length);
                if (dict.count(sub) > 0) {
                    ranges.emplace(i, i + length -1);
                }
            }
        }
        
        Ranges merged; 
        for (auto iter = ranges.begin(); iter != ranges.end(); ++iter) {
            if (merged.empty()) {
                merged.emplace_back(iter->first, iter->second);
            } else if (iter->first <= merged.back().end+1) {
                merged.back().end = std::max(merged.back().end, iter->second);
            } else {
                merged.emplace_back(iter->first, iter->second);
            }
        }

        std::string result;
        result.reserve(s.size()*2);
        int start = 0;
        for (auto& range : merged) {
            if (start < s.size()) {
                result.append(s.substr(start, range.start - start));                
            }
            result.append("<b>");
            result.append(s.substr(range.start, range.end-range.start+1));
            result.append("</b>");
            start = range.end + 1;
        }
        if (start < s.size()) {
            result.append(s.substr(start, s.size() - start + 1));
        }
        return result;
    }
};

bool test_bold_tags(std::string s, std::vector<std::string> words, std::string expected) {
    Solution soln;
    auto result = soln.addBoldTag(s, words);
    return result == expected;
}

void test_bold_tags() {
    assert(test_bold_tags("", {"abc", "fg"}, ""));
    assert(test_bold_tags("abcdefg", {"bcd"}, "a<b>bcd</b>efg"));
    assert(test_bold_tags("abcdefg", {"bcd", "fg"}, "a<b>bcd</b>e<b>fg</b>"));
    assert(test_bold_tags("abcdefg", {"abcd", "fg"}, "<b>abcd</b>e<b>fg</b>"));
    assert(test_bold_tags("abcdefg", {"abcd", "bcd", "fg"}, "<b>abcd</b>e<b>fg</b>"));
    assert(test_bold_tags("abcdefg", {"abcd", "bc", "fg"}, "<b>abcd</b>e<b>fg</b>"));
    assert(test_bold_tags("abcdefg", {"abcd", "abc", "fg"}, "<b>abcd</b>e<b>fg</b>"));
    assert(test_bold_tags("abcdefg", {"bcd", "abc", "cde", "fg"}, "<b>abcdefg</b>"));
    assert(test_bold_tags("abcdefg", {"abc", "de", "fg"}, "<b>abcdefg</b>"));
    assert(test_bold_tags("abcdefg", {"abc", "fg"}, "<b>abc</b>de<b>fg</b>"));

}

int main(int argc, char** argv) {
    test_bold_tags();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
