// Leetcode: https://leetcode.com/problems/base-7/
// Convert an integer to base 7. Return the result as a string.

// Approach: Append powers of 7 to the string reprsentation. No leading zeroes, and handle negative values
// Acceptance: 44.5

#include <iostream>
#include <string>
#include <assert.h>

// Accepted. Faster than 100% of cpp submissions.
class Solution {
public:
  std::string convertToBase7(int64_t num) {
    int64_t base = 7, divisor = 1;
    int64_t digits_appended = 0;
    std::string result; 
    if (num < 0) {
      result.append(1, '-');
      num = std::abs(num);
    }
     
    while (divisor < num) divisor = divisor * base;
    while (divisor > 0) {
      auto digit = num / divisor;
      if (digit > 0 || digits_appended > 0 || num == 0) {
        result.append(1, '0' + digit);
        ++digits_appended;
      }
      num = num - (divisor * digit);
      divisor = divisor / base;
    } 
    return result;
  }
};

void test_convert_to_base_7() {
  Solution soln;
  
  assert(soln.convertToBase7(0) == "0");
  assert(soln.convertToBase7(1) == "1");
  assert(soln.convertToBase7(-1) == "-1");
  assert(soln.convertToBase7(6) == "6");
  assert(soln.convertToBase7(7) == "10");
  assert(soln.convertToBase7(77) == "140");
  assert(soln.convertToBase7(100) == "202");
  assert(soln.convertToBase7(-100) == "-202");
}

int main(int argc, char** argv) {
  test_convert_to_base_7();
  std::cout << argv[0] + 2 << "...OK!" << std::endl;
  return 0;
}
