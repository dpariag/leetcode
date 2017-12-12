// Leetcode: https://leetcode.com/problems/triangle/description/
// Given a triangle, find the minimum path sum from top to bottom. 
// At each step, you may move to any adjacent number in the row below.

// Brute Force: Use DFS to evaluate all paths through the triangle. 
// Better: Use DP to track the min sum at each row of the triangle.
// The min sum in the next row is derived from the min sum in the current row.

#include <vector>
#include <algorithm>
#include <iostream>
#include <assert.h>

using Row = std::vector<int>;
using Triangle = std::vector<Row>;

// Accepted. 3ms. Beats 98.33% of submissions, ties 1.67% of submissions.
class Solution {
public:
    int minimumTotal(Triangle& triangle) {
        if (triangle.empty()) { return 0; }
        Row cur_sum = triangle.front(), prev_sum;
        
        for (int row  = 1; row < triangle.size(); ++row) {
            prev_sum = cur_sum;
            cur_sum = Row(triangle[row].size(), 0);

            cur_sum.front() = prev_sum.front() + triangle[row].front();
            cur_sum.back() = prev_sum.back() + triangle[row].back(); 
            for (int col = 1; col < triangle[row].size() - 1; ++col) {
                cur_sum[col] = triangle[row][col] + std::min(prev_sum[col], prev_sum[col-1]);
            }
        } 
        return *std::min_element(cur_sum.begin(), cur_sum.end()); 
    }
};

bool test_min_total(Triangle t, int expected) {
    Solution soln;
    return soln.minimumTotal(t) == expected;
}

void test_min_total() {
    assert(test_min_total({{2}}, 2)); 
    assert(test_min_total({{2},{4,5}}, 6)); 
    assert(test_min_total({{2},{4,5},{1,1,1}}, 7)); 
    assert(test_min_total({{2},{4,5},{1,2,3}}, 7)); 
    assert(test_min_total({{2},{4,5},{11,2,3}}, 8)); 
    assert(test_min_total({{2},{3,4},{6,5,7},{4,1,8,3}}, 11)); 
}

int main(int argc, char** argv) {
    test_min_total();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
