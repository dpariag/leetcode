// Leetcode: https://leetcode.com/problems/peeking-iterator/description/
// Given an Iterator class interface with methods: next() and hasNext(), 
// design and implement a PeekingIterator that support the peek() operation -- 
// it essentially peek() at the element that will be returned by the next call to next().

#include <vector>
#include <iostream>
#include <assert.h>

using namespace std;

class Iterator {
    struct Data;
	Data* data;
public:
	Iterator(const vector<int>& nums);
	Iterator(const Iterator& iter);
	virtual ~Iterator();

	// Returns the next element in the iteration.
	int next();

	// Returns true if the iteration has more elements.
	bool hasNext() const;
};

// Accepted. 3ms. Beats 3.95% of submissions, ties 94.32% of submissions.
class PeekingIterator : public Iterator {
public:
	PeekingIterator(const vector<int>& nums) : Iterator(nums) {}

    // Returns the next element in the iteration without advancing the iterator.
	int peek() {
        Iterator iter(static_cast<Iterator>(*this));
        return iter.next();
	}

	int next() {
	    return Iterator::next();
	}

	bool hasNext() const {
	    return Iterator::hasNext();
	}
};

int main(int argc, char** argv) {
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
