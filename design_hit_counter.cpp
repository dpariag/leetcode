// Leetcode: https://leetcode.com/problems/design-hit-counter/description/
// Design a hit counter which counts the number of hits received in the past 300 secs.
// Timestamps are whole seconds, and hits occur in chronological order.

// Approach: A fixed-size circular buffer of size 300. Have to be careful about
// updating the array and the total count when time moves forward.

#include <vector>
#include <iostream>
#include <assert.h>

// Accepted. 3ms. Beats 1.38% of submissions, ties 85.08% of submissions.
class HitCounter {
public:
    HitCounter() : m_counts(300, 0) {
    }
    
    void hit(int timestamp) {
    	clear(timestamp);
    	int dest = index(timestamp);
    	++m_counts[dest];
    	++m_total;
    	m_cur = timestamp;
    }
    
    int getHits(int timestamp) {
        clear(timestamp);
        return m_total;
    }
private:
	inline int index(int timestamp) {
		return (timestamp - 1) % 300;
	}

	inline void clear(int timestamp) {
    	int diff = timestamp - m_cur;
    	if ((diff / m_counts.size()) > 0) {
    		// Clear the whole array
    		for (int i = 0; i < m_counts.size(); ++i) { m_counts[i] = 0; }
    		m_total = 0;
    	} else {
    		// Clear a subset of the array
    		int cleared = 0, to_clear = diff % m_counts.size();
			int start = index(m_cur+1);
			while (cleared < to_clear) {
				m_total -= m_counts[start];
	    		m_counts[start] = 0;
	    		start = (start + 1) % m_counts.size();
	    		++cleared;
			}
    	}
	}

	std::vector<int> m_counts;
	int m_cur = 1;		// current timestamp
	int m_total = 0;
};

void test_hit_counter() {
	HitCounter hc;

	assert(hc.getHits(1) == 0);
	assert(hc.getHits(10) == 0);

	hc.hit(10);
	assert(hc.getHits(10) == 1);
	assert(hc.getHits(11) == 1);

	hc.hit(12);
	assert(hc.getHits(12) == 2);

	hc.hit(300);
	assert(hc.getHits(300) == 3);	

	hc.hit(301);
	assert(hc.getHits(301) == 4);

	hc.hit(310);
	assert(hc.getHits(310) == 4);

	hc.hit(610);
	assert(hc.getHits(610) == 1);	
	assert(hc.getHits(910) == 0);
}

int main(int argc, char** argv) {
	test_hit_counter();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
