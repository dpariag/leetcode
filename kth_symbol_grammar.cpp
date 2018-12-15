// Leetcode: https://leetcode.com/problems/k-th-symbol-in-grammar/
// row 1: 0
// row 2: 01
// row 3: 0110
// row 4: 01101001

// Brute Force: Generate the N'th string, then return the byte at offset K. Exponential time/space
// Better: Determine if K lies in the right/left half of the string. Repeatedly divide the string in half,
// each time mapping K to it's offset in the left half. Flip if K was in the right half.
// Acceptance: 37.6

#include <iostream>
#include <assert.h>

// Accepted. 0ms. Faster than 100% of cpp submissions.
class Solution {
public:
  int kthGrammar(int N, int K) {
    if (N == 1) { return 0; }
    bool flip = false;
    while (N > 2) {
      auto length = (1 << (N-1));
      auto middle = length / 2;
      if (K > middle) {
        flip = !flip;
        K -= middle;
      }
      --N;
    }
    auto result = (K == 1) ? 0 : 1;
    return flip ? (result + 1) % 2 : result;
  }
};

bool test_grammar(int N, int K, int expected) {
  Solution soln;
  return soln.kthGrammar(N, K) == expected;
}

void test_grammar() {
  assert(test_grammar(3,4,0));   // 0110
  assert(test_grammar(1,1,0));   // 0
  assert(test_grammar(2,1,0));   // 01
  assert(test_grammar(2,2,1));   // 01
  assert(test_grammar(3,1,0));   // 0110
  assert(test_grammar(3,2,1));   // 0110
  assert(test_grammar(3,3,1));   // 0110
  assert(test_grammar(4,7,0));   // 01101001
  assert(test_grammar(5,3,1));   // 0110100110010110
  assert(test_grammar(5,5,1));   // 0110100110010110
  assert(test_grammar(5,6,0));   // 0110100110010110
  assert(test_grammar(5,10,0));  // 0110100110010110
  assert(test_grammar(5,16,0));  // 0110100110010110
}

int main(int argc, char** argv) {
  test_grammar();
  std::cout << argv[0] + 2 << "...OK!" << std::endl;
  return 0;
}
