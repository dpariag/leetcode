// Leetcode: https://leetcode.com/problems/partition-labels/description/
// Given a string s of lowercase letters, partition s into as many parts as possible so that each letter
// appears in at most one part. Return a the lengths of each partition.

// Brute Force: Generate all partitions of s, check which are valid and track max number.
// Better: First pass: count the chars in s. Second pass: Decrement the count of each char,
// and if it is zero, remove it from the set of chars in the current partition. The partition
// is counted when it's char set is empty. O(n) time.

#include <vector>
#include <unordered_set>
#include <iostream>
#include <assert.h>

using CharSet = std::unordered_set<char>;

// Accepted. 10ms. Beats 51.33% of submissions.
class Solution {
public:
    std::vector<int> partitionLabels(const std::string& s) {
        std::vector<int> part_lengths;
        CharSet char_set;
        int counts[26] = {0};

        for (auto ch : s) {
            ++counts[ch-'a'];
        }

        int length = 0;
        for (int i = 0; i < s.size(); ++i) {
            --counts[s[i]-'a'];
            ++length;
            if (counts[s[i]-'a'] == 0) {
                char_set.erase(s[i]);
                if (char_set.empty()) {
                    part_lengths.emplace_back(length);
                    length = 0;
                }
            } else {
                char_set.emplace(s[i]);
            }
        }
        return part_lengths;
    }
};

bool test_partition(std::string s, std::vector<int> expected) {
    Solution soln;
    return soln.partitionLabels(s) == expected;
}

void test_partition() {
    assert(test_partition("a", {1}));
    assert(test_partition("abcd", {1,1,1,1}));
    assert(test_partition("abcda", {5}));
    assert(test_partition("abacdcdefegehh", {3,4,5,2}));
    assert(test_partition("babcdcfghjic", {3,9}));
}

int main(int argc, char** argv) {
    test_partition();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}