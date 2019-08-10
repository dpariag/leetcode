// Leetcode: https://leetcode.com/problems/maximize-distance-to-closest-person/

// Approach: Scan the array looking for a block of zeroes. There are two cases:
// 1) The block is anchored at one end of the array
// 2) The block is surrounded by ones.
// The distance to the closest person is different in each case, so that distance
// must be calculated for each block and the max tracked. O(n) time, O(1) space.
// Acceptance: 41.3%

#include <vector>
#include <iostream>
#include <assert.h>

// Accepted. 8ms, faster than 98.59% of C++ submissions
class Solution {
public:
  int maxDistToClosest(const std::vector<int>& seats) {
    int start = -1, end = -1;
    int max_distance = 0;

    for (int i = 0; i < seats.size(); ++i) {
      const auto seat = seats[i];
      if (seat == 0) {
        if (start == -1) {
          start = i, end = i-1; // end is incremented below
        }
        ++end;
      } else if (seat == 1) {
        start = -1, end = -1; 
      } 
      
      auto distance = 0;
      if (start == 0 || end == seats.size() - 1) {
        distance = (end - start) + 1;
      } else {
        distance = (end - start + 2) / 2;
      }
      max_distance = std::max(max_distance, distance);
    } //for

    return max_distance;
  }
};

void test_max_distance() {
  Solution soln;

  assert(soln.maxDistToClosest({1,0,0,0}) == 3); 
  assert(soln.maxDistToClosest({1,0,0,0,1,0,1}) == 2); 
  assert(soln.maxDistToClosest({0,0,0,1}) == 3); 
  assert(soln.maxDistToClosest({0,0,0,1,0,0,0,0}) == 4); 
  assert(soln.maxDistToClosest({0,0,0,1,0,0,0,1}) == 3); 
  assert(soln.maxDistToClosest({1,1,0,1}) == 1); 
  assert(soln.maxDistToClosest({0,1,1,1,0,0,1,0,0}) == 2); 
  assert(soln.maxDistToClosest({0,0,0,1,0,0,0,1,0,0,0,0,1,1,0,0,0,1}) == 3); 
}


int main(int argc, char** argv) {
  test_max_distance();
  std::cout << argv[0] + 2 << "...OK!" << std::endl;
  return 0;
}
