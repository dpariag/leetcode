// Leetcode: https://leetcode.com/problems/product-of-array-except-self/
// Given an array, nums,  of n integers where n > 1, return an array, output, such that output[i]
// contains the product of all the elements of nums except nums[i].
// Example: given [1,2,3,4], return [24,12,8,6]

// Brute Force: For each i, iterate nums computing the product nums[j], where j != i. O(n^2) time.
// Better: Pre-compute prefix & suffix products of nums[i]. Use these products to compute output[i].
// O(n) time and space.

#include <vector>
#include <iostream>
#include <assert.h>

struct Product {
    int64_t prefix = 1;
    int64_t suffix = 1;
};

using Products = std::vector<Product>;
using Numbers = std::vector<int>;

// Accepted. 56ms. Beats 23.83% of submissions, ties 7.60% of submissions.
class Solution {
public:
    Numbers productExceptSelf(const Numbers& nums) {
        Numbers output(nums.size());
        Products products(nums.size() + 2); // pad left and right with dummy products
        auto size = nums.size();

        for (auto i = 0; i < size; ++i) {
            products[i+1].prefix = products[i].prefix * nums[i];
            products[size - i].suffix = products[size -i + 1].suffix * nums[size - i - 1];
        }
        for (auto i = 1; i <= size; ++i) {
            output[i-1] = products[i-1].prefix * products[i+1].suffix; 
        }
        return output;
    }
};

bool test_array_product(const Numbers& nums, const Numbers& output) {
    Solution soln;
    return soln.productExceptSelf(nums) == output;
}

void test_array_product() {
    assert(test_array_product({1}, {1}));
    assert(test_array_product({10,20}, {20,10}));
    assert(test_array_product({1,1,1,1}, {1,1,1,1}));
    assert(test_array_product({2,2,2,2}, {8,8,8,8}));
    assert(test_array_product({4,3,2,1}, {6,8,12,24}));
    assert(test_array_product({4,3,2,1}, {6,8,12,24}));
    assert(test_array_product({2,2,2,2,2}, {16,16,16,16,16}));
}

int main(int argc, char** argv) {
    test_array_product();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
