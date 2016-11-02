// Leetcode: https://leetcode.com/problems/kth-largest-element-in-an-array/
// Find the k'th largest element in an unsorted array (not the k'th distinct element).
// Example: Given [3,2,1,5,6,4] and k = 2, return 5. Assume 1 ≤ k ≤ array's length.

// Brute Force: Sort the array and return the k'th largest element. O(n*logn) time and O(1) space.
// Better: Iterate the array, using a min heap to store the k largest elements.
// After iteration, return the top of the heap - this is by definition the k'th largest element.

#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>
#include <assert.h>

using MinHeap = std::priority_queue<int, std::vector<int>, std::greater<int>>;

// Accepted. 15ms runtime. Beats 85.22% of submissions.
class Solution {
public:
    int findKthLargest(std::vector<int>& nums, int k) {
        assert(nums.size() > 0 && k > 0 && k <= nums.size());
        MinHeap min_heap;

        for (auto i = 0; i < nums.size(); ++i) {
            if (min_heap.size() < k) {
                min_heap.emplace(nums[i]);
            } else if (nums[i] >= min_heap.top()) {
                min_heap.pop();
                min_heap.emplace(nums[i]);
            }
        }
        return min_heap.top();
    }
};

bool test_kth_largest(std::vector<int> nums, int k) {
    Solution soln;
    std::vector<int> copy(nums);
    std::sort(copy.begin(), copy.end());
    return copy[copy.size() - k] == soln.findKthLargest(nums, k);
}

void test_kth_largest() {
    assert(test_kth_largest({42}, 1));              // singleton array
    assert(test_kth_largest({3,2,1,5,6,4}, 1));     // k = 1 is the largest element
    assert(test_kth_largest({3,2,1,5,6,4}, 2));     // typical k
    assert(test_kth_largest({3,2,1,5,6,4}, 6));     // k = size ==> smallest element
    assert(test_kth_largest({1,1,1,5,6,7}, 3));     // duplicates outside top k 
    assert(test_kth_largest({3,2,1,5,5,5}, 3));     // duplicates in top k 
    assert(test_kth_largest({22,22,22,22,22}, 3));  // all duplicates
}

int main(int argc, char** argv) {
    test_kth_largest();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
