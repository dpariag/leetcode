// Leetcode: https://leetcode.com/problems/largest-sum-of-averages/description/
// If we partition an integer array A into at most K adjacent (non-empty) sub-arrays, then our score is the sum of 
// the average of each sub-array. What is the largest score possible?

// Brute Force: Recursively calculate all splits of A into K sub-arrays. O(n^k) time.
// Better: Memoize subproblems. Define table[K][end] to be the best score possible with K splits
// over the range [0,end] inclusive. Then use DP to fill in the table as below.

#include <vector>
#include <iostream>
#include <assert.h>

// Accepted. 4ms. Beats 99.04% of submissions.
class Solution {
public:
    double largestSumOfAverages(std::vector<int>& A, int K) {
        std::vector<std::vector<double>> averages(K, std::vector<double>(A.size(), 0.0));;
        std::vector<double> sums(A.size(), 0);
       
        sums.front() = A.front();
        averages[0].front() = A.front();
        for (int i = 1; i < A.size(); ++i) {
            sums[i] = A[i] + sums[i-1];
            averages[0][i] = double(sums[i]) / double(i+1);
        }

        for (int k = 1; k < K; ++k) {
            auto start = k;
            for (int end = start; end < A.size(); ++end) {
                // Find the best split in the range [start,end]
                double max_avg = 0.0;
                // split is the starting index of the rightmost subarray
                for (int split = start; split <= end; ++split) {
                    // Find the average of everything to the right of the split
                    double right_avg = (sums[end] - sums[split-1]) / (end - split + 1);
                    // Find the sum of averages left of the split
                    double left_sum_avgs = averages[k-1][split-1];
                    max_avg = std::max(max_avg, left_sum_avgs + right_avg);
                }
                averages[k][end] = max_avg;
            }
        }
        return averages.back().back();      
    }
};

void test_largest_sum_of_averages() {
    Solution soln;
    std::vector<int> A{9,1,2,3,9};
    assert(soln.largestSumOfAverages(A, 3) == 20);
}

int main(int argc, char** argv) {
    test_largest_sum_of_averages();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
