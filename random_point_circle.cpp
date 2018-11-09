// Leetcode: https://leetcode.com/problems/generate-random-point-in-a-circle/ 
// Given the radius and x,y co-ordinates of the center of a circle, 
// write a function which generates a uniform random point inside the circle.

// Approach: Use polar co-ordinates and trigonometry.
// Generate a random distance <= radius, and a random angle in radians. These define a point within
// the circle. Use trigonometry (sin/cos) to find the horizontal and vertical distances 
// However, all such points are not equaly likely to be generated!
// A larger circle should contain more points on its circumference than a smaller circle.
// The CDF is actually sqrt(x), and we use that to scale the radius.

#include <vector>
#include <random>
#include <cmath>
#include <iostream>
#include <assert.h>

// Accepted. 116ms. Beats 90.75% of submissions
static const double cPI = 3.14159;
class Solution {
public:
  Solution(double r, double x_center, double y_center):
    x(x_center), y(y_center), radius(r) {
    gen = std::mt19937(rd());
    dist = std::uniform_real_distribution<>(0, 1.0);
  }
  
  std::vector<double> randPoint() {
    auto angle = dist(gen) * 2 * cPI; // in radians
    auto r = radius * std::sqrt(dist(gen)); // smaller radius
    return {x + r*std::cos(angle), y + r*std::sin(angle)};
  }

private:
  double x;
  double y;
  double radius;
  std::random_device rd;  // To obtain a seed for the random number engine
  std::mt19937 gen;
  std::uniform_real_distribution<> dist;
};

int main(int argc, char** argv) {
  return 0;
}
