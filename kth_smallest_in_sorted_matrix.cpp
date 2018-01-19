// Leetcode: https://leetcode.com/problems/kth-smallest-element-in-a-sorted-matrix/description/

// Brute Force: Copy the matrix to an array, sort it and return the k'th element. O(n^2*logn) in best case
// Better: Use a min-heap to iterate the rows of the matrix. O(k*logn). Better if k << n^2

#include <vector>
#include <queue>
#include <iostream>
#include <assert.h>

using Matrix = std::vector<std::vector<int>>;

struct Cood {
    int row = 0;
    int col = 0;
    int value = 0;
    Cood(int r, int c, int v): row(r), col(c), value(v) {}
    bool operator>(const Cood& other) const { return value > other.value; }
};
using MinHeap  = std::priority_queue<Cood, std::vector<Cood>, std::greater<Cood>>;

// Accepted. 46ms. Beats 41.68% of submissions, ties 11.86% of submissions.
class Solution {
public:
    int kthSmallest(Matrix& matrix, int k) {
        MinHeap min_heap;

        // Add the first column to the min-heap
        for (int row = 0; row < matrix.size(); ++row) {
            min_heap.emplace(row, 0, matrix[row][0]);
        }

        // Repeatedly remove the smallest row value and replace it with its successor
        int i = 0, k_smallest = 0;
        while (i < k) {
            auto min = min_heap.top();
            min_heap.pop();
            if (min.col + 1 < matrix[min.row].size()) {
                min_heap.emplace(min.row, min.col+1, matrix[min.row][min.col+1]);
            }
            ++i;
            k_smallest = min.value;
        }
        return k_smallest;
    }
};

int main(int argc, char** argv) {
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
