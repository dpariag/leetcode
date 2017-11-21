// Leetcode: https://leetcode.com/problems/moving-average-from-data-stream/description/
//

// Brute Force:
// Better:

#include <vector>
#include <iostream>
#include <assert.h>

// Accepted. 33ms. Beats 52.07% of submissions, ties 18.84% of submissions.
class MovingAverage {
public:
    /** Initialize your data structure here. */
    MovingAverage(int size): m_values(size, 0), m_index(-1) { 
    }

    double next(int val) {
        m_index = (m_index + 1) % m_values.size();
        auto discard = m_values[m_index];
        m_values[m_index] = val;

        total += val;
        total -= discard;
        if (size < m_values.size()) { ++size; }
        std::cout << double(total) / double(size) << std::endl;
        return double(total) / double(size);
    }

private:
    std::vector<int> m_values;
    int m_index = 0;
    int total = 0;
    int size = 0;
};

void test_moving_average() {
    MovingAverage m1(1);
    assert(m1.next(1) == 1.0);
    assert(m1.next(21) == 21.0);

    MovingAverage m2(2);
    assert(m2.next(0) == 0.0);
    assert(m2.next(1) == 0.5);
    assert(m2.next(1) == 1.0);
    assert(m2.next(5) == 3.0);

    MovingAverage m3(3);
    assert(m3.next(1) == 1);
    assert(m3.next(2) == 1.5);
    assert(m3.next(6) == 3.0);
    assert(m3.next(10) == 6.0);
    assert(m3.next(5) == 7.0);

}

int main(int argc, char** argv) {
    test_moving_average();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
