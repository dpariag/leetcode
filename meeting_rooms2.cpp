// Leetcode: https://leetcode.com/problems/meeting-rooms-ii/description/
// Given an array of meeting time intervals consisting of start and end times [[s1,e1],[s2,e2],...] 
// (si < ei), find the minimum number of conference rooms required.

// Brute Force: Use an array to represent all time slots. Iterate intervals incrementing any time 
// with a room in use.
// Better: Split intervals into start and end times, and sort each. Starting a new meeting 
// (advancing start) adds a room.
// Advancing end (if current end <= current start) frees up a room. Track max.

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

using Intervals = std::vector<Interval>;

// Accepted. 12ms. Beats 68.35% of submissions, ties 13.08% of submissions.
class Solution {
public:
    int minMeetingRooms(Intervals& intervals) {
        std::vector<int> start_times(intervals.size(), 0);
        std::vector<int> end_times(intervals.size(), 0);

        for (int i = 0; i < int(intervals.size()); ++i) {
            start_times[i] = intervals[i].start;
            end_times[i] = intervals[i].end;
        }

        std::sort(start_times.begin(), start_times.end());
        std::sort(end_times.begin(), end_times.end());
        int max_rooms = 0;

        int ended = 0;
        for (int started = 0; started < int(start_times.size()); ++started) {
            while (end_times[ended] <= start_times[started]) { ++ended; }
            max_rooms = std::max(max_rooms, (started-ended+1));
        }
        return max_rooms;
    }
};

bool test_min_rooms(Intervals intervals, int expected_min) {
    Solution soln;
    return soln.minMeetingRooms(intervals) == expected_min; 
}

void test_min_rooms() {
    assert(test_min_rooms({{11,20},{4,19},{13,17},{6,13}}, 3));
    assert(test_min_rooms({{1,5},{8,9},{8,9}}, 2));
    assert(test_min_rooms({{13,15},{1,13}}, 1));
    assert(test_min_rooms({{5,10}}, 1));
    assert(test_min_rooms({{5,10},{15,20}}, 1));
    assert(test_min_rooms({{5,10},{15,20},{0,30}}, 2));
    assert(test_min_rooms({{1,10},{1,18},{15,20},{11,40}}, 3));
    assert(test_min_rooms({{6,17},{8,9},{11,12},{6,9}}, 3));
}

int main(int argc, char** argv) {
    test_min_rooms();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
