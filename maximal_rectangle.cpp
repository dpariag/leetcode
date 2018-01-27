// Leetcode: https://leetcode.com/problems/maximal-rectangle/description/
// Given a 2D matrix of 0's and 1's, find the area of the largest rectangle containing only 1's.

// Brute Force:
// Better:

#include <vector>
#include <stack>
#include <iostream>
#include <assert.h>

using Matrix = std::vector<std::vector<char>>;
using Histogram = std::vector<int>;
using Histograms = std::vector<Histogram>;

// Accepted. 23ms. Beats 33.65% of submissions, ties 17.67% of submissions.
class Solution {
public:
    inline int largest_rectangle(const Histogram& hist) {
        std::stack<int> indices; // indices of increasingly taller bars
        int area = 0;

        for (int i = 0; i < hist.size(); ++i) {
            if (indices.empty() || hist[i] >= hist[indices.top()]) {
                // New bar of same or greater height
                indices.emplace(i);
            } else {
                // Shorter bar: Pop taller bars updating area calculation
                while (!indices.empty() && hist[indices.top()] > hist[i]) {
                    int height = hist[indices.top()];
                    indices.pop();
                    int width = indices.empty() ? i : (i - indices.top() - 1);
                    area = std::max(area, width*height);
                }
                indices.emplace(i);
            }
        }
        
        int right = hist.size();
        while (!indices.empty()) {
            int height = hist[indices.top()];
            indices.pop();
            int width = indices.empty() ? right : (right - indices.top() - 1);
            area = std::max(area, width*height);
        }
        return area;
    }

    int maximalRectangle(const Matrix& matrix) {
        if (matrix.empty() || matrix[0].empty()) { return 0; }

        int max_area = 0;
        Histograms bars(matrix.size()+1, Histogram(matrix[0].size(), 0));
        for (int i = 0; i < matrix.size(); ++i) {
            for (int j = 0; j < matrix[0].size(); ++j) {
                bars[i+1][j] = (matrix[i][j] == '1') ? bars[i][j] + 1 : 0;
            }
            max_area = std::max(max_area, largest_rectangle(bars[i+1]));
        }
        return max_area;
    }
};

void test_maximal_rectangle() {
    Solution soln;

    assert(soln.maximalRectangle({
                {'1','0','1','0','0'},
                {'1','0','1','1','1'},
                {'1','1','1','1','1'},
                {'1','0','0','1','0'}}) == 6);

    assert(soln.maximalRectangle({
                {'1','0','1','1','1'},
                {'1','0','1','1','1'},
                {'1','1','1','1','1'},
                {'1','0','0','1','0'}}) == 9);

    assert(soln.maximalRectangle({
                {'1','0','1','1','0'},
                {'1','0','0','1','1'},
                {'1','1','1','1','1'},
                {'1','0','0','1','0'}}) == 5);

    assert(soln.maximalRectangle({
                {'1','0','1','1','0'},
                {'1','0','0','1','1'},
                {'1','0','1','1','0'},
                {'1','0','0','1','0'}}) == 4);

    assert(soln.maximalRectangle({
                {'1','1','1','1','0'},
                {'1','1','0','1','1'},
                {'1','1','1','1','0'},
                {'1','1','0','1','0'}}) == 8);

    assert(soln.maximalRectangle({
                {'0','1','1','1','0'},
                {'1','1','1','1','1'},
                {'1','1','1','1','1'},
                {'1','1','0','1','0'}}) == 10);
}

int main(int argc, char** argv) {
    test_maximal_rectangle();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}