// Leetcode: https://leetcode.com/problems/permutation-in-string/description/ 
//

// Brute Force:
// Better:

#include <vector>
#include <iostream>
#include <assert.h>

struct StringCover {

  StringCover(const std::string& s) {
    for (auto ch : s) {
      need[ch-'a']++;
    }
  }

  inline void clear() {
    for (int i = 0; i < 26; ++i) {
      have[i] = 0;
    }
    count = 0;
  }

  int count = 0;      // how many chars we have 
  int need[26] = {0}; // how many of each char we need 
  int have[26] = {0}; // how many of each char we have 
};

// Accepted. 8ms. Beats 71.46% of submissions.
class Solution {
public:
  bool checkInclusion(std::string& s1, std::string& s2) {
    StringCover cover(s1);
    int left = 0, right = 0;
    while (right < s2.size()) {
      auto idx = s2[right] - 'a';

      if (cover.need[idx] == 0) {
        // Mismatch! Don't need this letter
        cover.clear();
        ++right, left = right;
        continue;
      } else if (cover.have[idx] == cover.need[idx]) {
        // Shrink the window until no longer covered
        while (left < right && cover.have[idx] == cover.need[idx]) {
          cover.have[s2[left] - 'a']--;
          ++left, --cover.count;
        }
      } 
      cover.have[idx]++;
      ++cover.count;
      if (cover.count == s1.size()) { return true; }
      ++right;
    }
    return false;
  }
};

bool test_inclusion(std::string s1, std::string s2, bool expected) {
  Solution soln;
  return soln.checkInclusion(s1, s2) == expected;
}

void test_inclusion() {
  assert(test_inclusion("row", "helloworld", true));
  assert(test_inclusion("row", "wotowxrwo", true));
  assert(test_inclusion("row", "roroowr", true));
  assert(test_inclusion("row", "roroowx", false));
}

int main(int argc, char** argv) {
  test_inclusion();
  std::cout << argv[0] + 2 << "...OK!" << std::endl;
  return 0;
}
