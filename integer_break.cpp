// Leetcode: https://leetcode.com/problems/integer-break/description/
// Given a positive integer n, where 2 <= n <= 58 break it into the sum of at least two positive integers
// and maximize the product of those integers. Return the maximum product you can get.

// Brute Force: Calculate all possible sums of two integers that sum to n. Track the product of each pair.
// Also consider recursive decomposition of LHS and RHS in each sum, tracking the max. O(2^n) time.
// Better: Memoize the recursion. Note a DP bottom-up solution is also possible.

#include <vector>
#include <iostream>
#include <assert.h>

static const int MAX_PRODUCT = 58;

// Accepted. 0ms. Beats 25.68% of submissions, ties 74.32% of submissions.
class Solution {
public:
    int find_max_product(std::vector<int>& products, int n) {
        if (n <= 0) { return 0; }
        if (products[n] != -1) { return products[n]; } 

        int rhs = 1;
        int max_product = 0;
        while (rhs <= n/2) {
            int sub_product1 = find_max_product(products, n-rhs);
            int sub_product2 = find_max_product(products, rhs);
            
            max_product = std::max(max_product, sub_product1 * sub_product2); 
            max_product = std::max(max_product, sub_product1 * rhs); 
            max_product = std::max(max_product, n-rhs * sub_product2); 
            max_product = std::max(max_product, (n-rhs) * rhs); 
            ++rhs;
        }
        products[n] = max_product;
        return max_product;
    }

    int integerBreak(int n) {
        std::vector<int> products(MAX_PRODUCT + 1, -1);
        products[1] = 1;
        products[2] = 1; // 2 = 1 + 1 and 1*1 = 1
        return find_max_product(products, n);
    }
};

void test_integer_break() {
    Solution soln;

    assert(soln.integerBreak(2) == 1); 
    assert(soln.integerBreak(3) == 2); 
    assert(soln.integerBreak(4) == 4); 
    assert(soln.integerBreak(6) == 9); 
    assert(soln.integerBreak(7) == 12); 
    assert(soln.integerBreak(8) == 18); 
    assert(soln.integerBreak(10) == 36); 
}

int main(int argc, char** argv) {
    test_integer_break();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
