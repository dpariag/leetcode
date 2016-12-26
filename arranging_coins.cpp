// Leetcode: https://leetcode.com/problems/arranging-coins/
// Given n coins, you want to form in a staircase shape, where the k-th row has exactly k coins.
// Find the total number of full staircase rows that can be formed.

// Brute Force: Sum 1 + 2 + 3 + ... until the sum exceeds n. Return (num_additions - 1). O(sqrt(n))
// Better: sum(1..n) = n * (n+1) / 2. Use binary search to find the number of rows. O(log(n))

#include <iostream>
#include <assert.h>

// Accepted. 9ms. Beats 62.18% of submissions, ties 37.72% of submissions.
class Solution {
public:
    int arrangeCoins(int n) {
        if (n <= 0) { return 0; }
        uint64_t min_rows = 1, max_rows = n;
        uint64_t rows = 0, sum = 0;

        while (min_rows < max_rows) {
            rows = min_rows + (max_rows - min_rows) / 2;
            sum = (rows * (rows+1)) / 2; 
            if (sum == n) {
                return rows;
            } else if (sum < n) {
                min_rows = rows + 1;
            } else { // sum > n
                max_rows = rows - 1;
            }
        }
        sum = (min_rows * (min_rows+1)) / 2;
        return sum > n ? min_rows - 1 : min_rows;
    }
};

void test_arrange_coins() {
    Solution soln;
    assert(soln.arrangeCoins(0) == 0);
    assert(soln.arrangeCoins(1) == 1);
    assert(soln.arrangeCoins(2) == 1);
    assert(soln.arrangeCoins(3) == 2);
    assert(soln.arrangeCoins(4) == 2);
    assert(soln.arrangeCoins(5) == 2);
    assert(soln.arrangeCoins(6) == 3);
    assert(soln.arrangeCoins(8) == 3);
    assert(soln.arrangeCoins(10) == 4);
    assert(soln.arrangeCoins(1804289383) == 60070);
    assert(soln.arrangeCoins(1681692777) == 57994);
}

int main(int argc, char** argv) {
    test_arrange_coins();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
