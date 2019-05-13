// Leetcode: https://leetcode.com/problems/binary-subarrays-with-sum/
// In an array A of 0s and 1s, how many non-empty subarrays have sum S?

// Brute Force:
// Better:
// Acceptance: 37.5

#include <iostream>
#include <vector>
#include <assert.h>

// Accepted. Faster than 99.06% of cpp submissions.
class Solution {
public:
  int numSubarraysWithSum(const std::vector<int>& A, int target_sum) {
    int left = 0, right = 0, leading_zeroes= 0, num_ones = 0;
    int count = 0, sum = 0;
    while (right < A.size()) {
      sum += A[right];
      num_ones += (A[right] == 1 ?  1 : 0);

      if (sum == target_sum) {
        count += (leading_zeroes + 1); 
        if (target_sum == 0 && A[right] == 0 && num_ones == 0) ++leading_zeroes;
      } else if (sum < target_sum) {
        leading_zeroes += (num_ones == 0 && A[right] == 0 ? 1 : 0);
      } else {
        // sum > target_sum
        while (sum > target_sum) {
          sum -= A[left];
          if (A[left] == 1) --num_ones;
          ++left;
        }

        leading_zeroes = 0;
        int pos = left;
        while (pos < right && A[pos] == 0) {
          ++leading_zeroes, ++pos;
        }
        if (sum > 0) count += (leading_zeroes + 1);
      }
      // 0001 1100100
      ++right;
    } // while
    return count;
  }
};

void test_num_subarrays() {
  Solution soln;
  assert(soln.numSubarraysWithSum({0,0,0,0,0}, 0) == 15);
  assert(soln.numSubarraysWithSum({0,0,0,1,1,1,0,0}, 3) == 12);
  assert(soln.numSubarraysWithSum({1,0,1,0,1}, 2) == 4);
  assert(soln.numSubarraysWithSum({1,0,1}, 2) == 1);
  assert(soln.numSubarraysWithSum({1,0,0}, 0) == 3);
}

int main(int argc, char** argv) {
  test_num_subarrays();
  std::cout << argv[0] + 2 << "...OK!" << std::endl;
  return 0;
}
