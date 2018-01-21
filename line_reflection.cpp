// Leetcode: https://leetcode.com/problems/line-reflection/description/
// Given n 2-D points, find if there is a line parallel to y-axis that reflects the given points.

// Brute Force: Consider all pairs of points. Find the dividing line and see if each point is reflected. O(n^3)

// Better: Find the leftmost and rightmost points and calculate their dividing line. Sort points by x co-od,
// breaking ties differently depending if points are on the left or right. Iterate the array from both ends,
// each pair should reflect each other.

// Better: Store all points in a hash map by y co-od. Use the dividing line between leftmost and rightmost
// points. Each point should have a counterpart in the hash map on the other side of the line.

#include <vector>
#include <algorithm>
#include <iostream>
#include <assert.h>

using Pnt = std::pair<int,int>;
using Points = std::vector<Pnt>;

bool point_less(const Pnt& p1, const Pnt& p2, double line) {
    if (p1.first < p2.first) { return true; } // lies to the left
    if (p1.first == p2.first) {
        // Break ties differently left and right of the line
        if (p1.first < line) { 
            return p1.second > p2.second; 
        } else {
            return p1.second < p2.second;
        }
    }
    return false;
}

// Accepted. 21ms. Beats 73.86% of submissions, ties < 1% of submissions.
class Solution {
public:
    bool isReflected(Points& points) {
        if (points.size() < 2) { return true; }

        int min_x = std::numeric_limits<int>::max();
        int max_x = std::numeric_limits<int>::min();
        for (auto& p : points) {
            min_x = std::min(min_x, p.first);
            max_x = std::max(max_x, p.first);
        }
        double dist = double(max_x - min_x) / 2.0;
        double line = min_x + dist;

        std::sort(points.begin(), points.end(),
                  [line](const Pnt& p1, const Pnt& p2) { return point_less(p1,p2,line);});
        
        int left = 0, right = points.size() - 1;
        while (left < right) {
            // Remaining points are on the line
            if (points[left].first == line && points[right].first == line) { return true; }
            
            // Check y co-ods match
            if (points[left].second  != points[right].second) { return false; }
            
            double left_dist = line - double(points[left].first);
            double right_dist = double(points[right].first) - line; 
            if (left_dist != right_dist) { return false; }

            ++left, --right;
            while (left < points.size() && points[left] == points[left-1]) {++left; }
            while (right >= 0 && points[right] == points[right+1]) {--right;}
        }

        return (left == right) ? points[left].first == line : true;
    }
};

bool test_line_reflection(Points points, bool expected) {
    Solution soln;
    return soln.isReflected(points) == expected;
}

void test_line_reflection() {
    assert(test_line_reflection({{0,0},{1,0},{3,0}}, false));
    assert(test_line_reflection({{-16,1},{16,1},{16,1}}, true));
    assert(test_line_reflection({{-16,1},{16,1},{16,1},{16,1}}, true));
    assert(test_line_reflection({{-3,1},{-3,2},{-2,2},{-2,4},{2,2},{2,4},{3,1},{3,2}}, true));
}

int main(int argc, char** argv) {
    test_line_reflection();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
