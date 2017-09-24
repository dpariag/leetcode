// Leetcode: 
// Given a sorted array, two integers k and x, find the subarray of size k whose elements are 
// closest to x. In the event of a tie, return the subarray with smaller values.

// Brute Force: Generate all subarrays, find the closest one of size k. O(n^2) time.
// Better: Use binary search to find where x would lie in the array, then choose the k closest elems.
// O(logn + k) which is O(n) if k approaches n.
// Best: Repeatedly shrink array by discarding (size-k)/2 elements from the array. O(logN) time.

#include <vector>
#include <iostream>
#include <assert.h>

// Accepted. 113ms. Beats 92.26% of submisssions, ties 2.71% of submisssions.
class Solution {
public:
    std::vector<int> findClosestElements(const std::vector<int>& arr, int k, int x) {
        int left = 0, right = int(arr.size()-1);

        while ((right - left + 1) > k) {
            int to_discard = std::max(1, ((right - left + 1) - k) / 2);
            int new_left = left + to_discard;
            int new_right = right - to_discard;

            int left_distance = std::abs(arr[new_left-1] - x);
            int right_distance = std::abs(arr[new_right+1] - x);
            
            if (left_distance <= right_distance) {
                right = new_right;
            } else {
                left = new_left;
            }
        }
        return std::vector<int>(arr.begin()+left, arr.begin()+right+1);
    }
};

bool test_find_closest_elems(std::vector<int> arr, int k, int x, std::vector<int> expected) {
    Solution soln;
    auto result = soln.findClosestElements(arr, k, x);
    for (auto r : result) {
        std::cout << r << " ";
    }
    std::cout << std::endl;
    return result == expected;
}

void test_find_closest_elems() {
    assert(test_find_closest_elems({0,0,0,1,3,5,6,7,8,8}, 2, 2, {1,3}));
    assert(test_find_closest_elems({1,2,3,4,5}, 4, 3, {1,2,3,4}));
    assert(test_find_closest_elems({2,7,11,15,21,22,23,30}, 4, 3, {2,7,11,15}));
    assert(test_find_closest_elems({2,7,11,15,21,22,23,30}, 2, 20, {21,22}));
    assert(test_find_closest_elems({2,7,11,15,21,22,23,30}, 3, -20, {2,7,11}));
    assert(test_find_closest_elems({2,7,11,15,21,22,23,30}, 3, 40, {22,23,30}));
    assert(test_find_closest_elems({2,7,11,15,21,22,23,30}, 1, 11, {11}));
}

int main(int argc, char** argv) {
    test_find_closest_elems();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
