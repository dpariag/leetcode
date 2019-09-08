// Leetcode: https://leetcode.com/problems/implement-rand10-using-rand7/submissions/
// Given rand7() which returns a number over [1,7], write rand10 which will 
// return a random number over [1,10]

// Approach: Use rand7 to generate the digits of a base 7 number, and convert it
// to base10 as we go. Return the generated number modulo 10 + 1
// Acceptance: 

#include <iostream>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

int rand7() {
  return 1 + (rand() % 7);
}

// 68ms. Faster than 94.20% of cpp submissions.
class Solution {
public:
    int rand10() {
      int base10_number = 0;
      int pow7 = 1;
      for (int i = 0; i < 4; ++i) {
        auto digit = rand7() - 1;
        base10_number += digit * pow7;
        pow7 = pow7 * 7;
      }
      return 1 + (base10_number % 10);
    }
};


int main(int argc, char** argv) {
  srand(time(nullptr));
  std::cout << argv[0] + 2 << "...OK!" << std::endl;
  return 0;
}
