// Leetcode: https://leetcode.com/problems/subarray-sums-divisible-by-k/
// Given an integer array A, return the number of (contiguous, non-empty) subarrays that have a sum divisible by K.

// Brute Force: Generate all subarrays, compute each sum and check divisibility by K. O(n^3)
// Better: Store prefix remainders (i.e., running_sum % K) in a hash map. For each running sum,
// determine if there is a prefix subarray that can be subtracted to give a suffix that is divisible by K
// A prefix subarray can be subtracted if it has either a positive or negative sum.
// Acceptance: 37.4

#include <iostream>
#include <vector>
#include <unordered_map>
#include <assert.h>

// Accepted. 56ms. Faster than 94.61% of submissions
class Solution {
public:
  int subarraysDivByK(std::vector<int>& A, int K) {
    // Use a lookup table instead of a hash map. Negative keys are stored first, then positive ones
    // Just a trick to enable faster lookups (compared to a hash map)
    int remainders[20000] = {0};   // Store index i at (i + K) for -K < i < K
    remainders[K] = 1;  // empty array (i.e., remainder = 0)
    int64_t sum = 0, num_subarrays = 0; 
    for (int i = 0; i < A.size(); ++i) {
      sum += A[i];
      auto remainder = sum % K;
      auto smaller = remainder;
      auto bigger = (remainder < 0) ? remainder + K : remainder - K;
      num_subarrays += remainders[smaller + K];  
      num_subarrays += remainders[bigger + K]; 
      remainders[remainder + K]++;
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
