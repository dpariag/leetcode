// Leetcode: https://leetcode.com/problems/employee-free-time/
// An interval [a,b] represents a busy time for an employee. Given N such lists representing the
// schedules of N employees, find the times when all employees are free.

// Brute Force: Find the free times for each employee, check against all other employees. O(m*N*m)
// Better: Use a heap to track the next working time of each employee. Repeatedly extract the min
// from the heap and determine if a free interval exists between this working interval and the last.

#include <vector>
#include <queue>
#include <iostream>
#include <assert.h>

struct Interval {
  int start;
  int end;
  Interval() : start(0), end(0) {}
  Interval(int s, int e) : start(s), end(e) {}
};
using Intervals = std::vector<Interval>;

struct IntervalIndex {
  Interval interval;
  int32_t row;
  int32_t col;
  IntervalIndex(const Interval& i, int32_t r, int32_t c): interval(i), row(r), col(c) {}
};

struct IntervalGreater {
  bool operator()(const IntervalIndex& i, const IntervalIndex& j) {
    if (i.interval.start == j.interval.start) { return i.interval.end > j.interval.end; }
    return i.interval.start > j.interval.start;
  }
};
using MinHeap = std::priority_queue<IntervalIndex, std::vector<IntervalIndex>, IntervalGreater>;

// Accepted. 32ms. Faster than 99.25% of submissions.
class Solution {
public:
  inline Interval min_interval(MinHeap& min_heap, const std::vector<Intervals>& schedule) {
    auto min = min_heap.top(); 
    min_heap.pop();
    if (min.col + 1 < schedule[min.row].size()) {
      min_heap.emplace(schedule[min.row][min.col+1], min.row, min.col+1);
    }
    return min.interval;
  }

  Intervals employeeFreeTime(const std::vector<Intervals>& schedule) {
    MinHeap min_heap;
    for (int i = 0; i < schedule.size(); ++i) {
      min_heap.emplace(IntervalIndex{schedule[i].front(), i, 0});
    }
  
    Intervals free;
    auto merged = min_interval(min_heap, schedule);
    while (!min_heap.empty()) {
      auto min = min_interval(min_heap, schedule);
      if (min.start <= merged.end) {
        merged.end = std::max(merged.end, min.end);
      } else {
        free.emplace_back(merged.end, min.start);
        merged = min; 
      }
    }
    return free;
  }
};

bool test_free_time(std::vector<Intervals> schedule, Intervals expected) {
  Solution soln;
  auto free_time = soln.employeeFreeTime(schedule);
  if (free_time.size() != expected.size()) {
    return false;
  }
  for (int i = 0; i < expected.size(); ++i) {
    if (free_time[i].start != expected[i].start) { return false; }
    if (free_time[i].end != expected[i].end) { return false; }
  }
  return true;
}

void test_free_time() {
  assert(test_free_time({{{1,2},{5,6}},{{1,3}}, {{4,10}}}, {{3,4}}));
  assert(test_free_time({{{1,3},{6,7}},{{2,4}}, {{2,5},{9,12}}}, {{5,6},{7,9}}));
  assert(test_free_time({{{1,3},{6,7}},{{1,3}},{{2,4}}, {{2,5},{9,12}}}, {{5,6},{7,9}}));
}

int main(int argc, char** argv) {
  test_free_time();
  std::cout << argv[0] + 2 << "...OK!" << std::endl;
  return 0;
}
