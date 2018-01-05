// Leetcode: 

// Brute Force:
// Better:

#include <vector>
#include <iostream>
#include <assert.h>

// Forward declaration of isBadVersion API.
bool isBadVersion(int version);

// Accepted. 0ms. Beats 18.20% of submissions, ties 81.80% of submissions.
class Solution {
public:
    int find_bad_version(int start, int end) {        
        int first_bad = -1;
        while (start <= end) {
            if (start == end && first_bad == -1) { return start; }
            int mid = start + (end-start) / 2;
            auto is_bad = isBadVersion(mid);
            if (is_bad) {
                first_bad = mid;
                end = mid -1;
            } else {
                // Good.
                start = mid + 1;
            }
        }
        return first_bad;
    }

    int firstBadVersion(int n) {
        return find_bad_version(1, n);
    }
};

int main(int argc, char** argv) {
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
