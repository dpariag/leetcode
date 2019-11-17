// Leetcode:

// Brute Force:
// Better:
// Acceptance: 

#include <iostream>
#include <vector>
#include <assert.h>

class Solution {
public:
  inline int left_edge(const std::vector<int>& rec) { return rec[0]; }
  inline int right_edge(const std::vector<int>& rec) { return rec[2]; }
  inline int top_edge(const std::vector<int>& rec) { return rec[3]; }
  inline int bottom_edge(const std::vector<int>& rec) { return rec[1]; }

  bool has_vertical_overlap(const std::vector<int>& rec1, const std::vector<int>& rec2) {
    return 
      (left_edge(rec1) > left_edge(rec2) && left_edge(rec1) < right_edge(rec2)) ||
      (right_edge(rec1) > left_edge(rec2) && right_edge(rec1) < right_edge(rec2));
  }  

  bool has_horizontal_overlap(const std::vector<int>& rec1, const std::vector<int>& rec2) {
    return
      (top_edge(rec1) < top_edge(rec2) && top_edge(rec1) > bottom_edge(rec2)) ||
      (bottom_edge(rec1) < top_edge(rec2) && bottom_edge(rec1) > bottom_edge(rec2));
  }

  bool isRectangleOverlap(const std::vector<int>& rec1, const std::vector<int>& rec2) {
    return 
      (has_vertical_overlap(rec1, rec2) && has_horizontal_overlap(rec1, rec2)) ||
      (has_vertical_overlap(rec2, rec1) && has_horizontal_overlap(rec2, rec1));
  }
};

void test_is_rectangle_overlap() {
  Solution soln;
  assert(soln.isRectangleOverlap({0,0,2,2}, {1,1,3,3}) == true);
  assert(soln.isRectangleOverlap({0,0,1,1}, {1,0,2,1}) == true);
}

int main(int argc, char** argv) {
  test_is_rectangle_overlap(); 
  std::cout << argv[0] + 2 << "...OK!" << std::endl;
  return 0;
}
