// Leetcode: https://leetcode.com/problems/4sum-ii/description/
// Given four integer arrays A, B, C, D, compute how many tuples (i,j,k,l) exist such that 
// A[i] + B[j] + C[k] + D[l] == 0.

// Brute Force: Generate all 4-tuples, counting those with zero sum. O(n^4) time
// Better: Store all pair-sums of C,D in a hash map. Generate pairs over A,B and look up their 
// complement in the map. O(n^2) time.

#include <vector>
#include <iostream>
#include <unordered_map>
#include <assert.h>

using Cache = std::unordered_map<int,int>;

// Accepted. 179ms. Beats 96.94% of submissions, ties 0.34% of submissions. 
class Solution {
public:
    int fourSumCount(const std::vector<int>& A, const std::vector<int>& B, 
                     const std::vector<int>& C, const std::vector<int>& D) {
        Cache cache;
        for (int i = 0; i < C.size(); ++i) {
            for (int j = 0; j < D.size(); ++j) {
                cache[C[i]+D[j]]++;
            }
        }

        int ways = 0;
        for (int i = 0; i < A.size(); ++i) {
            for (int j = 0; j < B.size(); ++j) {
                auto sum = A[i] + B[j];
                auto found = cache.find(-sum);
                if (found != cache.end()) { ways += found->second; }
            }
        }
        return ways;
    }
};

void test_four_sum_count() {
    Solution soln;
    assert(soln.fourSumCount({},{},{},{}) == 0);
    assert(soln.fourSumCount({1,2},{-2,-1},{-1,2},{0,2}) == 2);
    assert(soln.fourSumCount({-1,-1},{-1,1},{-1,1},{1,-1}) == 6);
}

int main(int argc, char** argv) {
    test_four_sum_count();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
