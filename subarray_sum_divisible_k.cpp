// Leetcode: https://leetcode.com/problems/subarray-sums-divisible-by-k/
// Given an integer array A, return the number of (contiguous, non-empty) subarrays that have a sum divisible by K.

// Brute Force: Generate all subarrays, compute each sum and check divisibility by K. O(n^3)
// Better:
// Acceptance: 

#include <iostream>
#include <vector>
#include <unordered_map>
#include <assert.h>

using SumMap = std::unordered_map<int64_t, int64_t>;  // sum to number of occurences

// Accepted. 76ms. Faster than 36.75% of submissions
class Solution {
public:
  int subarraysDivByK(std::vector<int>& A, int K) {
    SumMap prefix_sums(A.size()* 2);
    prefix_sums[0] = 1;  // empty array
    int64_t sum = 0, num_subarrays = 0; 
    for (int i = 0; i < A.size(); ++i) {
      sum += A[i];
      auto remainder = sum % K;
      auto smaller = remainder;
      auto bigger = (remainder < 0) ? remainder + K : remainder - K;
       
      auto found = prefix_sums.find(smaller);
      if (found != prefix_sums.end()) num_subarrays += found->second;
      found = prefix_sums.find(bigger);
      if (found != prefix_sums.end()) num_subarrays += found->second;
      prefix_sums[remainder]++;
    }
    return num_subarrays;
  }
};

bool test_subarrays_div_k(std::vector<int> A, int K, int expected) {
  Solution soln;
  return soln.subarraysDivByK(A, K) == expected;
}

void test_subarrays_div_k() {
  assert(test_subarrays_div_k({7,-5,5,-8,-6,6,-4,7,-8,-7}, 7, 11));
  assert(test_subarrays_div_k({2,-2,2,-4}, 6, 2));
  assert(test_subarrays_div_k({-1,2,9}, 2, 2));
  assert(test_subarrays_div_k({4,5,0,-2,-3,1}, 5, 7));
  assert(test_subarrays_div_k({4,5,0,1,-2,-3}, 5, 6));
  assert(test_subarrays_div_k({2,2,2,2,5}, 5, 1));
}

int main(int argc, char** argv) {
  test_subarrays_div_k();
  std::cout << argv[0] + 2 << "...OK!" << std::endl;
  return 0;
}
