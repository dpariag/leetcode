// Leetcode: https://leetcode.com/problems/top-k-frequent-elements/description/
// Given a non-empty array of integers, return the k most frequent elements.

// Brute Force: For each element in the array, scan the array to get its count.
// Store counts in a second array, sort that and return the top K values. O(n^2) time.
// Better: Count unique values in a hash map, then use selection rank on the aggregated counts.
// O(n) expected time.

#include <ctime>
#include <random>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <iostream>
#include <assert.h>

using ItemCounts = std::vector<std::pair<int,int>>; // (item, count)

// Accepted. 19ms. Beats 99.60% of submissions.
class Solution {
public:

    int partition(ItemCounts& item_counts, int pivot_idx, int start, int end) {
        int read = start, write = start;
        std::swap(item_counts[pivot_idx], item_counts[end]);
        int pivot_count = item_counts[end].second;

        while (read < end) {
            if (item_counts[read].second <= pivot_count) {
                std::swap(item_counts[write], item_counts[read]);
                ++write;
            }
            ++read;
        }
        std::swap(item_counts[write], item_counts[end]);
        return write;
    }

    void selection_rank(ItemCounts& item_counts, int k) {
        int start = 0, end = item_counts.size()-1;

        while (start <= end) {
            int pivot_idx = start + (std::rand() % (end-start+1));
            pivot_idx = partition(item_counts, pivot_idx, start, end);

            if (pivot_idx == k-1) {
                return;
            } else if (pivot_idx < k-1) {
                start = pivot_idx + 1;
            } else {
                end = pivot_idx - 1;
            }
        }
    }

    std::vector<int> topKFrequent(std::vector<int>& nums, int k) {
        std::unordered_map<int,int> counts(nums.size()*2);
        for (auto num : nums) { ++counts[num]; }

        ItemCounts item_counts(counts.begin(), counts.end());
        selection_rank(item_counts, item_counts.size() - k);

        std::vector<int> result(k, 0);
        for (int i = 0; i < k; ++i) {
            result[i] = item_counts.back().first;
            item_counts.pop_back();
        }
        return result;
    }
};

bool test_top_k_frequent(std::vector<int> nums, int k, std::vector<int> expected) {
    Solution soln;
    auto top_k = soln.topKFrequent(nums, k);

    std::sort(top_k.begin(), top_k.end());
    std::sort(expected.begin(), expected.end());
    return top_k == expected;
}

void test_top_k_frequent() {
    assert(test_top_k_frequent({3,0,1,0}, 1, {0}));
    assert(test_top_k_frequent({4}, 1, {4}));
    assert(test_top_k_frequent({2,2,2,2}, 1, {2}));
    assert(test_top_k_frequent({2,2,3,1,1,1}, 1, {1}));
    assert(test_top_k_frequent({1,1,1,2,2,3}, 2, {1,2}));
    assert(test_top_k_frequent({2,2,1,1,1,3}, 2, {1,2}));
    assert(test_top_k_frequent({2,2,3,1,1,1}, 2, {1,2}));
    assert(test_top_k_frequent({1,2,3,1,2,1}, 2, {1,2}));    
    assert(test_top_k_frequent({2,2,3,1,1,1}, 3, {1,2,3}));
    assert(test_top_k_frequent({2,2,3,3,1,1,1,4,5,6}, 3, {1,2,3}));
    assert(test_top_k_frequent({-5,-9,67,-10,4,-57,47,13,-67,-26,-57,63,38,-68,62,
                                -45,-37,95,49,-91,-53,-42,-33,80,78,-30,-36,22,9,
                                -86,79,-1,44,-92,30,-68,-94,58,-51,-26,-38,5,-74,25,
                                71,-93,52,-12,-86,7,-86,53,78,-31,-5,-87,88,-98,-39,
                                9,99,23,96,-90,51,-64,35,-73,9,60,-78,70,99,14,70,71,
                                -78,50,7,46,-89,57,-1,87,-87,-95,48,49,79,-54,31,28,
                                -27,75,31,-76,-12,35,40,-90,-60,-60,-7,67,73,-34,-42,
                                -35,61,51,18,95,16,78,-81,-91,-30,92,57,-79,5,41,29,72,
                                -62,-47,80,29,1,-21,-36,5,82,4,-12,-52,-56,-47,-68,95,
                                85,-87,-7,-12,98,75,-64,-93,11,73,-81,-9,-12,-9,51,17,
                                -94,33,-9,57,-35,10,-17,87,-18,-55,-52,30,-62,73,35,-74,
                                -47,-63,77,-72,-55,5,73,21,14,7,-65,-51,-55,-49,98,-20,
                                -22,-68,34,-20,92,55,47,-20,6,-54,-12,3,75,69,60,15,88,
                                64,2,-27,-50,55,73,46,-15,-64,93,-47,-75,-55,-75,21,-57,
                                91,-12,-99,-68,-56,-14,-4,-77,-94,55,93,-31,68,-12,-23,59,
                                -56,-86,43,83,-93,-78,-11,-7,96,-3,-87,-37,19,-78,67,-29,77,
                                -28,91,-73,-68,-22,18,-7,3,15,77,99,31,-48,-86,-45,-82,52,
                                -39,8,-88,-83,-58,-77,5,87,-61,50,32,-66,-36,60,-53,52,70,
                                -36,-1,83,-56,33,98,-80,28,1,-21,-50,-60,44,99,18,83,-29,83,
                                -36,-55,-6,96,-60,61,75,6,-57,2,82,62,-27,36,60,72,92,61,-65,79,
                                -57,-34,-23,-28,-55,53,36,-80,5,-76,64,-81,-32,-43,-1,50,-16,
                                -72,-74,22,88,28,-79,-99,85,-13,-34,-76,85,6,21,-99,10,-46,79,
                                11,-70,17,47,-22,-62,0,6,75,-19,57,-25,-52,-83,90,21,95,52,68,
                                47,-12,76,-9,-65,86,90,16,74,64,26,84,64,-42,97,-72,53,-76,11,89,
                                -62,67,100,15,53,68,-16,24,11,-77,20,59,-95,-50,-20,27,45,94,13,
                                -93,86,49,12,19,17,-33,-52,-28,71,79,-19,-73,40,-99,83,77,19,
                                -20,98,86,-5,-5,73,18,100,73,-45,33,3,89,32,-53,73,16,-3,-26,
                                -80,49,-78,67,31,1,-85,-44,-91,-68,75,-74,95,23,89,99,-84,54,
                                -93,68,0,-41,66,-15,-27,-23,-9,-68,37,45,-69,57,80,10,-64,35,
                                26,55,-67,31,-76,36,-99,21}, 
                                7, {-12,-68,73,-55,-9,75,5}));
}

int main(int argc, char** argv) {
    std::srand(std::time(0));
    test_top_k_frequent();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}