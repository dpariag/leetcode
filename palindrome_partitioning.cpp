// Leetcode: https://leetcode.com/problems/palindrome-partitioning/
// Given a string s, partition s such that every substring of the partition is a palindrome.
// Return all possible palindromic partitionings of s.
// Example: given s = "aab", return {{"aa","b"}, {"a","a","b"}}

// Is a DP, table-driven approach possible? table[i][j] is true iff s[i..j] is a palindrome.
// Fill out the diagonal first (substrings of length 1).
// Then fill out substrings of length 2,3,...,n
// After construction, walk the first row of the table, building decompositions.
// O(n^2) time and space.

#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>
#include <assert.h>

using Partition = std::vector<std::string>;
using Partitions = std::vector<Partition>;
using PartitionMap = std::unordered_map<std::string, Partitions>;

// Accepted. 52ms. Beats 23.23% of submissions, ties 0.51% of submissions.
class Solution1 {
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

        auto found = m_partitions.find(s);
        if (found != m_partitions.end()) {
            return found->second;
        }

        Partitions result;
        if (is_palindrome(s)) {
            result.emplace_back(Partition({s}));
        }

        for (int i = s.size() - 1; i >= 1; --i) {
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
        m_partitions.emplace(s, result);
        return result;
    }
private:
    PartitionMap m_partitions;
};

class Solution2 {
public:
    using Table = std::vector<std::vector<bool>>;

    Table build_table(const std::string& s) {
        Table table(s.size(), std::vector<bool>(s.size(), false));

        // Substrings of length 1 are always palindromic
        for (auto i = 0u; i < s.size(); ++i) { table[i][i] = true; }

        for (auto len = 2u; len <= s.size(); ++len) {
            for (auto row = 0; row <= s.size() - len; ++row) {
                auto col = row + len - 1;
                if (len == 2) {
                    table[row][col] = s[row] == s[col];
                } else {
                    table[row][col] = s[row] == s[col] && table[row+1][col-1];
                }
            }
        }
        return table;
    }

    void partition_search(Partitions& partitions, Partition partition,
                          const Table& table, const std::string& s, int start) {
        //std::cout << "s = " << s << std::endl;
        //std::cout << "start = " << start << std::endl;
        if (start >= s.size()) {
            partitions.emplace_back(partition);
            return;
        }

        /*
        if (table[start][s.size()-1]) {
            // s[start...end] is a palindrome
            partition.emplace_back(s.substr(start));
            partitions.emplace_back(partition);
            partition_search(partitions, partition, table, s, s.size());
            partition.pop_back();
        }
        */

        for (auto i = start; i < s.size(); ++i) {
            if (table[start][i]) {
                partition.emplace_back(s.substr(start, i - start + 1));
                partition_search(partitions, partition, table, s, i+1);
                partition.pop_back();
            }
        }
    }

    Partitions partition(const std::string& s) {
        Partitions result;
        Partition p;
        Table table = build_table(s);
        /*
        for (auto i = 0; i < table.size(); ++i) {
            for(auto j = 0; j < table.size(); ++j) {
                std::cout << (table[i][j] ? "T" : "F") << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
        */
        partition_search(result, p, table, s, 0);
        return result;
    }

private:
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
    Solution1 soln1;
    Solution2 soln2;

    auto p1 = soln1.partition(s);
    std::sort(p1.begin(), p1.end());

    auto p2 = soln2.partition(s);
    std::sort(p2.begin(), p2.end());

    std::sort(expected.begin(), expected.end());

    /*
    std::cout << "Got" << std::endl;
    print(p2);
    std::cout << "Expected" << std::endl;
    print(expected);
    std::cout << std::endl;
    */
    return p1 == expected && p2 == expected;
    //return p2 == expected;
}

void test_partition() {
    assert(test_partition("abba", Partitions({{"a","b","b","a"}, {"abba"}, {"a", "bb", "a"}})));
    assert(test_partition("aab", Partitions({{"a","a","b"}, {"aa", "b"}})));
    assert(test_partition("aaaaa", 
        Partitions({{"a","a","a","a","a"}, 
                    {"aa","a","a","a"}, {"a","aa","a","a"}, {"a","a","aa","a"}, {"a","a","a","aa"},
                    {"aa", "aa", "a"}, {"aa", "a", "aa"}, {"a","aa","aa"},
                    {"aaa","a","a"}, {"aaa","aa"}, {"a","aaa","a"}, {"aa","aaa"},{"a","a","aaa"},
                    {"aaaa","a"}, {"aaaaa"},
                    {"a","aaaa"}})));
}

void test_solution_2() {
    Solution2 soln;
    soln.partition("abba");
    soln.partition("babe");
    soln.partition("babab");
}

int main(int argc, char** argv) {
    //test_solution_2();
    test_partition();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
