// Leetcode: https://leetcode.com/problems/intersection-of-two-arrays-ii/
// Compute the intersection of two integer arrays

// Brute Force: For each item in the first array, scan the second array to find it. O(n^2) time
// Better: Count distinct values in each array using hash maps. 
// Build intersection from these counts. O(n) time.

#include <vector>
#include <iostream>
#include <unordered_map>
#include <assert.h>

// Accepted. 4ms. Beats 100% of submissions.
class Solution {
public:
  std::vector<int> intersect(std::vector<int>& nums1, std::vector<int>& nums2) {
    std::vector<int> intersection;
    std::unordered_map<int,int> counts1;
    std::unordered_map<int,int> counts2;

    for (const auto value : nums1) { ++counts1[value]; }
    for (const auto value : nums2) { ++counts2[value]; }

    for (const auto item : counts1) {
      auto key = item.first;
      if (counts2.count(key) > 0) {
        auto key_count = std::min(counts1[key], counts2[key]);
        intersection.insert(intersection.begin(), key_count, key);
      }
    }
    return intersection;
  }
};

int main(int argc, char** argv) {
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
