#include <vector>
#include <iostream>
#include <assert.h>
#include "union_find.h"

// Quick test of union-find functionality
void test_union_find() {
    UnionFind u1(5); // 5 possible items

    u1.add(1);
    u1.add(2);
    u1.add(3);
    u1.add(4);
    assert(u1.find(1) == 1);
    assert(u1.find(2) == 2);
    assert(u1.find(3) == 3);
    assert(u1.find(4) == 4);

    u1.merge(2,3);
    assert(u1.find(2) == u1.find(3));
    assert(u1.find(1) != u1.find(2));

    u1.merge(3,4);
    assert(u1.find(2) == u1.find(3));
    assert(u1.find(3) == u1.find(4));
    assert(u1.find(1) != u1.find(4));
}

int main(int argc, char** argv) {
    test_union_find();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
