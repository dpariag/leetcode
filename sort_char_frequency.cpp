// Leetcode: https://leetcode.com/problems/sort-characters-by-frequency/description/
// Given a string, sort it in decreasing order based on the frequency of characters.

// Brute Force: 
// Better: Sort chars in the string by their frequency, then generate the result string.

#include <vector>
#include <iostream>
#include <assert.h>

// Accepted. 12ms. Beats 94.09% of submissions, ties 4.46% of submissions.
class Solution {
public:
    std::string frequencySort(const std::string& s) {
        std::string result;

        // Count frequency of each character
        std::vector<int> counts(255, 0);
        for (auto ch : s) {
            counts[int(ch)]++;
        }

        // Get a list of unique characters in the string
        std::string chars;
        for (int i = 0; i < 255; ++i) {
            if (counts[i] > 0) { chars.append(1, char(i)); }
        }

        // Sort character by their frequency in the original string
        std::sort(chars.begin(), chars.end(), 
                  [counts](char a, char b) { return counts[a] > counts[b]; });

        // Build result string
        for (auto ch : chars) {
            result.append(counts[ch], ch);
        }
        return result;
    }
};

void test_frequency_sort() {
    Solution soln;
    // Tests assume that ties are broken lexicographically
    assert(soln.frequencySort("") == "");
    assert(soln.frequencySort("a") == "a");
    assert(soln.frequencySort("tree") == "eert");
    assert(soln.frequencySort("cccaaa") == "aaaccc"); 
    assert(soln.frequencySort("Aabb") == "bbAa");
}

int main(int argc, char** argv) {
    test_frequency_sort();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
