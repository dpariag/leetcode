// Leetcode: https://leetcode.com/problems/shuffle-an-array/description/
// Shuffle a set of numbers without duplicates.

// Brute Force: Generate all permutations of the array and return one at random.
// Better: Generate one random permutation. For result[i], choose one of the remaining
// (n - i) elements and swap it into result[i]. O(n) time and space.

#include <vector>
#include <random>
#include <ctime>
#include <iostream>
#include <assert.h>

// Accepted. 236ms. Beats 52.37% of submissions, ties
class Solution {
public:
    Solution(std::vector<int> nums): m_nums(nums) {}

    /** Resets the array to its original configuration and return it. */
    std::vector<int> reset() {
        return m_nums;
    }

    /** Returns a random shuffling of the array. */
    std::vector<int> shuffle() {
        std::vector<int> result(m_nums);
        int sz = result.size();
        for (int i = 0; i < sz; ++i) {
            // Pick a value for result[i]
            int target = i + std::rand() % (sz - i);
            std::swap(result[i], result[target]);
        }
        return result;
    }
private:
    std::vector<int> m_nums;
};

int main(int argc, char** argv) {
    std::srand(std::time(nullptr));
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
