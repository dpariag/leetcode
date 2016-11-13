// Leetcode: https://leetcode.com/problems/intersection-of-two-arrays/
// Compute the intersection of two arrays (unordered, no duplicates).
// Example: Given nums1 = {1, 2, 2, 1} and nums2 = {2, 2}, return {2}.

// Brute Force: For each nums1[i], scan nums2 to see if it exists there. O(m*n) time.
// Better: Sort the arrays and then perform a merge, saving common elements.
// O(n*logn) + O(m*logm) + O(m+n) time and O(1) space.
// Better: Store one array in a hash_map, iterate the other array building the intersection.
// O(n+m) time and O(n) space.

#include <vector>
#include <iostream>
#include <unordered_set>
#include <assert.h>

using Numbers = std::vector<int>;

// Accepted. 9ms. Beats 61.41% of submissions and ties 35.40% of submissions.
class Solution {
public:
    Numbers intersection(Numbers& nums1, Numbers& nums2) {
        Numbers intersection;
        std::unordered_set<int> set;

        // Store unique elements from nums1
        for (auto n : nums1) {
            set.emplace(n);
        }

        // Iterate nums2, storing common elements (once per element)
        for (auto n : nums2) {
            auto found = set.find(n);
            if (found != set.end()) {
                intersection.emplace_back(*found);
                set.erase(found);
            }
        }
        return intersection;
    }
};

bool test_intersection(Numbers nums1, Numbers nums2, Numbers expected_intersection) {
    Solution soln;
    auto intersection = soln.intersection(nums1, nums2);

    std::sort(intersection.begin(), intersection.end());
    std::sort(expected_intersection.begin(), expected_intersection.end());
    return intersection == expected_intersection;
}

void test_intersection() {
    assert(test_intersection({},{},{}));
    assert(test_intersection({1},{},{}));
    assert(test_intersection({},{1},{}));
    assert(test_intersection({1,2,2,1},{2},{2}));
    assert(test_intersection({1,2,2,1},{2,2},{2}));
    assert(test_intersection({1,1,3,6,7},{2,2},{}));
    assert(test_intersection({1,2,3,4},{1,2,3,4},{1,2,3,4}));
}

int main(int argc, char** argv) {
    test_intersection();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
