// Leetcode: https://leetcode.com/problems/find-right-interval/description/
// For each interval i in a given set, find the nearest interval whose start point is >= i's 
// end point.

// Brute Force: For each interval, scan the array looking for the earliest foll. interval. O(n^2)
// Better: Sort a copy of the array by interval.start. For each interval, use binary search to
// find the earliest foll. interval. O(n*logn) time.

#include <vector>
#include <algorithm>
#include <unordered_map>
#include <iostream>
#include <assert.h>

struct Interval {
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};

using Intervals = std::vector<Interval>;
using IntervalMap = std::unordered_map<int, int>; // Interval.start --> index

// Accepted. 86ms. Beats 81.58% of submissions, ties 7.02% of submisssions.
class Solution {
public:

    int bsearch(const Intervals& intervals, int interval_end, int start, int end) {
        if (start > end) { return start; }
        
        int mid = start + (end - start) / 2;
        
        if (intervals[mid].start == interval_end) {
            return mid;
        } else if (interval_end < intervals[mid].start) {
            return bsearch(intervals, interval_end, start, mid-1);
        } else { 
            return bsearch(intervals, interval_end, mid+1, end);
        }
    }

    std::vector<int> findRightInterval(Intervals& intervals) {
        std::vector<int> result(intervals.size(), 0);
        IntervalMap interval_map;

        for (int i = 0; i < intervals.size(); ++i) {
            interval_map[intervals[i].start] = i;
        }

        Intervals sorted = intervals;
        std::sort(sorted.begin(), sorted.end(), 
                 [](const Interval& a, const Interval& b) { return a.start < b.start; });

        for (int i = 0; i < intervals.size(); ++i) {
            auto right_interval = bsearch(sorted, intervals[i].end, 0, sorted.size() - 1);
            result[i] = (right_interval >= sorted.size()) ? -1 : 
                        interval_map[sorted[right_interval].start];
        }
        return result;
    }
};

bool test_right_intervals(Intervals intervals, std::vector<int> expected) {
    Solution soln;
    auto right_intervals = soln.findRightInterval(intervals);
    return right_intervals == expected;
}

void test_right_intervals() {
    assert(test_right_intervals({}, {}));
    assert(test_right_intervals({{1,2}}, {-1}));
    assert(test_right_intervals({{3,4},{2,3},{1,2}}, {-1,0,1}));
    assert(test_right_intervals({{1,4},{2,3},{3,4}}, {-1,2,-1}));
}

int main(int argc, char** argv) {
    test_right_intervals();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
