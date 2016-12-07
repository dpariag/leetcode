// Leetcode: https://leetcode.com/problems/palindrome-partitioning/
// Given a string s, partition s such that every substring of the partition is a palindrome.
// Return all possible palindromic partitionings of s.
// Example: given s = "aab", return {{"aa","b"}, {"a","a","b"}}

#include <vector>
#include <string>
#include <iostream>
#include <assert.h>

using Partition = std::vector<std::string>;
using Partitions = std::vector<Partition>;

// Accepted. 96ms. Beats 10.75% of submissions, ties 0.51% of submissions.
class Solution {
public:
    inline bool is_palindrome(const std::string& s) {
        auto len = s.size();
        for (auto i = 0u; i < (len / 2); ++i) {
            if (s[i] != s[len-i-1]) { return false;}
        }
        return true;
    }

    Partitions partition(const std::string& s) {
        if (s.size() == 0) { return Partitions(); }
        if (s.size() == 1) { return Partitions({Partition({s})}); }

        Partitions result;
        if (is_palindrome(s)) {
            result.emplace_back(Partition({s}));
        }

        for (int i = s.size() - 1; i >= 0; --i) {
            // Process string right to left to make building the partition faster
            auto right = s.substr(i);   // right fragment
            if (is_palindrome(right)) {
                auto left = s.substr(0,i);
                auto left_partition = partition(left);
                for (auto& p : left_partition) {
                    p.emplace_back(right);
                }
                result.insert(result.end(), left_partition.begin(), left_partition.end());
            }
        }
        return result;
    }
};

void print(const Partitions& partitions) {
    for (auto& partition : partitions) {
        for (auto& p : partition) {
            std::cout << p << " ";
        }
        std::cout << std::endl;
    } 
}

bool test_partition(std::string s, Partitions expected) {
    Solution soln;

    auto p = soln.partition(s);
    std::sort(p.begin(), p.end());
    std::sort(expected.begin(), expected.end());

    std::cout << "Got" << std::endl;
    print(p);
    std::cout << "Expected" << std::endl;
    print(expected);

    return p == expected;
}

void test_partition() {
    assert(test_partition("aab", Partitions({{"a","a","b"}, {"aa", "b"}})));
    assert(test_partition("abba", Partitions({{"a","b","b","a"}, {"abba"}, {"a", "bb", "a"}})));
    assert(test_partition("aaaaa", 
        Partitions({{"a","a","a","a","a"}, 
                    {"aa","a","a","a"}, {"a","aa","a","a"}, {"a","a","aa","a"}, {"a","a","a","aa"},
                    {"aa", "aa", "a"}, {"aa", "a", "aa"}, {"a","aa","aa"},
                    {"aaa","a","a"}, {"aaa","aa"}, {"a","aaa","a"}, {"aa","aaa"},{"a","a","aaa"},
                    {"aaaa","a"}, {"aaaaa"},
                    {"a","aaaa"}})));
}

void test_palindrome() {
    Solution soln;

    assert(soln.is_palindrome("a") == true);
    assert(soln.is_palindrome("aa") == true);
    assert(soln.is_palindrome("ab") == false);
    assert(soln.is_palindrome("abba") == true);
    assert(soln.is_palindrome("abcba") == true);
    assert(soln.is_palindrome("abcdba") == false);
    assert(soln.is_palindrome("abccba") == true);
}

int main(int argc, char** argv) {
    test_palindrome();
    test_partition();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
