// Leetcode: https://leetcode.com/problems/shifting-letters/
// Given a string S and integer array shifts[i], for every shifts[i] = X, we want to shift the first i+1 letters of
// S by X (with wrapping). A letter shift is an increment (with wrapping). For example, shift('a', 2) = 'c'

// Brute Force: For every shift[i], apply the shift to the first i+1 letters of S. O(n^2) time.
// Better: Preprocess the shifts array to calculate the final shift of each letter. O(n) time.
// Acceptance: 37.3 

#include <iostream>
#include <vector>
#include <string>
#include <assert.h>

// Accepted. 36ms. Beats 97.68% of accepted submissions.
class Solution {
public:
    std::string shiftingLetters(const std::string& s, std::vector<int>& shifts) {
      std::string shifted = s;
      for (int i = shifts.size() - 2; i >= 0; --i) {
        shifts[i] = (shifts[i] + shifts[i+1]) % 26;
      }
    
      for (int i = 0; i < s.size(); ++i) {
        auto shift = shifts[i];
        shifted[i] = 'a' + ((int(s[i] - 'a') + shift) % 26); 
      }
      return shifted;   
    }
};

bool test_shifting_letters(std::string s, std::vector<int> shifts, std::string expected) {
  Solution soln;
  return soln.shiftingLetters(s, shifts) == expected;
}

void test_shifting_letters() {
  assert(test_shifting_letters("ruu", {26,9,17}, "rul"));
  assert(test_shifting_letters("a", {26}, "a"));
  assert(test_shifting_letters("abc", {0,0,0}, "abc"));
  assert(test_shifting_letters("abc", {1,0,0}, "bbc"));
  assert(test_shifting_letters("abc", {1,0,1}, "ccd"));
  assert(test_shifting_letters("abc", {1,0,2}, "dde"));
  assert(test_shifting_letters("abc", {3,5,9}, "rpl"));
}

int main(int argc, char** argv) {
  test_shifting_letters();
  std::cout << argv[0] + 2 << "...OK!" << std::endl;
  return 0;
}
