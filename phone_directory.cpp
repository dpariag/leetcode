// Leetcode: https://leetcode.com/problems/design-phone-directory/description/
// Approach: Track available numbers in an unordered_set.

#include <unordered_set>
#include <iostream>
#include <assert.h>

class PhoneDirectory {
public:
    /** Initialize your data structure here
        @param maxNumbers - The maximum numbers that can be stored in the phone directory. */
    PhoneDirectory(int maxNumbers) {
        for (int i = 0; i < maxNumbers; ++i) {
            m_available.emplace(i);
        }
    }
    
    /** Provide a number which is not assigned to anyone.
    @return - Return an available number. Return -1 if none is available. */
    int get() {
        if (m_available.empty()) { return -1; }
        auto iter = m_available.begin();
        int number = *iter;
        m_available.erase(iter);
        return number;        
    }
    
    /** Check if a number is available or not. */
    bool check(int number) {
        return m_available.count(number) == 1;
    }
    
    void release(int number) {
        m_available.emplace(number);
    }
private:
    std::unordered_set<int> m_available;
};

void test_phone_directory() {
    PhoneDirectory directory(3);

    assert(directory.check(0) == true);
    assert(directory.check(1) == true);
    assert(directory.check(2) == true);

    int taken1 = directory.get();
    assert(taken1 == 0 || taken1 == 1 || taken1 == 2);
    assert(directory.check(taken1) == false);

    int taken2 = directory.get();
    assert(taken1 != taken2);
    assert(directory.check(taken1) == false);

    int taken3 = directory.get();
    assert(taken3 != taken2 && taken3 != taken1);
    assert(directory.check(taken3) == false);
    assert(directory.check(taken2) == false);
    assert(directory.check(taken1) == false);

    directory.release(taken3);
    assert(directory.check(taken3) == true);
}

int main(int argc, char** argv) {
    test_phone_directory();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}