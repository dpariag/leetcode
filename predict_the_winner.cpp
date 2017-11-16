// Leetcode: https://leetcode.com/problems/predict-the-winner/description/
// Given an non-negative array of integer scores, players alternate choosing a number from either
// end of the array. Chosen numbers are removed, and play continues until all scores are chosen.  
// Given an array of scores, determine if player1 can win, assuming both players play optimally.

// Brute Force: Choose left score, recurse. Choose right score, recurse. Pick better of left,right.
// O(2^n) time and O(n) space.
// Better: Memoize the recursion. Alternatively, build a DP table where table[start][end] represents
// the best score differential for when starting with scores[start..end]. O(n^2) time/space.

#include <vector>
#include <iostream>
#include <limits>
#include <assert.h>

using Cache = std::vector<std::vector<int>>;
static const int min_int = std::numeric_limits<int>::min();

// Accepted. 3ms. Beats 29.29% of submissions, ties 65.13% of submissions.
class RecursiveSolution {
public:
    // Return the best possible score difference possible on the subarray nums[start...end]
    int predict_winner(const std::vector<int>& nums, int start, int end, Cache& cache) {
        if (start == end) { return nums[start]; }
       
        if (cache[start][end] != min_int) { return cache[start][end]; } 
        // choose left, then choose right. Return the highest score possible
        auto opp_left = predict_winner(nums, start+1, end, cache);
        auto opp_right = predict_winner(nums, start, end-1, cache);
        cache [start][end] = std::max(nums[start] - opp_left, nums[end] - opp_right);
        return cache[start][end];
    }

    bool PredictTheWinner(const std::vector<int>& nums) {
        Cache cache(nums.size(), std::vector<int>(nums.size(), min_int));
        return predict_winner(nums, 0, nums.size() - 1, cache) >= 0;
    }
};

// Accepted. 0ms. Beats 94.53% of submissions, ties. 5.47% of submissions.
class IterativeSolution {
public:
    bool PredictTheWinner(const std::vector<int>& nums) {
        std::vector<std::vector<int>> table(nums.size(), std::vector<int>(nums.size(), min_int));

        // Iterate diagonals of decreasing length
        for (int diag = 0; diag < nums.size(); ++diag) {
            int diag_length = nums.size() - diag;
            for (int start = 0; start < diag_length; ++start) {
                int end = start + diag; 
                if (start == end) {
                    table[start][end] = nums[start];
                } else {
                    auto play_left = nums[start] - table[start+1][end];
                    auto play_right = nums[end] - table[start][end-1];
                    table[start][end] = std::max(play_left, play_right);
                } 
            }
        }
        return table.front().back() >= 0;
    }
};

template <typename Solution>
void test_predict_winner() {
    Solution soln;
    assert(soln.PredictTheWinner({1}) == true);
    assert(soln.PredictTheWinner({1,5,2}) == false);
    assert(soln.PredictTheWinner({1,5,233,7}) == true);
}

int main(int argc, char** argv) {
    test_predict_winner<RecursiveSolution>();
    test_predict_winner<IterativeSolution>();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
