// Leetcode: https://leetcode.com/problems/max-points-on-a-line/description/

// Brute Force: Generate all pairs of lines. For each line, count all points that lie on the line. O(n^3) time.
// Better: For a given point, examine all remaining points to see how many unique lines are formed.
// Determine uniqueness by storing lines in a hash map.

#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <utility>
#include <iostream>
#include <cmath>
#include <assert.h>

struct Point {
    int x;
    int y;
    Point() : x(0), y(0) {}
    Point(int a, int b) : x(a), y(b) {}
};

int gcd(int num1, int num2) {
    while (num2) {
        int temp = num2; 
        num2 = num1 % num2;
        num1 = temp;
    }
    return num1;
}

struct Line {
    Line(const Point& p1, const Point& p2): p(p1) {
        int rise = p2.y - p1.y;
        int run = p2.x - p1.x;
        int g_div =  gcd(rise, run);
        slope.first = rise / g_div, slope.second = run / g_div;
    }

    bool operator==(const Line& other) const {
        return slope == other.slope && p.x == other.p.x && p.y == other.p.y;
    }

    std::pair<int,int> slope;
    Point p;
};

struct LineHash {
    size_t operator()(const Line& l) const {
        return (l.slope.first*19 + l.slope.second*23) ^ (l.p.x ^ l.p.y);
    }
};

struct PointEquals {
   bool operator()(const Point& p1, const Point& p2) const { return p1.x == p2.x && p1.y == p2.y; }
};

using Points = std::vector<Point>;

// Accepted. 11ms. Beats 44.25% of submissions, ties < 1% of submissions.
class Solution {
public:
    int maxPoints(Points& points) {
        if (points.size() <= 1) { return points.size(); }

        PointEquals point_equals;
        std::unordered_map<Line, int, LineHash> line_map;
        int max_count = 0;

        for (int i = 0; i < points.size(); ++i) {
            line_map.clear();
            int duplicate_points = 1;
            int max_points = 0;
            for (int j = i+1; j < points.size(); ++j) {
                if (point_equals(points[i], points[j])) {
                    ++duplicate_points;
                } else {
                    Line l(points[i], points[j]);
                    int count = ++line_map[l];
                    max_points = std::max(max_points, count);
                }
            }
            max_count = std::max(max_count, max_points + duplicate_points);
        }
        return max_count;
    }
};

bool test_max_lines(Points points, int expected) {
    Solution soln;
    return soln.maxPoints(points) == expected;
}

void test_max_lines() {
    assert(test_max_lines({}, 0));
    assert(test_max_lines({{0,0}}, 1));
    assert(test_max_lines({{0,0},{0,0}}, 2));
    assert(test_max_lines({{1,1},{2,2}}, 2));
    assert(test_max_lines({{1,1},{2,2},{3,3}}, 3));
    assert(test_max_lines({{1,1},{2,2},{3,3},{3,1}}, 3));
    assert(test_max_lines({{1,1},{2,2},{3,3},{3,1},{-1,-1}}, 4));
    assert(test_max_lines({{1,1},{2,2},{3,3},{3,1},{-1,-1},{-1,-2}}, 4));
    assert(test_max_lines({{1,1},{2,2},{3,3},{3,6},{-1,-2},{-1,-2}}, 3));
    assert(test_max_lines({{1,1},{2,2},{3,6},{4,8},{-1,-2},{-2,-4}}, 4));
    assert(test_max_lines({{560,248},{0,16},{30,250},{950,187},{630,277},{950,187},
                           {-212,-268},{-287,-222},{53,37},{-280,-100},{-1,-14},{-5,4},{-35,-387},{-95,11},
                           {-70,-13},{-700,-274},{-95,11},{-2,-33},{3,62},{-4,-47},{106,98},{-7,-65},
                           {-8,-71},{-8,-147},{5,5},{-5,-90},{-420,-158},{-420,-158},{-350,-129},{-475,-53},
                           {-4,-47},{-380,-37},{0,-24},{35,299},{-8,-71},{-2,-6},{8,25},{6,13},{-106,-146},
                           {53,37},{-7,-128},{-5,-1},{-318,-390},{-15,-191},{-665,-85},{318,342},{7,138},
                           {-570,-69},{-9,-4},{0,-9},{1,-7},{-51,23},{4,1},{-7,5},{-280,-100},{700,306},{0,-23},
                           {-7,-4},{-246,-184},{350,161},{-424,-512},{35,299},{0,-24},{-140,-42},{-760,-101},
                           {-9,-9},{140,74},{-285,-21},{-350,-129},{-6,9},{-630,-245},{700,306},{1,-17},{0,16},
                           {-70,-13},{1,24},{-328,-260},{-34,26},{7,-5},{-371,-451},{-570,-69},{0,27},{-7,-65},
                           {-9,-166},{-475,-53},{-68,20},{210,103},{700,306},{7,-6},{-3,-52},{-106,-146},{560,248},
                           {10,6},{6,119},{0,2},{-41,6},{7,19},{30,250}}, 22));
}

void test_gcd() {
    assert(gcd(1,0) == 1);
    assert(gcd(1,1) == 1);
    assert(gcd(5,1) == 1);
    assert(gcd(5,2) == 1);
    assert(gcd(4,2) == 2);
    assert(gcd(6,8) == 2);
    assert(gcd(6,9) == 3);
    assert(gcd(15,9) == 3);
    assert(gcd(7,13) == 1);
}

int main(int argc, char** argv) {
    test_gcd();
    test_max_lines();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}