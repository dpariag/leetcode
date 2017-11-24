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

class Solution {
public:
    int minMeetingRooms(Intervals& intervals) {
        if (intervals.empty()) { return 0; }
        // Sort by increasing end time
        std::sort(intervals.begin(), intervals.end(),
                [](const Interval& i1, const Interval& i2) {
                    return (i1.end < i2.end) || (i1.end == i2.end && i1.start < i2.start); });

        int left = 0, right = 0, rooms = 0, max_rooms = 0;
        while (right < intervals.size()) {
            while (intervals[left].end <= intervals[right].start) { 
                ++left; 
                rooms = std::max(0, rooms-1);
                std::cout << "*rooms = " << rooms << std::endl;
            }
            //max_rooms = std::max(max_rooms, right - left + 1);
            if (rooms == 0 || (right > 0 && intervals[right].start < intervals[right-1].end)) { ++rooms; }
            std::cout << "rooms = " << rooms << std::endl;
            max_rooms = std::max(rooms, max_rooms);
            ++right;
        }
        std::cout << "max rooms = " << max_rooms << std::endl;
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
