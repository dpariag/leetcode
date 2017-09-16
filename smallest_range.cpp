// Leetcode:  
// Given k integer arrays (sorted in ascending order), find the smallest interval [a,b] that includes
// at least one number from each of the k lists.

// Brute Force:
// Better:

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

class Solution {
public:
    Array smallestRange(const Arrays& nums) {
        std::map<int, Elem> range;

        for (int i = 0; i < nums.size(); ++i) {
            range.emplace(std::make_pair(nums[i][0], Elem(i, 0)));
        }
        
        Array smallest_range({range.begin()->first, (--range.end())->first});
        auto smallest_range_size = smallest_range[1] - smallest_range[0];
        auto cur_range = smallest_range; 
        
        while (true) {
            auto smallest = range.begin()->second;
            if (smallest.index + 1 == nums[smallest.array].size()) { break; }
            range.erase(range.begin());
            range.emplace(std::make_pair(nums[smallest.array][smallest.index+1], 
                                         Elem(smallest.array, smallest.index+1)));
            cur_range[0] = range.begin()->first;
            cur_range[1] = (--range.end())->first;
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
    assert(soln.smallestRange({{4,10,15,24,26},{0,9,12,20}, {5,18,22,30}}) == Array({20,24}));
}



int main(int argc, char** argv) {
    test_smallest_range();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
