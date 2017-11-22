// Leetcode: https://leetcode.com/problems/k-empty-slots/description/
// Given an flower bed with N spots (1..N), flowers[i] = j denotes that on the i'th day, the j'th
// flower will bloom (and stay in bloom thereafter). Given an integer k, determine if there is a
// day where two flowers are in bloom with k empty spots between them.

// Brute Force:
// Better:

#include <vector>
#include <unordered_map>
#include <iostream>
#include <assert.h>

using FlowerToDays = std::unordered_map<int, int>;

class Solution {
public:
    int kEmptySlots(const std::vector<int>& flowers, int k) {
        FlowerToDays days(flowers.size()*2);

        for (int i = 0; i < flowers.size(); ++i) {
            days[flowers[i]] = i+1;
        }
         
        int left_day = 0;
        int target_flower, target_day = std::numeric_limits<int>::max();
        for (int flower = 1; flower <= flowers.size(); ++flower) {
            int bloom_day = days[flower];
            std::cout << "target_day = " << target_day << std::endl;
            std::cout << "flower = " << flower << " blooms on day " << bloom_day << std::endl;
            if (bloom_day < target_day) {
                target_flower = flower + k + 1;
                target_day = days[target_flower];
                left_day = bloom_day;
                std::cout << "new target flower = " << target_flower << " target_day = " << target_day << std::endl;
            } else if (bloom_day == target_day) {
                std::cout << "Found the gap on day " << bloom_day << std::endl;
                return std::max(bloom_day , left_day);
            }
            std::cout << std::endl;
        }
        std::cout << "NO GAP!" << std::endl;
        return -1;
    }
};

void test_k_empty_slots() {
    Solution soln;

    assert(soln.kEmptySlots({3,9,2,8,1,6,10,5,4,7}, 1) == 6);
    assert(soln.kEmptySlots({1,2,3}, 1) == -1);
    assert(soln.kEmptySlots({1,3,2}, 1) == 2);
    assert(soln.kEmptySlots({6,5,8,9,7,1,10,2,3,4}, 2) == 8);

}


int main(int argc, char** argv) {
    test_k_empty_slots();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
