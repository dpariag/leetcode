// Leetcode: https://leetcode.com/problems/non-overlapping-intervals/description/
// Given a collection of intervals, find the minimum number of intervals you need to remove to 
// make the rest of the intervals non-overlapping.

// Brute Force: Generate all subsets of intervals, find the longest non-overlapping subset. 
// Better: Sort the intervals by start. Iterate, tracking the last interval added.
// If an addition causes overlap, choose the interval ending first. O(n*logn) time, O(1) space.

#include <vector>
#include <iostream>
#include <algorithm>
#include <assert.h>

struct Interval {
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};

using Intervals = std::vector<Interval>;

// Accepted. 9ms. Beats 27.84% of submissions, ties 64.73% of submisssions.
class Solution {
public:
    int eraseOverlapIntervals(Intervals& intervals) {
        if (intervals.empty()) { return 0; }
        std::sort(intervals.begin(), intervals.end(),
                 [](const Interval& a, const Interval& b) { return a.start < b.start; });

        int num_removed = 0;
        int last = 0;
        for (int i = 1; i < intervals.size(); ++i) {
            if (intervals[i].start >= intervals[last].end) {
                last = i;
            } else {
                if (intervals[i].end < intervals[last].end) {
                    last = i;
                }
                ++num_removed;
            }
        }
        return num_removed;
    }
};


bool test_erase_overlapping(Intervals intervals, int expected_removals) {
    Solution soln;
    return soln.eraseOverlapIntervals(intervals) == expected_removals;
}

void test_erase_overlapping() {
    assert(test_erase_overlapping({{1,2},{2,3}}, 0));
    assert(test_erase_overlapping({{1,2},{2,3},{3,4},{1,3}}, 1));
    assert(test_erase_overlapping({{1,2},{1,2},{1,2}}, 2));
    assert(test_erase_overlapping({{1,2},{1,6},{3,4},{2,4},{2,3}}, 2));
}

int main(int argc, char** argv) {
    test_erase_overlapping();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
