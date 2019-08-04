// Leetcode: https://leetcode.com/problems/set-intersection-size-at-least-two/

// Approach: Sort intervals in ascending order by end time. The last two items in each interval are then most
// likely to overlap with the next interval. Scan the array choosing new intervals as needed. O(n*logn) time.
// Acceptance: 35.7

#include <iostream>
#include <vector>
#include <algorithm>
#include <assert.h>

using Range = std::vector<int>;

// Sort intervals by ascending start time. Break ties by 
struct {
  bool operator()(Range& a, Range& b) const {
    if (a.back() == b.back()) { return a.front() > b.front(); }
    return a.back() < b.back();
  }
} RangeEnd;

// Accepted. 40ms. Faster than 67.50% of submissions.
class Solution {
public:
  int intersectionSizeTwo(std::vector<Range>& ranges) {
    std::sort(ranges.begin(), ranges.end(), RangeEnd);  // Sort by right endpoint
    int last = -1, second_last = -1;  // Last two items in a range
    int set_size = 0;

    for (const auto range : ranges) {
      if (last < range.front() && second_last < range.front()) {
        set_size += 2;
        last = range.back();
        second_last = last - 1;
      } else if (second_last < range.front()) {
        second_last = last;
        last = range.back();
        set_size += 1;
      } 
    }
    return set_size;
  }
};

bool test_intersection(std::vector<Range> ranges, int expected) {
  Solution soln;
  return soln.intersectionSizeTwo(ranges) == expected; 
}

void test_intersection() {
  assert(test_intersection({{1,2},{2,3},{2,4},{4,5}}, 5)); // {1,2,3,4,5}
  assert(test_intersection({{1,2},{1,3},{1,4},{1,5}}, 2)); // {1,2}
  assert(test_intersection({{1,3},{1,4},{2,5},{3,5}}, 3)); // {2,3,4}
  assert(test_intersection({{2,6},{4,8},{6,10}}, 3)); // {4,6,7}
  assert(test_intersection({{1,3},{1,4},{2,6},{3,6},{6,7}}, 4)); // {4,6,7}
  assert(test_intersection({{1,5},{3,19},{4,21},{5,9},{8,9}}, 4));
  assert(test_intersection({{0,1},{0,6},{0,10},{1,2},{1,3},{2,5},{4,9},{6,7},{7,9}}, 7));
  assert(test_intersection({{1,3},{4,9},{0,10},{6,7},{1,2},{0,6},{7,9},{0,1},{2,5},{6,8}}, 7)); // {0,1,2,5,6,7,8}
  assert(test_intersection({{2,10},{3,7},{3,15},{4,11},{6,12},{6,16},{7,8},{7,11},{7,15},{11,12}}, 5));//{6,7,8,11,12}
}

int main(int argc, char** argv) {
  test_intersection();
  std::cout << argv[0] + 2 << "...OK!" << std::endl;
  return 0;
}
