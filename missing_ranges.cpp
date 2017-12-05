// Leetcode: https://leetcode.com/problems/missing-ranges/description/
// Given a sorted integer array whose elements are in the inclusive range [lower, upper], return its missing ranges.
// Example: Given [0, 1, 3, 50, 75], lower = 0 and upper = 99, return ["2", "4->49", "51->74", "76->99"].

// Approach: Scan the array looking for gaps between consecutive elements. Treat endpoints specially. O(n) time.

#include <vector>
#include <iostream>
#include <assert.h>

using Ranges = std::vector<std::string>;

// Accepted. 0ms. Beats 15.34% of submissions, ties 84.66% of submissions.
class Solution {
public:
    inline std::string make_range(int64_t start, int64_t end) {
        std::string range;
        if (start == end) {
            range = std::to_string(start);
        } else if (start < end) {
            range.append(std::to_string(start));
            range.append("->");
            range.append(std::to_string(end));
        }
        return range;
    }

    Ranges findMissingRanges(const std::vector<int>& nums, int lower, int upper) {
        if (nums.empty()) { return Ranges({make_range(lower, upper)});}

        Ranges missing;
        
        auto start_range = make_range(lower, int64_t(nums.front())-1);
        if (!start_range.empty()) { missing.emplace_back(std::move(start_range)); }

        for (int i = 0; i+1 < nums.size(); ++i) {
            auto range = make_range(int64_t(nums[i])+1, int64_t(nums[i+1])-1);
            if (!range.empty()) { missing.emplace_back(std::move(range)); }
        }

        auto end_range = make_range(int64_t(nums.back())+1, upper);
        if (!end_range.empty()) { missing.emplace_back(std::move(end_range)); }
        
        return missing;
    }
};

void test_missing_ranges() {
    Solution soln;

    assert(soln.findMissingRanges({}, 1, 10) == Ranges({"1->10"}));
    assert(soln.findMissingRanges({1,10}, 1, 10) == Ranges({"2->9"}));
    assert(soln.findMissingRanges({1,2,3,4,5}, 1, 5) == Ranges({}));
    assert(soln.findMissingRanges({0,1,3,50,75}, -1, 75) == Ranges({"-1", "2", "4->49", "51->74"}));
    assert(soln.findMissingRanges({0,1,3,50,75}, -1, 75) == Ranges({"-1", "2", "4->49", "51->74"}));
    assert(soln.findMissingRanges({0,1,3,50,75}, 0, 75) == Ranges({"2", "4->49", "51->74"}));
    assert(soln.findMissingRanges({0,1,3,50,75}, 0, 99) == Ranges({"2", "4->49", "51->74", "76->99"}));
    assert(soln.findMissingRanges({2147483647}, 0, 2147483647) == Ranges({"0->2147483646"}));
}


int main(int argc, char** argv) {
    test_missing_ranges();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
