// Leetcode: https://leetcode.com/problems/string-without-aaa-or-bbb/

// Approach: Calculate (A-B) and append characters in the pattern 'aab' (A > B) or 'bba' (B > A).
// It may not be possible to append the entire 3-char sequence if there are not enough chars remaining.
// Acceptance: 34.6%

#include <iostream>
#include <assert.h>

// Accepted. 0ms. Faster than 100% of cpp submissions.
class Solution {
public:
  std::string build_string(int longer, char longer_char, int shorter, char shorter_char) {
    std::string result;
    int difference;
    while (longer > 0) {
      difference = longer - shorter;
      if (difference > 0) {
        if (longer) result.push_back(longer_char), --longer;
        if (longer) result.push_back(longer_char), --longer;
        if (shorter) result.push_back(shorter_char), --shorter;
      } else {
        if (longer) result.push_back(longer_char), --longer;
        if (shorter) result.push_back(shorter_char), --shorter;
      }
    }
    return result;
  }

  std::string strWithout3a3b(int A, int B) {
    if (A >= B) {
      return build_string(A, 'a', B, 'b');
    }
    return build_string(B, 'b', A, 'a');
  }
};

int char_count(std::string str, char c) {
  int count = 0;
  for (auto ch : str) {
    if (ch == c) ++count;
  }
  return count;
}

bool test_string(int A, int B) {
  Solution soln;
  auto str = soln.strWithout3a3b(A, B); 
  return str.size() == (A+B) && char_count(str, 'a') == A && char_count(str, 'b') == B;
}


void test_string_building() {
  assert(test_string(1,1)); 
  assert(test_string(2,1)); 
  assert(test_string(3,1)); 
  assert(test_string(1,2)); 
  assert(test_string(1,3)); 
  assert(test_string(10,4)); 
  assert(test_string(10,5)); 
  assert(test_string(10,6)); 
}

int main(int argc, char** argv) {
  test_string_building();
  std::cout << argv[0] + 2 << "...OK!" << std::endl;
  return 0;
}
