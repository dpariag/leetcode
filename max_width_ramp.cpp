// Leetcode: https://leetcode.com/problems/maximum-width-ramp/
// Given an integer array, a ramp is a tuple (i,j) for which i < j and A[i] <= A[j]. 
// The width of such a ramp is j - i. Find the maximum width ramp in A. Return 0 if none exists

// Brute Force: For every A[i], scan forwards looking for the longest ramp. O(n^2) time.
// Better: Sort the entries, saving original index in A. Scan sorted array tracking min index and ramp. O(n) time.
// Acceptance: 37.8

#include <iostream>
#include <vector>
#include <assert.h>

struct Entry {
  int index;
  int value;
  Entry(int i, int v): index(i), value(v) {}
  bool operator<(const Entry& other) const {
    if (value == other.value) return index < other.index;
    return value < other.value;
  }
};

// Accepted. 60ms. Faster than 80.84% of cpp submissions.
class Solution {
public:
  int maxWidthRamp(const std::vector<int>& A) {
    std::vector<Entry> entries;
    entries.reserve(A.size());

    for (int i = 0; i < A.size(); ++i) {
      entries.emplace_back(i, A[i]);
    }

    std::sort(entries.begin(), entries.end()); 
    int min_index = entries.size();
    int max_ramp = 0;
    for (int i = 0; i < entries.size(); ++i) {
      min_index = std::min(min_index, entries[i].index);
      if (min_index < entries[i].index) {
        max_ramp = std::max(max_ramp, entries[i].index - min_index);
      }
    }
    return max_ramp;
  }
};

void test_max_ramp() {
  Solution soln;
  assert(soln.maxWidthRamp({6,0,8,2,9}) == 4);
  assert(soln.maxWidthRamp({5,4,3,2,1}) == 0);
  assert(soln.maxWidthRamp({3,4,0,0,1}) == 2);
  assert(soln.maxWidthRamp({3,4,0,0,1,5}) == 5);
  assert(soln.maxWidthRamp({0,1,2,3,4,5}) == 5);
  assert(soln.maxWidthRamp({6,0,8,2,1,5}) == 4);
  assert(soln.maxWidthRamp({9,8,1,0,1,9,4,0,4,1}) == 7);
}

int main(int argc, char** argv) {
  test_max_ramp();
  std::cout << argv[0] + 2 << "...OK!" << std::endl;
  return 0;
}
