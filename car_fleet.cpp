// Leetcode: https://leetcode.com/problems/car-fleet/

// Acceptance: 39.2
// Approach: Generate a tuple (starting_position, speed, arrival time) for each car. Sort tuples by position.
// Iterate right to left merging cars if the i'th car will catch the i+1'th car. Adjust speed of i'th car if it
// catches its neighbor

#include <iostream>
#include <vector>
#include <assert.h>

struct Car {
  int position = 0;
  int speed = 0;
  double arrival_time = 0;
  bool operator<(const Car& other) const { return position < other.position; }
};

// Accepted. 44ms. Faster than 98.67% of cpp submissions.
class Solution {
public:
  int carFleet(int target, const std::vector<int>& position, const std::vector<int>& speed) {
    if (position.empty() || speed.empty()) { return 0; }

    std::vector<Car> cars;
    cars.reserve(position.size());
    for (int i = 0; i < position.size(); ++i) {
      auto arrival_time = double(target - position[i]) / double(speed[i]);
      cars.emplace_back(Car{position[i], speed[i], arrival_time});
    }

    std::sort(cars.begin(), cars.end());
    int num_fleets = cars.size();
    for (int i = cars.size()-2; i >= 0; --i) {
      if (cars[i].arrival_time <= cars[i+1].arrival_time) {
        --num_fleets;
        cars[i].arrival_time = cars[i+1].arrival_time;
      }
    }
    return num_fleets;
  }
};

void test_car_fleet() {
  Solution soln;

  assert(soln.carFleet(10, {0,4,2}, {2,1,3}) == 1);
  assert(soln.carFleet(10, {1,1,1,1,1}, {2,2,2,2,2}) == 1);
  assert(soln.carFleet(10, {1,1,1,1,1}, {2,2,2,2,3}) == 2);
  assert(soln.carFleet(10, {1,1,1,1,1}, {2,2,2,3,3}) == 2);
  assert(soln.carFleet(10, {1,1,1,1,1}, {2,2,2,4,3}) == 2);
  assert(soln.carFleet(10, {10,1,1,1,1}, {2,2,2,4,3}) == 3);
  assert(soln.carFleet(12, {10,8,0,5,3}, {2,4,1,1,3}) == 3);
}

int main(int argc, char** argv) {
  test_car_fleet();
  std::cout << argv[0] + 2 << "...OK!" << std::endl;
  return 0;
}
