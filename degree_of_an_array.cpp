// Leetcode: https://leetcode.com/problems/degree-of-an-array/description/
// Given an non-empty array, nums, find the width of the smallest subarray that has the same degree as nums.

// Brute Force: Generate all subarrays, count their degree. O(n^3) time.
// Better: Find the degree of nums, then scan nums tracking the (start,end) span of each element. O(n) time/space.

#include <vector>
#include <unordered_map>
#include <iostream>
#include <assert.h>

typedef struct Span {
    int count = 0;
    int first = -1;
    int last = -1;
} Span;
using SpanMap = std::unordered_map<int, Span>;
using Counts = std::unordered_map<int,int>;

// Accepted: 40ms. Beats 73.84% of submissions.
class Solution {
public:
    int findShortestSubArray(std::vector<int>& nums) {
	int degree = 0;
	Counts counts;
	for (auto num : nums) {
            degree = std::max(degree, ++counts[num]);
        }

	SpanMap span_map;
        int width = nums.size();
	for (int i = 0; i < nums.size(); ++i) {
	    auto& span = span_map[nums[i]];
	    ++span.count;
	    if (span.first == -1) span.first = i;
            span.last = i;
            if (degree == span.count) {
                width = std::min(width, span.last - span.first + 1);
            }
	}
	return width;
    }
};

bool test_degree(std::vector<int> nums, int expected) {
    Solution soln;
    return soln.findShortestSubArray(nums) == expected;
}

void test_degree() {
    assert(test_degree({2}, 1));
    assert(test_degree({2,2}, 2));
    assert(test_degree({2,1,2}, 3));
    assert(test_degree({1,2,2}, 2));
    assert(test_degree({2,2,1}, 2));
    assert(test_degree({1,2,3}, 1));
    assert(test_degree({1,2,3,1}, 4));
    assert(test_degree({1,2,3,2,1}, 3));
    assert(test_degree({1,2,2,3,1}, 2));
    assert(test_degree({1,2,2,3,1,4,2}, 6));
}

int main(int argc, char** argv) {
    test_degree();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
