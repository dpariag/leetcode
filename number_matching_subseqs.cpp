// Leetcode: https://leetcode.com/problems/number-of-matching-subsequences/description/
// https://leetcode.com/problems/number-of-matching-subsequences/description/
// Given a string s, and a list of words, find the number of words that are subsequences of s.

// Brute Force: Generate all subsequences of s, and match against words. Exponential time.
// Better: Build a list of indices of each character in s. Iterate letters in each word and use
// binary search to find a matching letter in s. O(m*logn) time.

#include <algorithm>
#include <assert.h>
#include <iostream>
#include <string>
#include <vector>

using Table = std::vector<std::vector<int>>;

// Accepted. 124ms. Beats 71.74% of cpp submissions.
class Solution {
public:
  int numMatchingSubseq(const std::string &s,
                        const std::vector<std::string> &words) {
    Table letter_indices(26, std::vector<int>());

    // Store the indices of each letter
    for (int i = 0; i < s.size(); ++i) {
      auto ch = s[i];
      letter_indices[ch - 'a'].emplace_back(i);
    }

    int num_subseq = 0;
    for (const auto &word : words) {
      int s_idx = -1; // index of character in s that we are matching
      int chars_matched = 0;
      for (int i = 0; i < word.size(); ++i) {
        auto ch = word[i];
        const auto &indices = letter_indices[ch - 'a'];
        auto iter = std::upper_bound(indices.begin(), indices.end(), s_idx);
        if (iter == indices.end())
          break;
        ++chars_matched;
        s_idx = *iter;
      }
      if (chars_matched == word.size())
        ++num_subseq;
    }
    return num_subseq;
  }
};

bool test_matching(std::string s, std::vector<std::string> words,
                   int expected) {
  Solution soln;
  return soln.numMatchingSubseq(s, words) == expected;
}

void test_matching_subseq() {
  assert(test_matching("abcde", {"a", "bb", "acd", "ace"}, 3));
  assert(test_matching("aaaxyyzzsas", {"a", "yy", "yzas", "aaa", "sas"}, 5));
}

int main(int argc, char **argv) {
  test_matching_subseq();
  std::cout << argv[0] + 2 << "...OK!" << std::endl;
  return 0;
}
