// Leetcode: https://leetcode.com/problems/largest-rectangle-in-histogram/description/
// Given a histogram specified as array of unit-width bars, find the area of the largest rectangle 
// in the histogram.

// Brute Force: For each A[i], scan forward to find largest rectangle starting at A[i]. O(n^2) time.
// Better: Use a stack to store the buildings in ascending order of height. If a shorter building
// is discovered, pop all taller buildings from the stack calculating the largest rectangle that uses
// the popped building as it's tallest building.

#include <vector>
#include <stack>
#include <limits>
#include <iostream>
#include <assert.h>

// Accepted. 9ms. Beats 70.06% of submissions, ties 29.94% of submissions.
class Solution {
public:
    int largestRectangleArea(const std::vector<int>& bars) {
        std::stack<int> stack; // Indices of increasingly taller buildings
        int max_area = 0;

        for (int i = 0; i < bars.size(); ++i) {
            if (stack.empty() || bars[i] > bars[stack.top()]) {
                // Current bar is taller than stack top, save it.
                stack.push(i);
            } else {
                // Current bar is shorter than stack top
                // Pop taller bars, calculating rectangle area with popped bar as the tallest bar.
                while (!stack.empty() && bars[stack.top()] > bars[i]) {
                    int popped = stack.top();
                    stack.pop();
                    // Popped bar is height of the rectangle
                    // The current stack top is the shortest building to the left of popped
                    // bars[i] is the shortest building to the right of popped
                    // Therefore i - stack.top() - 1 is the width of the building
                    int area = bars[popped] * (stack.empty() ? i : i - stack.top() - 1);
                    max_area = std::max(max_area, area);
                }
                stack.push(i);
            }
        }
        while (!stack.empty()) {
            int top = stack.top();
            stack.pop();
            int area = (bars[top] * (stack.empty() ? bars.size() : bars.size() - stack.top() - 1));
            max_area = std::max(max_area, area);
        }
        return max_area;
    }
};

void test_largest_rectangle() {
    Solution soln;
    assert(soln.largestRectangleArea({5,5,1,7,1,1,5,2,7,6}) == 12);
    assert(soln.largestRectangleArea({5}) == 5);
    assert(soln.largestRectangleArea({5,5}) == 10);
    assert(soln.largestRectangleArea({5,0,5}) == 5);
    assert(soln.largestRectangleArea({5,4,3,2,1}) == 9);
    assert(soln.largestRectangleArea({3,1,4,3,1,1,4,1,1}) == 9);
    assert(soln.largestRectangleArea({2,3,3,4,1,3,2,3}) == 9);
    assert(soln.largestRectangleArea({1,3,2,0,4,3,2,0,4,4,4}) == 12);
}

int main(int argc, char** argv) {
    test_largest_rectangle();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
