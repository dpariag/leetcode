// Leetcode: https://leetcode.com/problems/path-with-maximum-minimum-value/
// Given an integer matrix A with R rows and C columns, find the maximum score of a path starting at [0,0] 
// and ending at [R-1,C-1]. The score of a path is the minimum value in that path.
// For example, the value of the path 8 → 4 → 5 → 9 is 4.
// A path moves from one visited cell to any neighbouring unvisited cell (north, east, west, south).

// Brute Force: Generate all paths from [0,0] [R-1,C-1] and track the score of each path. Exponential time.
// Better: Use Dijkstra's algorithm to track the min path so far, and expand the min cost path so far
// Acceptance: 46.5

#include <iostream>
#include <queue>
#include <vector>
#include <assert.h>

struct Entry {
  int row = -1;
  int col = -1;
  int weight = -1;
  bool operator<(const Entry& other) const {
    return weight < other.weight;
  }
};

using MaxHeap = std::priority_queue<Entry, std::vector<Entry>>;

// Accepted. 224ms. Faster than 94.40% of C++ submissions.
class Solution {
public:
  int maximumMinimumPath(std::vector<std::vector<int>>& A) {
    MaxHeap max_heap;
    max_heap.emplace(Entry{0,0,A[0][0]});
    A[0][0] *= -1;
    auto dest_row = A.size() - 1, dest_col = A[0].size() - 1;
    while (!max_heap.empty()) {
      auto entry = max_heap.top();
      max_heap.pop();
      if (entry.row == dest_row && entry.col == dest_col) {
        // Arrived
        return entry.weight;
      } 
      if (entry.row > 0 && A[entry.row-1][entry.col] > 0) {
        // Above
        max_heap.emplace(Entry{entry.row - 1, entry.col, std::min(A[entry.row-1][entry.col], entry.weight)});
        A[entry.row-1][entry.col] *= -1;
      }
      if (entry.col > 0 && A[entry.row][entry.col-1] > 0) {
        // Left
        max_heap.emplace(Entry{entry.row, entry.col-1, std::min(A[entry.row][entry.col-1], entry.weight)});
        A[entry.row][entry.col-1] *= -1;
      }
      if (entry.row < dest_row && A[entry.row+1][entry.col] > 0)  {
        // Below
        max_heap.emplace(Entry{entry.row+1, entry.col, std::min(A[entry.row+1][entry.col], entry.weight)});
        A[entry.row+1][entry.col] *= -1;
      }
      if (entry.col < dest_col && A[entry.row][entry.col+1] > 0) {
        // Right
        max_heap.emplace(Entry{entry.row, entry.col+1, std::min(A[entry.row][entry.col+1], entry.weight)});
        A[entry.row][entry.col+1] *= -1;
      }
    }
    return 0;       
  }
};

bool test_max_min_path(std::vector<std::vector<int>> matrix, int expected) {
  Solution soln;
  return soln.maximumMinimumPath(matrix) == expected;
}

void test_max_min_path() {
  assert(test_max_min_path({{5,4,5},{1,2,6},{7,4,6}}, 4));
  assert(test_max_min_path({{7,4,4},{6,0,4},{3,1,7}}, 4));
  assert(test_max_min_path({{2,2,1,2,2,2},{1,2,2,2,1,2}}, 2));
  assert(test_max_min_path({{3,4,6,3,4},{0,2,1,1,7},{8,8,3,2,7},{3,2,4,9,8},{4,1,2,0,0},{4,6,5,4,3}},3));
}

int main(int argc, char** argv) {
  test_max_min_path();
  std::cout << argv[0] + 2 << "...OK!" << std::endl;
  return 0;
}
