// Leetcode: https://leetcode.com/problems/valid-square/description/
// Given the co-od of 4 points in 2D space, determine if the points construct a square.

// Brute Force: Identify top-left, top-right, etc. corners, calculate side lengths and corner angles.
// Better: Generate all 6 lines connecting 4 points. Square has 4 equal sides and 2 equal diagonals.

#include <vector>
#include <limits>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <assert.h>

using Pt = std::vector<int>;
using Points = std::vector<Pt>;

// Accepted. 6ms. Beats 20.30% of submissions, ties 53.96% of submissions
class Solution {
public:
    inline double line_length(const Pt& p1, const Pt& p2) {
        double rise = p1[1] - p2[1];
        double run = p1[0] - p2[0];
        return std::sqrt(rise*rise + run*run); 
    }

    inline bool eq(double a, double b) {
        return (a < b) ? (b-a) < 0.0001 : (a-b) < 0.0001;
    }

    bool validSquare(const Pt& p1, const Pt& p2, 
                     const Pt& p3, const Pt& p4) {
        Points points({p1,p2,p3,p4});
        std::vector<double> lens;

        for (int i = 0; i < 4; ++i) {
            for (int j = i+1; j < 4; ++j) {
                double length = line_length(points[i], points[j]);
                if (length == 0) { return false; }
                lens.push_back(length);
            }
        }

        std::sort(lens.begin(), lens.end());
        return eq(lens[0],lens[1]) && eq(lens[1],lens[2]) && eq(lens[2],lens[3]) && 
               eq(lens[4],lens[5]);
    }
};

void test_valid_square() {
    Solution soln;

    assert(soln.validSquare({1,0}, {-1,0}, {0,1}, {0,-1}));
    assert(soln.validSquare({0,0}, {1,1}, {1,0}, {0,1}));
    assert(soln.validSquare({-1,-1}, {1,1}, {-1,1}, {1,-1}));
    assert(soln.validSquare({0,0}, {1,1}, {1,0}, {0,2}) == false); // (0,2) not valid for a square
    assert(soln.validSquare({-1,-1}, {2,1}, {-1,1}, {2,-1}) == false); // rectangle
}

int main(int argc, char** argv) {
    test_valid_square();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
