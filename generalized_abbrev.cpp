// Leetcode: https://leetcode.com/problems/generalized-abbreviation/description/
// Write a function to generate the generalized abbreviations of a word.

// Approach: Recognize that a2b represent a__b. Each character can be included or not
// leading to top-down recursive enumeration. For short words, can be computed using
// integer bitmasks.

#include <vector>
#include <iostream>
#include <assert.h>

using Abbrevs = std::vector<std::string>;

// Accepted. 26ms. Beats 89.76% of submissions, ties 7.53% of submissions.
class Solution {
public:

    void gen_abbrevs(const std::string& word, int index, int span,
                     std::string cur, Abbrevs& result) {
        if (index >= word.size()) {
            // Append anything in span
            if (span > 0) { cur.append(std::to_string(span)); }
            result.emplace_back(cur);
            return;
        }

        // Abbreviate cur character
        gen_abbrevs(word, index+1, span+1, cur, result);

        // Include the current character
        if (span > 0) { cur.append(std::to_string(span)); }
        gen_abbrevs(word, index+1, 0, cur + word[index], result);
    }

    Abbrevs generateAbbreviations(const std::string& word) {
        Abbrevs result;
        gen_abbrevs(word, 0, 0, "", result);
        return result;
    }
};

void test_abbrevs() {
    Solution soln;
    auto abbrevs = soln.generateAbbreviations("word");
    std::sort(abbrevs.begin(), abbrevs.end());

    Abbrevs expected({"word", "1ord", "w1rd", "wo1d", "wor1", "2rd", "w2d", "wo2", 
                      "1o1d", "1or1", "w1r1", "1o2", "2r1", "3d", "w3", "4"});
    std::sort(expected.begin(), expected.end());
    assert(abbrevs == expected);
}

int main(int argc, char** argv) {
    test_abbrevs();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
