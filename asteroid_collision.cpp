// Leetcode: https://leetcode.com/problems/asteroid-collision/description/

// Brute Force: Repeatedly sweep the array looking for +- collisions. O(n^2) time.
// Better: Use a stack to track the unexploded asteroids. O(n) time and space.

#include <iostream>
#include <vector>
#include <assert.h>

using Asteroids = std::vector<int>;

// Accepted. 12ms. Beats 99.00% of cpp submissions.
class Solution {
public:
    Asteroids asteroidCollision(const Asteroids& asteroids) {
        Asteroids result;
        for (auto a : asteroids) {
            if (result.empty() ||
                (a < 0 && result.back() < 0) ||
                (a > 0 && result.back() > 0) ||
                (a > 0 && result.back() < 0)) {
                result.push_back(a);
            } else {
                // + - results in a crash
                bool a_exploded = false;
                while (!result.empty() && result.back() > 0) {
                    a_exploded = (result.back() >= std::abs(a));
                    if (result.back() <= std::abs(a)) { result.pop_back(); }
                    if (a_exploded) break; 
                }
                if (!a_exploded) { result.push_back(a); }
            }
        }
        return result;
    }
};

bool test_asteroid_collision(Asteroids input, Asteroids expected) {
    Solution soln;
    return soln.asteroidCollision(input) == expected;
}

void test_asteroid_collision() {
    assert(test_asteroid_collision({-2,-2,1,-2}, {-2,-2,-2}));
    assert(test_asteroid_collision({10,2,-5}, {10}));
    assert(test_asteroid_collision({8,-8}, {}));
    assert(test_asteroid_collision({-8,8}, {-8,8}));
    assert(test_asteroid_collision({-8,8}, {-8,8}));
    assert(test_asteroid_collision({10,6,3,-5,-6}, {10}));
}

int main(int argc, char** argv) {
    test_asteroid_collision();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
