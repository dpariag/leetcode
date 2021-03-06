// Leetcode: https://leetcode.com/problems/range-sum-query-2d-immutable/description/
// Given a 2D matrix, find the sum of the elements inside the rectangle defined by the 2 corners
// (row1, col1) and (row2, col2). The matrix is immutable, and many sum queries are executed.

// Brute Force: For each call, sweep the rectangle and sum it's elements. O(n^2) time.
// Better: Pre-compute row sums of the matrix. The sum can then be computed in O(n) time.

#include <vector>
#include <iostream>
#include <assert.h>

using Matrix = std::vector<std::vector<int>>;

// Accepted. 22ms. Beats 57.59% of submissions, ties 30.22% of submissions.
class NumMatrix {
public:
    NumMatrix(const Matrix& m): row_sums(m) {
        for (int row = 0; row < m.size(); ++row) {
            for (int col = 1; col < m[0].size(); ++col) {
                row_sums[row][col] = row_sums[row][col-1] + m[row][col];
            }
        }
    }

    int sumRegion(int row1, int col1, int row2, int col2) {
        if (row_sums.empty()) { return 0; }
        int total_sum = 0, left_sum = 0;
        for (int i = row1; i <= row2; ++i) {
            total_sum += row_sums[i][col2];
            if (col1 > 0) left_sum += row_sums[i][col1-1];
        }
        return total_sum - left_sum;
    }
private:
   Matrix row_sums; 
};

void test_sum_region() {
    Matrix m({{2,4,10,5}, {1,1,2,3}, {4,1,0,8}, {1,2,1,2}});
    NumMatrix num_matrix(m);

    assert(num_matrix.sumRegion(0,0,1,1) == 8);
    assert(num_matrix.sumRegion(0,2,1,3) == 20);
    assert(num_matrix.sumRegion(0,1,1,3) == 25);
    assert(num_matrix.sumRegion(0,0,1,3) == 28);
    assert(num_matrix.sumRegion(3,0,3,3) == 6);
}

int main(int argc, char** argv) {
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
