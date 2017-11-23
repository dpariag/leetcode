// Leetcode: https://leetcode.com/problems/meeting-rooms/description/ 
// Given an array of meeting time intervals consisting of start and end times [[s1,e1],[s2,e2],...] 
// (si < ei), determine if a person could attend all meetings.

// Brute Force: For each meeting, scan the array looking for an overlapping one. O(n^2) time.
// Better: Sort the array by meeting end times, then scan once looking for meetings that start
// before their predecessor ends. O(n*logn) time.

#include <vector>
#include <algorithm>
#include <iostream>
#include <assert.h>

struct Interval {
  int start;
  int end;
  Interval() : start(0), end(0) {}
  Interval(int s, int e) : start(s), end(e) {}
};

// Accepted. 9ms. Beats 59.24% of submissions, ties 40.76% of submissions.
class Solution {
public:
    bool canAttendMeetings(std::vector<Interval>& intervals) {
       std::sort(intervals.begin(), intervals.end(),
                  [](const Interval& i1, const Interval& i2) { 
                    return (i1.end < i2.end) || ((i1.end == i2.end) && i1.start < i2.start); });

      for (int i = 1; i < int(intervals.size()); ++i) {
        // Back-to-back meetings are OK
        if (intervals[i].start < intervals[i-1].end) { return false; }
      }
      return true;
    }
};

int main(int argc, char** argv) {
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
