// Leetcode: https://leetcode.com/problems/smallest-subsequence-of-distinct-characters/
// Return the lexicographically smallest subsequence of text that contains all the distinct 
// characters of text exactly once.

// Brute Force: Generate all subsequences, filter those with all chars once, return smallest. O(2^n) time
// Better: Use a stack to build the lexicographically smallest. Pop if stack.top < next_char and next_char
// exists later in the input string. Push next_char if it doesn't already exist in the stack
// Acceptance: 

#include <array>
#include <iostream>
#include <assert.h>

// Accepted. 0ms. Faster than 100% of submissions.
class Solution {
public:
    std::string smallestSubsequence(const std::string& text) {
      const int cNumChars = 26;
      int counts[cNumChars] = {0};

      // Count each character
      for (auto ch : text) {
        ++counts[ch-'a'];
      }
      
      bool used[cNumChars] = {false};
      std::string result;
      for (int i = 0; i < text.size(); ++i) {
        auto ch = text[i];
        --counts[ch-'a'];
        if (used[ch-'a'] > 0) continue;
        while (!result.empty()) {
          auto last = result.back(); 
          if (ch < last && counts[last-'a'] > 0) {
            result.pop_back();
            used[last-'a'] = false;
          } else {
            break;
          }
        } // while
        result.push_back(ch);
        used[ch-'a'] = true;
      }
      return result;
    }
};

bool test_smallest_subseq(std::string text, std::string expected) {
  Solution soln;
  return soln.smallestSubsequence(text) == expected;
}

void test_smallest_subseq() {
  assert(test_smallest_subseq("dbbbabadcdcbdaddddbbcbdaaadbdaadcaaabbab", "abcd"));
  assert(test_smallest_subseq("cbaacabcaaccaacababa", "abc"));
  assert(test_smallest_subseq("xaydeedax", "aydex"));
  assert(test_smallest_subseq("leetcode", "letcod"));
  assert(test_smallest_subseq("bcbcbcababa", "bca"));
  assert(test_smallest_subseq("ecbacba", "eacb"));
  assert(test_smallest_subseq("cdadabcc", "adbc"));
  assert(test_smallest_subseq("abcd", "abcd"));
}

int main(int argc, char** argv) {
  test_smallest_subseq();
  std::cout << argv[0] + 2 << "...OK!" << std::endl;
  return 0;
}
