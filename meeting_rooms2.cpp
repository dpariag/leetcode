// Leetcode: https://leetcode.com/problems/meeting-rooms-ii/description/
// Given an array of meeting time intervals consisting of start and end times [[s1,e1],[s2,e2],...] 
// (si < ei), find the minimum number of conference rooms required.

// Brute Force:
// Better:

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

// Accepted. 1365ms. Beats 0.09% of submissions, ties < 1% of submissions.
class Solution {
public:
    int minMeetingRooms(Intervals& intervals) {
        int left = std::numeric_limits<int>::max(), right = std::numeric_limits<int>::min();
        for (int i = 0; i < int(intervals.size()); ++i) {
            left = std::min(left, intervals[i].start);
            right = std::max(right, intervals[i].end);
        }

        std::vector<int> layout(right-left+1, 0);
        int max_rooms = 0;
        for (int i = 0; i < int(intervals.size()); ++i) {
            for (int start = intervals[i].start; start < intervals[i].end; ++start) {
                layout[start-left] += 1;
                max_rooms = std::max(max_rooms, layout[start-left]);
            }
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
