// Leetcode: https://leetcode.com/problems/set-mismatch/

// Brute Force:
// Better:
// Acceptance: 

#include <iostream>
#include <vector>
#include <assert.h>

// Accepted. 36ms. Faster than 87.16% of C++ submissions.
class Solution {
public:
  std::vector<int> findErrorNums(std::vector<int>& nums) {
    int i = 0;
    int duplicate = 0, missing = 0;
    while (i < nums.size()) {
      while (nums[i] != i+1) {
        if (nums[nums[i]-1] == nums[i]) {
          break;
        }
        std::swap(nums[i], nums[nums[i]-1]); 
      } 
      ++i;
    }

    for (i = 0; i < nums.size(); ++i) {
      if (nums[i] != i+1) {
        missing = i+1;
        duplicate = nums[i];
      }
    }
    return {duplicate, missing};
  }
};

bool test_find_errors(std::vector<int> nums, std::vector<int> expected) {
  Solution soln;
  return soln.findErrorNums(nums) == expected;
}

void test_find_errors() {
  assert(test_find_errors({1,1}, {1,2}));
  assert(test_find_errors({2,2}, {2,1}));
  assert(test_find_errors({1,2,2,4}, {2,3}));
  assert(test_find_errors({1,2,3,4,5,1}, {1,6}));
  assert(test_find_errors({6,2,3,4,5,6}, {6,1}));
}

int main(int argc, char** argv) {
  test_find_errors();
  std::cout << argv[0] + 2 << "...OK!" << std::endl;
  return 0;
}
