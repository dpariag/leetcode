// Leetcode:  
// Given k integer arrays (sorted in ascending order), find the smallest interval [a,b] that includes
// at least one number from each of the k arrays.

// Brute Force: Start with the range formed by arrays[i][0] for i = 0...k-1, then advance the min
// min element in the range. O(n*k)
// Better: Use a binary tree (std::map) to locate the minimum element. O(n*logk)

#include <map>
#include <vector>
#include <iostream>
#include <assert.h>

using Array = std::vector<int>;
using Arrays = std::vector<Array>;

struct Elem {
    int array = -1;
    int index = -1;
    Elem(int a, int i): array(a), index(i) {}
};

// Accepted. 52ms. Beats 49.56% of submissions, ties 11.26% of submissions.
class Solution {
public:
    Array smallestRange(const Arrays& nums) {
        std::multimap<int, Elem> range; // allow duplicates
        int smallest_max = std::numeric_limits<int>::max();

        for (int i = 0; i < nums.size(); ++i) {
            range.emplace(std::make_pair(nums[i][0], Elem(i, 0)));
            smallest_max = std::min(smallest_max, nums[i].back());
        }
        
        Array smallest_range({range.begin()->first, (--range.end())->first});
        auto smallest_range_size = smallest_range[1] - smallest_range[0];
        auto cur_range = smallest_range; 
        
        while (range.size() > 1) {
            auto smallest = range.begin()->second;
            range.erase(range.begin());
            if (smallest.index + 1 < nums[smallest.array].size()) {
                range.emplace(std::make_pair(nums[smallest.array][smallest.index+1], 
                                             Elem(smallest.array, smallest.index+1)));
            } 
            cur_range[0] = range.begin()->first;
            cur_range[1] = (--range.end())->first;
            if (cur_range[0] > smallest_max) { break; }

            auto cur_range_size = cur_range[1] - cur_range[0];
            if (cur_range_size < smallest_range_size ||
                (cur_range_size == smallest_range_size && cur_range[0] < smallest_range[0])) {
                smallest_range = cur_range;
                smallest_range_size = cur_range_size;
            }
        }
        return smallest_range;
    }
};

void test_smallest_range() {
    Solution soln;

    assert(soln.smallestRange({{1,1,1}}) == Array({1,1}));
    assert(soln.smallestRange({{1,1,1},{7}}) == Array({1,7}));
    assert(soln.smallestRange({{1,1,1},{1,1,1}}) == Array({1,1}));
    assert(soln.smallestRange({{1,1,1},{2,2}}) == Array({1,2}));
    assert(soln.smallestRange({{1,1,1},{2,2,2}}) == Array({1,2}));
    assert(soln.smallestRange({{1,2,4},{2,4,6}}) == Array({2,2}));
    assert(soln.smallestRange({{1,2,3},{1,2,3},{1,2,3}}) == Array({1,1}));
    assert(soln.smallestRange({{4,10,15,24,26},{0,9,12,20}, {5,18,22,30}}) == Array({20,24}));
}

int main(int argc, char** argv) {
    test_smallest_range();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
