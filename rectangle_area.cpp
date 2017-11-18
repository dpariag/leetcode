// Leetcode: https://leetcode.com/problems/rectangle-area/description/
// Find the total area covered by two rectilinear rectangles in a 2D plane.
// Each rectangle is defined by its bottom left corner and top right corner as shown in the figure.

// Approach: Find the area of intersection by finding the lower of the two tops, higher of the
// two bottoms, rightmost of the two lefts, and leftmost of the two rights. This area may be empty.
// Return the sum of the rectangle areas minus the intersection area.

#include <vector>
#include <iostream>
#include <assert.h>

// 19ms. Beats 25.81% of submissions, ties 13.55% of submissions.
struct Rectangle {
    Rectangle(int t, int b, int l, int r): top(t), bottom(b), left(l), right(r) {}

    int intersect_area(const Rectangle& other) {
        int i_top = std::min(top, other.top);
        int i_bottom = std::max(bottom, other.bottom);
        int i_left = std::max(left, other.left);
        int i_right = std::min(right, other.right);

        if (i_top > i_bottom && i_right > i_left) {
            return (i_top - i_bottom) * (i_right - i_left);
        }
        return 0;
    }

    int area() const {
        return (top-bottom) * (right-left);
    }

    int top = 0;
    int bottom = 0;
    int left = 0;
    int right = 0;
};

class Solution {
public:
    int computeArea(int A, int B, int C, int D, int E, int F, int G, int H) {
        Rectangle r1(D,B,A,C);
        Rectangle r2(H,F,E,G);
        return r1.area() + r2.area() - r1.intersect_area(r2);
    }
};

int main(int argc, char** argv) {
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
