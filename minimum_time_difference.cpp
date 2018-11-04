// Leetcode: https://leetcode.com/problems/minimum-time-difference/ 
// Given a list of timestamps, find the minimum number of minutes between any two timestamps.

// Brute Force: Generate all pairs of timestamps, track min difference. O(n^2)
// Better: Place timestamps on a 1440 minute timeline. Scan timeline for min difference. O(n) time

#include <vector>
#include <iostream>
#include <assert.h>

// Accepted. 8ms. Faster than 100% of submissions.
class Solution {
public:
  inline int to_minutes(const std::string& ts) {
    int mins = 0;
    mins += (ts[0] - '0') * 10 * 60;
    mins += (ts[1] - '0') * 60;
    mins += (ts[3] - '0') * 10;
    mins += (ts[4] - '0');
    return mins;
  }

  int findMinDifference(const std::vector<std::string>& timestamps) {
    const int mins_per_day = 24 * 60;
    std::vector<int> day(mins_per_day, 0);

    for (const auto& ts : timestamps) {
      day[to_minutes(ts)]+=1;
    }
    
    int min_gap = mins_per_day, first = -1, prev = -1;
    for (int i = 0; i < mins_per_day; ++i) {
      if (day[i] != 0) {
        if (day[i] > 1) { return 0; } // special case!
        if (prev != -1) {
          min_gap = std::min(min_gap, i - prev);
        }
        if (first == -1) { first = i; }
        prev = i;
      }
    }
    min_gap = std::min(min_gap, first + (mins_per_day - prev));
    std::cout << "min gap = " << min_gap << std::endl;
    return min_gap;
  }

};

void test_time_difference() {
  Solution soln;

  assert(soln.to_minutes("00:00") == 0);
  assert(soln.to_minutes("00:01") == 1);
  assert(soln.to_minutes("00:11") == 11);
  assert(soln.to_minutes("02:11") == 131);
  assert(soln.to_minutes("23:59") == 1439);

  assert(soln.findMinDifference({"23:59","00:00"}) == 1);
  assert(soln.findMinDifference({"10:00","20:00","00:00"}) == 240);
  assert(soln.findMinDifference({"10:00","20:00","00:00","10:05"}) == 5);
}

int main(int argc, char** argv) {
  test_time_difference();
  std::cout << argv[0] + 2 << "...OK!" << std::endl;
  return 0;
}
