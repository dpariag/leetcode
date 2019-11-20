// Leetcode: https://leetcode.com/problems/rectangle-overlap/
// A rectangle is represented as [x1, y1, x2, y2], where (x1, y1) is its bottom-left corner, 
// and (x2, y2) is its top-right corner.
// Given two (axis-aligned) rectangles, return whether they overlap.

// Approach: Calculate the overlap by looking at rightmost left edge, leftmost right edge, 
// lowest top edge and highest bottom edge.
// Acceptance: 47.8

#include <iostream>
#include <vector>
#include <assert.h>

// Accepted. Runtime 0ms. Beats 100% of submissions.
class Solution {
public:
  inline int left_edge(const std::vector<int>& rec) { return rec[0]; }
  inline int right_edge(const std::vector<int>& rec) { return rec[2]; }
  inline int top_edge(const std::vector<int>& rec) { return rec[3]; }
  inline int bottom_edge(const std::vector<int>& rec) { return rec[1]; }
      
  bool isRectangleOverlap(const std::vector<int>& rec1, const std::vector<int>& rec2) {
    auto left = std::max(left_edge(rec1), left_edge(rec2));
    auto right = std::min(right_edge(rec1), right_edge(rec2));
    auto top = std::min(top_edge(rec1), top_edge(rec2));
    auto bottom = std::max(bottom_edge(rec1), bottom_edge(rec2));
    return (right - left) > 0 && (top - bottom) > 0;
  }
};

void test_is_rectangle_overlap() {
  Solution soln;
  assert(soln.isRectangleOverlap({0,0,1,1}, {1,0,2,1}) == false);
  assert(soln.isRectangleOverlap({0,0,2,2}, {1,1,3,3}) == true);
}

int main(int argc, char** argv) {
  test_is_rectangle_overlap(); 
  std::cout << argv[0] + 2 << "...OK!" << std::endl;
  return 0;
}
