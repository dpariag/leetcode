// Leetcode: https://leetcode.com/problems/orderly-queue/

// Brute Force: Recursively generate permutations, tracking the lexicographically smallest one.
// Better:
// Acceptance: 45.0 

#include <iostream>
#include <assert.h>

// Accepted. 4ms. Faster than 100% of cpp submissions
class Solution {
public:
  std::string orderlyQueue(std::string& s, int k) {
    if (k == 1) {
      std::string min = s;
      for (int i = 0; i < s.size(); ++i) {
        // Perform n rotations
        auto ch = s.back();
        for (int j = s.size()-1; j > 0; --j) {
          s[j] = s[j-1];
        }
        s.front() = ch;
        if (s < min) {
          min = s;
        }
      }
      return min;
    } 
    std::sort(s.begin(), s.end());;
    return s;
  }
};

bool test_orderly_queue(std::string s, int k, std::string expected_min) {
  Solution soln;
  return soln.orderlyQueue(s,k) == expected_min;
}

void test_orderly_queue() {
  assert(test_orderly_queue("a", 1, "a"));
  assert(test_orderly_queue("a", 2, "a"));
  assert(test_orderly_queue("cba", 1, "acb"));
  assert(test_orderly_queue("cba", 2, "abc"));
  assert(test_orderly_queue("baaca", 1, "aacab"));
  assert(test_orderly_queue("baaca", 3, "aaabc"));
  assert(test_orderly_queue("axybz", 1, "axybz"));
  assert(test_orderly_queue("axybz", 2, "abxyz"));
}

int main(int argc, char** argv) {
  test_orderly_queue();
  std::cout << argv[0] + 2 << "...OK!" << std::endl;
  return 0;
}
