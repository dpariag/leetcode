// Leetcode: https://leetcode.com/problems/exam-room/
//

// Brute Force:
// Better:

#include <set>
#include <iostream>
#include <assert.h>

struct Range {
  int start = 0;
  int end = 0;
  int size = 0;
  int seat = 0;
  int distance = 0;

  Range(int s, int e, int last_seat) : start(s), end(e) {
    size = end - start; 
    if (end == last_seat) {
      seat = last_seat;
      distance = end - start;
    } else {
      seat = start + (size / 2);
      distance = std::min((seat-start), (end-seat));
    }
  }

  bool operator==(const Range& other) const {
    return start == other.start && end == other.end;
  }

  friend std::ostream& operator<<(std::ostream& os, const Range& r);  
};

std::ostream& operator<<(std::ostream& os, const Range& r) {
  os << " [" << r.start << "," << r.end << "] ";
  os << " distance = " << r.distance;
  return os;
}

// Descending order
struct CompareBySize {
  bool operator()(const Range& r1, const Range& r2) const {
    if (r1.distance == r2.distance) { return r1.start < r2.start; }    
    return r1.distance > r2.distance;
  }
};

struct CompareByStart {
  bool operator()(const Range& r1, const Range& r2) const {
    return r1.start < r2.start;
  }
};

// Accepted. 24ms. Beats 61.08% of submissions
class ExamRoom {
public:
  ExamRoom(int N): last_seat(N-1) {
    insert(0, last_seat);
  }

  int seat() {
    int seat = 0;
    auto begin_iter = ranges_by_size.begin();
    auto biggest = *begin_iter;
    ranges_by_size.erase(begin_iter);
    ranges_by_start.erase(biggest);

    if (biggest.start == 0) {
      seat = 0;
      insert(1, biggest.end);
    } else if (biggest.end == last_seat) {
      seat = last_seat;
      insert(biggest.start, last_seat - 1);
    } else {
      seat = biggest.start + (biggest.size / 2);
      if (biggest.start < seat) {
        insert(biggest.start, seat-1);
      }
      if (seat < biggest.end) {
        insert(seat+1, biggest.end);
      }
    }
    return seat;
  }

  void leave(int p) {
    auto next_iter = ranges_by_start.lower_bound(Range(p,p, last_seat));
    if (ranges_by_start.empty()) {
      // Nothing on either side
      insert(p, p);
    } else if (next_iter == ranges_by_start.end()) {
      // Nothing to the right of p
      auto prev_iter = ranges_by_start.rbegin();
      auto prev = *prev_iter;
      if (prev.end + 1 == p) {
        // Join with left 
        ranges_by_start.erase(prev);
        ranges_by_size.erase(prev);
        insert(prev.start, p);
      } else {
        // Nothing to join
        insert(p,p); 
      }
    } else {
      auto next = *next_iter;
      // Something to the right of p
      if (next_iter == ranges_by_start.begin()) {
        // Nothing to the left of p
        if (p == next.start-1) {
          // Join with right
          erase(next_iter);
          insert(p, next.end); 
        }
      } else {
        // Something to the left of p (i.e., both sides)
        auto temp_iter = next_iter;
        auto prev_iter = --next_iter;
        auto prev = *prev_iter;
        next_iter = temp_iter;
        if (p == prev.end+1 && p == next.start-1) {
          // Join both
          erase(prev_iter);
          erase(next_iter);
          insert(prev.start, next.end);
        } else if (p == prev.end+1) {
          // Join left
          erase(prev_iter);
          insert(prev.start, p);
        } else if (p == next.start-1) {
          // Join right
          erase(next_iter);
          insert(p, next.end);
        } else {
          // Nothing to join
          insert(p, p);
        }
      }
    }
  }

private:
  void insert(int start, int end) {
    if (start > end) { return; }
    Range r(start, end, last_seat);
    ranges_by_size.insert(r);
    ranges_by_start.insert(r);
  }

  void erase(std::set<Range>::iterator iter) {
    auto item = *iter;
    ranges_by_start.erase(iter);
    ranges_by_size.erase(item);
  }

  int last_seat;
  std::set<Range, CompareBySize> ranges_by_size;
  std::set<Range, CompareByStart> ranges_by_start;
};

void test_exam_room() {
  ExamRoom room(10);

  assert(room.seat() == 0);
  assert(room.seat() == 9);

  room.leave(9);
  assert(room.seat() == 9);
  assert(room.seat() == 4);
  assert(room.seat() == 2);
  assert(room.seat() == 6);
  assert(room.seat() == 1);
  assert(room.seat() == 3);
  assert(room.seat() == 5);
  assert(room.seat() == 7);
  assert(room.seat() == 8);

  room.leave(9);
  assert(room.seat() == 9);
  
  room.leave(1);
  assert(room.seat() == 1);

  ExamRoom room1(8);
  assert(room1.seat() == 0);
  assert(room1.seat() == 7);
  assert(room1.seat() == 3);
  room1.leave(0);
  room1.leave(7);
  assert(room1.seat() == 7);
  assert(room1.seat() == 0);
  assert(room1.seat() == 5);
  assert(room1.seat() == 1);
  assert(room1.seat() == 2);
  assert(room1.seat() == 4);
  assert(room1.seat() == 6);
}


int main(int argc, char** argv) {
  test_exam_room();
  std::cout << argv[0] + 2 << "...OK!" << std::endl;
  return 0;
}
