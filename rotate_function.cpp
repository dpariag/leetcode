// Leetcode: https://leetcode.com/problems/rotate-function/#/description
// Given an integer array A, obtain Bk by rotating A k positions clockwise. Then define:
// F(k) = 0 * Bk[0] + 1 * Bk[1] + ... + (n-1) * Bk[n-1].
// Calculate the maximum value of F(0), F(1), ..., F(n-1).

// Brute Force: Calculate N rotations (Bk), calculate F(k) for each. 
// O(n^2) time, assuming O(n) array rotations.
// Better: Realize that F(i+1) = F(i) + sum(A[0..n-1]) - (n*A[n-i]). 
// Each F(i) can be calculated in O(1) time, so O(n) time overall.

#include <vector>
#include <iostream>
#include <numeric>
#include <assert.h>

// Accepted. 9ms. Beats 45.06% of submissions, ties 54.94% of submissions.
class Solution {
public:
    int maxRotateFunction(const std::vector<int>& A) {
        const int sum = std::accumulate(A.begin(), A.end(), 0);
        int F_i = 0;
        for (int i = 1; i < A.size(); ++i) {
            F_i += i * A[i];
        }

        const int size = A.size();
        int max_F_i = F_i;
        for (int i = 1; i < A.size(); ++i) {
            F_i = F_i + sum - (size*A[size-i]);
            max_F_i = std::max(max_F_i, F_i);
        }
        return max_F_i;
    }
};

void test_rotate_function() {
    Solution soln;
    assert(soln.maxRotateFunction({}) == 0);
    assert(soln.maxRotateFunction({5}) == 0);
    assert(soln.maxRotateFunction({5,1}) == 5);
    assert(soln.maxRotateFunction({5,10}) == 10);
    assert(soln.maxRotateFunction({4,6,9,1}) == 43);
}

int main(int argc, char** argv) {
    test_rotate_function();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
