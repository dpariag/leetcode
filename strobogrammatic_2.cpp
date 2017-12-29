// Leetcode: https://leetcode.com/problems/strobogrammatic-number-ii/description/
// A strobogrammatic number looks the same when rotated 180 degrees (looked at upside down).
// Find all strobogrammatic numbers that are of length n.

// Brute Force: Iterate the numbers from 1 to n and check if each is strobogrammatic. O(10^n) time
// Better: Generate strobogrammatic numbers of length n from numbers of length (n-2). Let 'x' be a
// number of length (n-2), then 1x1, 8x8, 6x9, 9x6 are all strobogrammatic numbers. 0x0 is a special case. O(4^n) time/space

#include <vector>
#include <string>
#include <iostream>
#include <assert.h>

// Accepted. 19ms. Beats 65.40% of submissions, ties 27.00% of submissions.
class Solution {
public:
    std::vector<std::string> get_strobogrammatic(int n) {
        if (n == 0) { return {""}; }
        if (n == 1) { return {"0", "1", "8"}; }
        if (n == 2) { return {"00", "11", "69", "88", "96"}; }

        std::vector<std::string> result;
        auto numbers = get_strobogrammatic(n-2);
        std::vector<std::pair<char,char>> digit_pairs = {{'0','0'},{'1','1'},{'6','9'},{'8','8'},{'9','6'}};

        for (auto& pair : digit_pairs) {
            for (auto& number : numbers) {
                std::string new_number(1, pair.first);
                new_number.append(number);
                new_number.append(1, pair.second);
                result.emplace_back(std::move(new_number));
            }
        }
        return result;
    }

    std::vector<std::string> findStrobogrammatic(int n) {
        if (n == 1) { return {"0", "1", "8"}; }
        auto result = get_strobogrammatic(n);
        int i = 0;
        while (i < result.size()) {
            if (result[i].front() == '0') {
                std::swap(result[i], result.back());
                result.pop_back();
            }
            ++i;
        }
        return result;
    }
};

bool test_strobogrammatic(int n, std::vector<std::string> expected) {
    Solution soln;
    auto result = soln.findStrobogrammatic(n);
    std::sort(result.begin(), result.end());
    std::sort(expected.begin(), expected.end());
    return result == expected;
}

void test_strobogrammatic() {
    assert(test_strobogrammatic(0, {""}));
    assert(test_strobogrammatic(1, {"0", "1", "8"}));
    assert(test_strobogrammatic(2, {"11", "88", "69", "96"}));
    assert(test_strobogrammatic(3, {"101", "808", "609", "906", "111","181","818","888","619","916","689","986"}));
}

int main(int argc, char** argv) {
    test_strobogrammatic();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
