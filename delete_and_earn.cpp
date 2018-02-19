// Leetcode: https://leetcode.com/problems/delete-and-earn/description/
// Given an integer array, you can pick nums[i] to earn nums[i] points. 
// Afterwards, you must delete every element equal to nums[i]-1 or nums[i]+1. 
// Return the max points that can be earned.

// Brute Force: Choose each nums[i], then delete nums[i]-1, nums[i]+1 and recurse. O(n!) time.
// Better: Calculate the points available from each unique value, sort (value, points) pairs,
// then use dynamic programming. O(n*logn) time.

#include <vector>
#include <unordered_map>
#include <iostream>
#include <assert.h>

struct Item {
	int key = 0;
	int points = 0;
	Item(){}
	Item(int k, int p): key(k), points(p) {}
};

using Counts = std::unordered_map<int, int>; // value -> its count

// Accepted. 9ms. No runtime distribution data available
class Solution {
public:
    int deleteAndEarn(std::vector<int>& nums) {
    	if (nums.empty()) { return 0; }

        Counts counts;
        for (int i = 0; i < nums.size(); ++i) {
        	counts[nums[i]] += nums[i];
        }

        std::vector<Item> items;
        items.emplace_back(-2, 0);
        items.emplace_back(-1, 0);
        for (auto& c : counts) {
        	items.emplace_back(Item(c.first, c.second));
        }

        std::sort(items.begin(), items.end(), [](const Item& i1, const Item& i2){return i1.key < i2.key; });
        for (int i = 2; i < items.size(); ++i) {
        	int choice1 = 0, choice2 = 0;
        	if (items[i].key == items[i-1].key + 1) {
        		choice1 = std::max(items[i].points + items[i-2].points, items[i-1].points);
        	} else {
        		choice2 = items[i].points + items[i-1].points;
        	}
        	items[i].points = std::max(choice1, choice2);
        }
        return items.back().points;
    }
};

bool test_points(std::vector<int> nums, int expected) {
	Solution soln;
	return soln.deleteAndEarn(nums) == expected;
}

void test_points() {
	assert(test_points({}, 0));
	assert(test_points({11}, 11));
	assert(test_points({3,4,2}, 6));
	assert(test_points({11,11}, 22));
	assert(test_points({11,11,13}, 35));
	assert(test_points({11,11,12}, 22));
	assert(test_points({11,11,12,12}, 24));
	assert(test_points({2,2,3,3,3,4}, 9));
	assert(test_points({10,12,14}, 36));
	assert(test_points({2,2,3,3,3,4,4,4,5,5,5}, 24));
	assert(test_points({1,1,1,2,4,5,5,5,6}, 18));
	assert(test_points({8,3,4,7,6,6,9,2,5,8,2,4,9,5,9,1,5,7,1,4}, 61));
	assert(test_points({3,7,10,5,2,4,8,9,9,4,9,2,6,4,6,5,4,7,6,10}, 66));
}

int main(int argc, char** argv) {
	test_points();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}