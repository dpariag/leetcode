// Leetcode: https://leetcode.com/problems/range-sum-query-2d-mutable/description/
// Given a 2D matrix, implement two functions:
// sum(row1, col1, row2, col2)  : return the sum of the area defined by (row1, col1) and (row2, col2).
// update(row, col, value)      : matrix[row][col] = value

// Brute Force: Store the matrix in memory, sweep the rectangle to compute sums. O(1) update(), O(n^2) sum().
// Better: Store row_sums[i][j] = sum(matrix[row][0]...matrix[row][j]) inclusive. (n) update() and sum()

#include <vector>
#include <iostream>
#include <assert.h>

using Matrix = std::vector<std::vector<int>>;

// Accepted. 89ms. Beats 79.39% of submissions, ties 0.84% of submissions.
class NumMatrix {
public:
    NumMatrix(const Matrix& matrix) : m_row_sums(matrix), m_num_rows(matrix.size()) {
        if (!matrix.empty()) m_num_cols = matrix[0].size();
        for (int row = 0; row < m_num_rows; ++row) {
            for (int col = 1; col < m_num_cols; ++col) {
                m_row_sums[row][col] += m_row_sums[row][col-1];
            }
        }
    }
    
    void update(int row, int col, int val) {
        auto old_value = m_row_sums[row][col];
        if (col > 0) old_value -= m_row_sums[row][col-1];
        auto delta = (val - old_value);

        for (int j = col; j < m_num_cols; ++j) {
            m_row_sums[row][j] += delta;
        }
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
        int sum = 0;
        for (int row = row1; row <= row2; ++row) {
            sum += m_row_sums[row][col2];
            if (col1 > 0) sum -= m_row_sums[row][col1-1];
        }
        return sum;
    }
private:
    Matrix m_row_sums; // m_row_sums[i][j] = sum of row i from 0..j inclusive
    int m_num_rows;
    int m_num_cols;
};

void test_sum_region_mutable() {
    NumMatrix n({{1,2,3,4},{5,6,7,8},{9,10,11,12}});

    assert(n.sumRegion(0,0,2,3) == 78);
    assert(n.sumRegion(0,0,1,3) == 36);
    assert(n.sumRegion(1,1,1,3) == 21);
    assert(n.sumRegion(1,1,2,3) == 54);

    n.update(2,3, 15);
    assert(n.sumRegion(0,0,2,3) == 81);
    assert(n.sumRegion(0,0,1,3) == 36);
    assert(n.sumRegion(2,0,2,3) == 45);
    n.update(2,3, 12);
    assert(n.sumRegion(2,0,2,3) == 42);

    n.update(1,2,12);
    assert(n.sumRegion(0,0,2,3) == 83);
    assert(n.sumRegion(0,0,0,3) == 10);
    assert(n.sumRegion(0,0,1,3) == 41);

}

int main(int argc, char** argv) {
    test_sum_region_mutable();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
