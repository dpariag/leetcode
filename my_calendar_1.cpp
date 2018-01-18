// Leetcode: 

// Brute Force:
// Better:

#include <map>
#include <iostream>
#include <assert.h>

// Accepted. 76ms. Beats 76.39% of submissions, ties 7.18% of submissions
class MyCalendar {
public:
    MyCalendar() {}
    
    bool book(int start, int end) {
        auto after = bookings.upper_bound(start); // find appt with next larger end time

        if (after == bookings.end() || (after == bookings.begin() && end <= after->second)) {
            // We are the first or last appt with no overlap
            bookings.emplace(std::make_pair(end, start));
            return true;
        } 
        
        if (end > after->second) {
            // Our appt ends after the start of the following appt
            return false; 
        }

        auto before = after;
        --before;
        if (before->first > start) {
            // Previous appt ends after we begin
            return false;
        }

        // All clear. Previous ends before we begin, we end before next begins
        bookings.emplace(std::make_pair(end,start));
        return true;
    }
private:
    std::map<int,int> bookings; // maps end_time -> start_time
};

void test_calendar() {
    MyCalendar cal;
    assert(cal.book(10,20) == true);
    assert(cal.book(15,25) == false);
    assert(cal.book(20,30) == true);
}

int main(int argc, char** argv) {
    test_calendar();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
