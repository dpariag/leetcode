// Leetcode: https://leetcode.com/problems/ransom-note/description/
// Given a ransom note and a magazine, determine if the note can be 
// constructed from the magazine's characters

// Brute Force: For each char in the note, scan the magazine to find it and then remove it.
// Better: Count chars in the note. Scan the magazine decrementing char counts, 
// and stopping when all counts are zero.

#include <vector>
#include <unordered_map>
#include <iostream>
#include <assert.h>

using CharCounts = std::unordered_map<char, int>;

// Accepted. 22ms. Beats 79.80% of submissions, ties 14.83% of submissions.
class Solution {
public:
    bool canConstruct(const std::string& ransomNote, const std::string& magazine) {
        CharCounts counts;

        for (auto ch : ransomNote) { counts[ch]++; }

        for (auto ch : magazine) {
            if (counts.count(ch)) {
                int count = --counts[ch];
                if (count == 0) { counts.erase(ch); }
            }
            if (counts.empty()) { return true; }
        }
        return counts.empty();
    }
};

void test_can_construct() {
    Solution soln;

    assert(soln.canConstruct("", "") == true);
    assert(soln.canConstruct("aa", "aab") == true);
    assert(soln.canConstruct("aa", "ab") == false);
    assert(soln.canConstruct("aa", "aa") == true);
    assert(soln.canConstruct("abc", "bcadef") == true);
    assert(soln.canConstruct("abc", "badef") == false);
}

int main(int argc, char** argv) {
    test_can_construct();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
