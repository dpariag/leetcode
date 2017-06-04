// Leetcode: https://leetcode.com/problems/next-greater-element-i/#/description
// Given two arrays (without duplicates) where nums1’s elements are subset of nums2. Find all the 
// next greater numbers for nums1's elements in nums2.  The Next Greater Number of a number in nums1 
// is the first greater number to its right in nums2. If it does not exist, output -1 for this number.
// Example: nums1 = [4,1,2], nums2 = [1,3,4,2], return [-1,3,-1]
// Example: nums1 = [4,1,2,3,7,0,10], nums2 = [1,3,4,2,10,8,0,11,7], return []
// Example: nums2 = [1,2,3,10,9,8,15,1,21,16,100,-1,5]

// Brute Force: For each number in nums1, scan nums2 for it, then scan for next greater. O(n^2) time.
// Better: Preprocess nums2 using a stack to calculate the next larger element of nums2[i].
// Record the next larger values in a hash map, then process nums1.

#include <vector>
#include <stack>
#include <unordered_map>
#include <iostream>
#include <assert.h>

using Numbers = std::vector<int>;

// Accepted. 15ms. Beats 54.76% of submissions, ties 8.72% of submissions.
class Solution {
public:
    Numbers nextGreaterElement(const Numbers& nums1, const Numbers& nums2) {
        std::stack<int> pending; // elements in nums2 whose next greater is unknown
        std::unordered_map<int, int> next_greater(nums2.size()*2); // map nums2[i] to its next greater

        for (auto n : nums2) {
            while(!pending.empty() && n > pending.top()) {
                next_greater.emplace(pending.top(), n);
                pending.pop();
            }
            pending.push(n);
        }

        Numbers result(nums1.size(), 0);
        for (int i = 0; i < nums1.size(); ++i) {
            auto found = next_greater.find(nums1[i]);
            result[i] = (found == next_greater.end()) ? -1 : found->second;
        }
        return result;
    }
};

bool test_next_greater(const Numbers& nums1, const Numbers& nums2, const Numbers& expected) {
    Solution soln;
    return soln.nextGreaterElement(nums1, nums2) == expected;
}

void test_next_greater() {
    assert(test_next_greater({4,1,2}, {1,3,4,2}, {-1,3,-1}));
    assert(test_next_greater({1,2,3,4}, {1,2,3,4}, {2,3,4,-1}));
    assert(test_next_greater({4,3,2,1}, {1,2,3,4}, {-1,4,3,2}));
    assert(test_next_greater({4,3,2,1}, {4,3,2,1}, {-1,-1,-1,-1}));
    assert(test_next_greater({3,2,4,1}, {4,3,2,1}, {-1,-1,-1,-1}));
    assert(test_next_greater({3,2,4,1}, {1,-5,4,2,6,3,9}, {9,6,6,4}));
}

int main(int argc, char** argv) {
    test_next_greater();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
