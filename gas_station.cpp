// Leetcode: https://leetcode.com/problems/gas-station/description/
// N gas stations lie on a circular route. Each station has gas[i] gas, and it costs cost[i] to get
// to the next station. You have a car with an unlimited gas tank. Return the starting gas 
// station's index if it is possible to travel the entire circuit once, otherwise return -1

// Brute Force: Start at every station, try to complete the circle. O(n^2) time.
// Better: Traverse the circle, try starting at any station where gas[i] >= cost[i]. If the car's 
// tank becomes empty then the last starting station is not viable. Sum gas[i] and cost[i] 
// since there must be enough gas across all stations to complete the journey. O(n) time.

#include <vector>
#include <iostream>
#include <assert.h>

// Accepted. 6ms. Beats 25.27% of submissions, ties 74.63% of submissions.
class Solution {
public:
    int canCompleteCircuit(const std::vector<int>& gas, const std::vector<int>& cost) {
        int total_gas = 0, total_cost = 0, gas_tank = 0;
        int starting_station = -1;
        for (int i = 0; i < gas.size(); ++i) {
            total_gas += gas[i];
            total_cost += cost[i];
            auto delta = (gas[i] - cost[i]);
            
            if (starting_station < 0 && delta >= 0) {
                starting_station = i;
                gas_tank = delta;
            } else if (starting_station >= 0) {
                gas_tank += delta;
                if (gas_tank < 0) {
                    starting_station= -1;
                }
            }
        }
        return (total_gas >= total_cost) ? starting_station : -1; 
    }
};

void test_gas_station() {
    Solution soln;
    assert(soln.canCompleteCircuit({5},{5}) == 0);
    assert(soln.canCompleteCircuit({10},{5}) == 0);
    assert(soln.canCompleteCircuit({4},{5}) == -1);
    assert(soln.canCompleteCircuit({10,15,15,10,20},{12,16,10,5,10}) == 2);
    assert(soln.canCompleteCircuit({1,2,3,4,5},{3,4,5,1,2}) == 3);
}

int main(int argc, char** argv) {
    test_gas_station();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
