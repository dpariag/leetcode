// Leetcode: https://leetcode.com/problems/maximum-distance-in-arrays/

// Approach: Scan sorted arrays looking for min and max. 
// Acceptance: 

#include <vector>
#include <iostream>
#include <assert.h>

// Accepted. 20ms. Faster than 99.11% of C++ submissions
class Solution {
public:
  int maxDistance(std::vector<std::vector<int>>& arrays) {
    int min_index{0}, min{arrays[0].front()};
    int max_index{0}, max{arrays[0].back()};
    int max_distance = 0;

    // Scan the arrays to find the min and max
    for (int i = 1; i < arrays.size(); ++i) {
      if (i != min_index) {
        max_distance = std::max(max_distance, (arrays[i].back() - min));
      }
      if (arrays[i].front() < min) {
        min = arrays[i].front(), min_index = i;
      }
      
      if (i != max_index) {
        max_distance = std::max(max_distance, (max - arrays[i].front()));
      }
      if (arrays[i].back() > max) {
        max = arrays[i].back(), max_index = i;
      }
    }
    return max_distance;
  }
};

bool test_max_distance(std::vector<std::vector<int>> arrays, int expected) {
  Solution soln;
  return soln.maxDistance(arrays) == expected;
}

void test_max_distance() {
  assert(test_max_distance({{1,4}, {0,5}}, 4));
  assert(test_max_distance({{2,2,3,10}, {5,6,15}, {1,2,2,2}}, 14));
  assert(test_max_distance({{2,2,3,10}, {5,6,15}, {2,2,2,2}}, 13));
  assert(test_max_distance({{2,2,3,10}, {1,6,15}, {2,2,2,2}}, 13));
  assert(test_max_distance({{2,2,3,10}, {1,6,7,8}, {2,2,2,2}}, 9));
}

int main(int argc, char** argv) {
  test_max_distance();
  std::cout << argv[0] + 2 << "...OK!" << std::endl;
  return 0;
}
