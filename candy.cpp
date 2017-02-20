// Leetcode: https://leetcode.com/problems/candy/?tab=Description
// There are N children standing in a line. Each child is assigned a rating value.
// Give candies to each child so that children with a higher rating get more candies than 
// their neighbors.  What is the minimum candies you must give?

// Brute Force:
// Better: A two-pass algorithm (left-to-right, then right-to-left) comparing each child to its
// predecessor, and adjusting their candy assignment if needed. O(n) time and space.

#include <vector>
#include <iostream>
#include <numeric>
#include <assert.h>

// Accepted. 26ms. Beats 78.13% of accepted submissions, ties 20.66% of submissions.
class Solution {
public:
    int candy(const std::vector<int>& ratings) {
        int num_candies = ratings.size();
        std::vector<int> candies(ratings.size(), 1); // all kids start with one candy

        // Left to right pass, comparing each child to their left neighbour.
        for (auto i = 1; i < ratings.size(); ++i) {
            if (ratings[i] > ratings[i-1]) {
                num_candies += (candies[i-1] + 1) - candies[i];
                candies[i] = candies[i-1] + 1;
            }
        }

        // Right to left pass, comparing each child to their right neighbour.
        for (int i = ratings.size() - 2; i >= 0; --i) {
            if (ratings[i] > ratings[i+1]) {
                auto prev = candies[i];
                candies[i] = std::max(candies[i], candies[i+1] + 1);
                num_candies += candies[i] - prev;
            }
        } 
        return num_candies;
    }
};

void test_candy() {
    Solution soln;
    assert(soln.candy({}) == 0);
    assert(soln.candy({1,1,1,1,1,1,1}) == 7);
    assert(soln.candy({1,1,2,3,4,2,1}) == 14);
    assert(soln.candy({11,1,2,3,4,2,11}) == 15);
}

int main(int argc, char** argv) {
    test_candy();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
