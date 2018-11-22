// Leetcode: https://leetcode.com/problems/kth-largest-element-in-a-stream/
// Design a class to find the k'th largest number in a stream

// Brute Force: Maintain a sorted array. O(n) add operation.
// Better: Use a min-heap. O(logK) add operation

#include <vector>
#include <queue>
#include <iostream>
#include <assert.h>

using MinHeap = std::priority_queue<int, std::vector<int>, std::greater<int>>;

// Accepted. 28ms. Beats 98.16% of submissions.
class KthLargest {
public:
  KthLargest(int k, const std::vector<int>& nums): k(k), min_heap(nums.begin(), nums.end()) {
    while(min_heap.size() > k) { min_heap.pop(); }
  }

  int add(int val) {
    if (min_heap.size() < k) {
      min_heap.emplace(val);
    } else if (val > min_heap.top()) {
      min_heap.pop();
      min_heap.emplace(val);
    }
    return min_heap.top();
  }
private:
  int k;
  MinHeap min_heap;
};

void test_kth_largest() {
  KthLargest kth(3, {4,5,8,2});
  assert(kth.add(3) == 4);
  assert(kth.add(5) == 5);
  assert(kth.add(10) == 5);
  assert(kth.add(9) == 8);
  assert(kth.add(4) == 8);
   
}

int main(int argc, char** argv) {
  test_kth_largest();
  std::cout << argv[0] + 2 << "...OK!" << std::endl;
  return 0;
}
