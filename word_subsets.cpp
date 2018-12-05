// Leetcode: https://leetcode.com/problems/word-subsets/
// Given two arrays of words A and B, return all the 'universal' words in A.
// A word is 'universal' if its letters can be used to construct every word in B.

// Brute Force: For every word in A, check if it can construct every word in B. O(m*n) time.
// Better: Track the max number of each lettter required across all words in B. Check each word in A against the
// max letter counts. O(m + n) time
// Acceptance: 43.3

#include <string>
#include <vector>
#include <iostream>
#include <assert.h>

const int ALPHABET_SIZE = 26;
using Words = std::vector<std::string>;
using CharCounts = std::vector<int>;

// Accepted. 112ms. Faster than 77.70% of cpp submissions.
class Solution {
public:
  inline CharCounts count(const std::string& word) {
    CharCounts counts(ALPHABET_SIZE, 0);
    for (auto ch : word) { counts[ch-'a']++; }
    return counts;
  } 

  inline void merge(CharCounts& dst, const CharCounts& src) {
    for (int i = 0; i < dst.size(); ++i) {
      dst[i] = std::max(dst[i], src[i]);
    }
  }

  // Return true iff 'a' contains 'b'
  inline bool contains(const CharCounts& a, const CharCounts& b) {
    for (int i = 0; i < a.size(); ++i) {
      if (a[i] < b[i]) { return false; }
    }
    return true;
  }  

  Words wordSubsets(const Words& A, const Words& B) {
    Words universal;
    CharCounts max_counts(ALPHABET_SIZE, 0);
    for (const auto& word : B) {
      auto counts = count(word);
      merge(max_counts, counts);
    }    

    for (const auto& word: A) {
      auto word_counts = count(word);
      if (contains(word_counts, max_counts)) {
        universal.emplace_back(word);
      }
    }
    return universal;
  }
};

bool test_word_subsets(Words A, Words B, Words expected) {
  Solution soln;
  auto universal = soln.wordSubsets(A, B);
  std::sort(universal.begin(), universal.end());
  std::sort(expected.begin(), expected.end());
  return universal == expected;
}


void test_word_subsets() {
  assert(test_word_subsets(
    {"amazon", "apple", "google", "facebook", "leetcode"}, 
    {"e", "o"}, 
    {"google", "facebook", "leetcode"}));
  assert(test_word_subsets(
    {"amazon", "apple", "google", "facebook", "leetcode"}, 
    {"e", "oo"}, 
    {"google", "facebook"}));
  assert(test_word_subsets(
    {"amazon", "apple", "google", "facebook", "leetface"}, 
    {"book", "face"}, 
    {"facebook"}));
  assert(test_word_subsets(
    {"aaa", "aabb", "aaccbb", "bbcc", "zzaaccbb"}, 
    {"a", "aa", "bb"},
    {"aabb", "aaccbb", "zzaaccbb"}));
}

int main(int argc, char** argv) {
  test_word_subsets();
  std::cout << argv[0] + 2 << "...OK!" << std::endl;
  return 0;
}
