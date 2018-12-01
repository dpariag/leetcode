// Leetcode: https://leetcode.com/problems/fruit-into-baskets/

// Brute Force:
// Better:
// Acceptance: 

#include <iostream>
#include <vector>
#include <assert.h>

// Accepted. 84ms. Faster than 97.44% of submissions.
class Solution {
public:
  int totalFruit(std::vector<int>& tree) {
    // Let's call the two kinds of fruit A and B
    int fruitA = -1, fruitB = -1;
    int numA = 0, numB = 0;
    int consecutiveA = 0, consecutiveB = 0;
    int max = 0;
    for (int i = 0; i < tree.size(); ++i) {
      if (tree[i] == fruitA) {
        ++consecutiveA;
        consecutiveB = 0;
        ++numA;
      } else if (tree[i] == fruitB) {
        ++consecutiveB;
        consecutiveA = 0;
        ++numB;
      } else {
        if (consecutiveA > 0) { 
          fruitB = tree[i];
          numA = consecutiveA, consecutiveA = 0; 
          numB = 1, consecutiveB = 1;
        } else if (consecutiveB > 0) { 
          fruitA = tree[i];
          numB = consecutiveB, consecutiveB = 0;
          numA = 1, consecutiveA = 1; 
        } else {
          fruitA = tree[i];
          numA = 1, consecutiveA = 1;
        }
      }
      max = std::max(max, numA + numB);
    }
    return max;
  }
};

bool test_total_fruit(std::vector<int> tree, int expected) {
  Solution soln;
  return soln.totalFruit(tree) == expected;
}

void test_total_fruit() {
  assert(test_total_fruit({5,9,0,9,6,9,6,9,9,9}, 7));
  assert(test_total_fruit({3,3,3,1,2,1,1,2,3,3,4}, 5));
  assert(test_total_fruit({1,2,3,2,2}, 4));
  assert(test_total_fruit({1,2,1}, 3));
  assert(test_total_fruit({0,1,2,2}, 3));
}

int main(int argc, char** argv) {
  test_total_fruit();
  std::cout << argv[0] + 2 << "...OK!" << std::endl;
  return 0;
}
