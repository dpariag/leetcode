// Leetcode: https://leetcode.com/problems/statistics-from-a-large-sample/

// Brute Force: Recreate the sample and then calculate aggregate statistics. O(n) time and space.
// Better: Use the summary information to calculate statisitics. O(1) time and space.
// Acceptance: 44.9

#include <cmath>
#include <iostream>
#include <vector>
#include <assert.h>

// Accepted 0ms. Faster than 100% of C++ submissions.
class Solution {
public:
  std::vector<double> sampleStats(std::vector<int>& count) {
    int64_t min = 256, max = -1, sum = 0, num_elems = 0, mode = -1;
    for (int i = 0; i < count.size(); ++i) {
      if (count[i] > 0) {
        max = i;
        if (i < min) min = i;
        sum += (i * count[i]);
        num_elems += count[i];
        if (mode == -1 || count[i] > count[mode]) mode = i;
      }
    }
    double mean = double(sum) / double(num_elems);
    int pos = 0, median_pos = num_elems / 2;
    bool even = (num_elems % 2) == 0;
    double median = -1.0;
    for (int i = 0; i < count.size(); ++i) {
      pos += count[i];
      if (pos >= median_pos) {
        median = i;
        if (even && pos == median_pos) {
          median = (double(i) + double(i+1)) / 2;  
        }
        break;
      } 
    } 
    return {double(min), double(max), mean, median, double(mode)};
  }
};

// Test the returned statistics against the expected ones - within some delta
bool test_sample(std::vector<int> count, std::vector<double> expected) {
  Solution soln;
  auto result = soln.sampleStats(count);
  for (int i = 0; i < result.size(); ++i) {
    if (std::fabs(double(result[i] - expected[i])) >= 0.00001) return false;
  }
  return true;
}

void test_sample() {
  assert(test_sample({0,4,3,2,2,0,0}, {1.00000,4.00000,2.18182,2.00000,1.00000}));
  assert(test_sample({0,1,3,4,0,0,0,0,0,0}, {1.00000,3.00000,2.37500,2.50000,3.00000}));
}

int main(int argc, char** argv) {
  test_sample();
  std::cout << argv[0] + 2 << "...OK!" << std::endl;
  return 0;
}
