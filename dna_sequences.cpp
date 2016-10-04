// Leetcode: https://leetcode.com/problems/repeated-dna-sequences/
// DNA is composed of a series of nucleotides abbreviated as A, C, G, and T (e.g., "ACGAATTCCG"). 
// When studying DNA, it is sometimes useful to identify repeated sequences within the DNA.
// Find all the 10-letter-long substrings that occur more than once in a DNA molecule.
// Example: Given "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT", return {"AAAAACCCCC", "CCCCCAAAAA"}.

// Brute Force: Generate every 10 char substring, search the original string for it. O((n-m)*(m*n))
// Better: Use a hash table to store and count substrings. O((n-m)*m)
// Possibly: Use Rabin-Karp style rolling hash to reduce hashing cost but still worst case O((n-m)*m)

#include <vector>
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <assert.h>

using Strings = std::vector<std::string>;
using RefCounts = std::unordered_map<std::string, unsigned>;

// Accepted. 129ms. Beats 72.49% of submissions and ties 2.14% of submissions.
class Solution {
public:
    Strings findRepeatedDnaSequences(std::string s) {
        Strings result;
        RefCounts counts;

        for (auto i = 0; i < s.size(); ++i) {
            auto substr = s.substr(i, 10);
            ++counts[substr];
        }

        for (auto& c : counts) {
            if (c.second > 1) {
                result.emplace_back(c.first);
            }
        }
        return result;
    }
};

bool test_repeated(const std::string& s, Strings expected) {
    Solution soln;
    auto repeated = soln.findRepeatedDnaSequences(s);

    std::sort(repeated.begin(), repeated.end());
    std::sort(expected.begin(), expected.end());
    return repeated == expected;
}

void test_repeated() {
    assert(test_repeated("AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT", {"AAAAACCCCC", "CCCCCAAAAA"}));
    assert(test_repeated("AAAAAAAAAAAA", {"AAAAAAAAAA"}));
    assert(test_repeated("AAACCCCCCCAAACCCCCCC", {"AAACCCCCCC"}));
    assert(test_repeated("AAACCCCCCCTTTAAACCCCCCC", {"AAACCCCCCC"}));
    assert(test_repeated("AAACCCCCCCTTTAAACCCCCCCTTT", 
                         {"AAACCCCCCC","AACCCCCCCT","ACCCCCCCTT","CCCCCCCTTT"}));
}

int main(int argc, char** argv) {
    test_repeated();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
