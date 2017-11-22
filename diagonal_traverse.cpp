// Leetcode: https://leetcode.com/problems/diagonal-traverse/description/
//

// Brute Force:
// Better:

#include <vector>
#include <iostream>
#include <assert.h>

using Matrix = std::vector<std::vector<int>>;
using Traversal = std::vector<int>;

class Solution {
public:
    Traversal findDiagonalOrder(Matrix& matrix) {
        Traversal traversal;
        if (matrix.empty()) { return traversal; }
        int num_diagonals = matrix.size() + matrix[0].size() - 1;

        return traversal;
    }
};

int main(int argc, char** argv) {
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
