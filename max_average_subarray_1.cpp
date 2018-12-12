// Leetcode: https://leetcode.com/problems/maximum-average-subarray-i/

// Approach: Use a sliding window of size K to sweep the array. Track the max average.
// Acceptance: 38.3

#include <iostream>
#include <vector>
#include <assert.h>

// Accepted. 112ms. Faster than 93.25% of cpp submissions.
class Solution {
public:
  double findMaxAverage(std::vector<int>& nums, int k) {
    double sum = 0.0, avg = 0.0, max_avg = std::numeric_limits<double>::max() * -1;
    for (int i = 0; i < nums.size(); ++i) {
      sum += double(nums[i]); 
      if (i >= k-1) {
        auto left = i - k;
        if (left >= 0) {
          sum -= nums[left];
        }
        avg = sum / double(k);
        max_avg = std::max(avg, max_avg); 
      }
    }    
    return max_avg;
  }
};

bool test_max_average(std::vector<int> nums, int k, double expected) {
  Solution soln;
  return soln.findMaxAverage(nums, k) == expected;
}

void test_max_average() {
  assert(test_max_average({-1}, 1, -1.0));
  assert(test_max_average({1,12,-5,-6}, 4, 0.5));
  assert(test_max_average({1,12,-5,-6,50,3}, 4, 12.75));
}

int main(int argc, char** argv) {
  test_max_average();
  std::cout << argv[0] + 2 << "...OK!" << std::endl;
  return 0;
}
