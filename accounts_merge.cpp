// Leetcode: https://leetcode.com/problems/accounts-merge/description/
// Given sets of email accounts, merge any sets which have a non-null intersection.

// Brute Force:
// Better:

#include <vector>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include <assert.h>

using Accounts = std::vector<std::vector<std::string>>;
using AccountSet = std::unordered_set<std::string>;

struct AccountGroup {
    std::string name;
    AccountSet accounts;
    AccountGroup(std::string& n, AccountSet&& set): name(n), accounts(set) {}
};
using AccountGroups = std::vector<AccountGroup>;
using AccountMap = std::unordered_map<std::string, int>; // email -> group index

// Accepted. 109ms. Beats 75.00% of submissions, ties 2.70% of submissions.
class Solution {
public:
    Accounts accountsMerge(Accounts& accounts) {
        AccountMap map;
        AccountGroups groups;

        for (auto& a : accounts) {
            AccountSet new_set;
            int set_index = groups.size();
            auto& name = a[0];

            for (int i = 1; i < a.size(); ++i) {
                auto& email = a[i];
                auto found = map.find(email);
                new_set.emplace(email);

                if (found != map.end()) {
                    if (set_index == groups.size()) { 
                        set_index = found->second; 
                    } else if (found->second != set_index) {
                        auto to_clear = found->second;
                        groups[set_index].accounts.insert(groups[to_clear].accounts.begin(), 
                                                          groups[to_clear].accounts.end());
                        for(auto& item : groups[to_clear].accounts) {
                            map[item] = set_index;
                        }
                        groups[to_clear].accounts.clear();
                    }
                }
            }
            for (auto& item : new_set) { map[item] = set_index; }
            if (set_index == groups.size()) {
                groups.emplace_back(name, std::move(new_set));
            } else {
                groups[set_index].accounts.insert(new_set.begin(), new_set.end());
            }
        }

        Accounts result;
        for (auto& group : groups) {
            if (group.accounts.size() == 0) { continue; }
            result.emplace_back(1, group.name);
            for (auto& email : group.accounts) {
                result.back().emplace_back(email);
            }
            std::sort(result.back().begin()+1, result.back().end());
        }
        return result;
    }
};

bool test_accounts_merge(Accounts accounts, Accounts expected) {
    Solution soln;
    auto merged = soln.accountsMerge(accounts);
    std::sort(merged.begin(), merged.end());
    std::sort(expected.begin(), expected.end());
    return merged == expected;
}

void test_accounts_merge() {
    assert(test_accounts_merge({{"David","David0@m.co","David1@m.co"},
                                {"David","David3@m.co","David4@m.co"},
                                {"David","David4@m.co","David5@m.co"},
                                {"David","David2@m.co","David3@m.co"},
                                {"David","David1@m.co","David2@m.co"}},

                                {{"David","David0@m.co","David1@m.co","David2@m.co","David3@m.co",
                                  "David4@m.co","David5@m.co"}}
                                ));

    assert(test_accounts_merge({{"Alex","Alex5@m.co","Alex4@m.co","Alex0@m.co"},
                                {"Ethan","Ethan3@m.co","Ethan3@m.co","Ethan0@m.co"},
                                {"Kevin","Kevin4@m.co","Kevin2@m.co","Kevin2@m.co"},
                                {"Gabe","Gabe0@m.co","Gabe3@m.co","Gabe2@m.co"},
                                {"Gabe","Gabe3@m.co","Gabe4@m.co","Gabe2@m.co"}},

                                {{"Alex","Alex0@m.co","Alex4@m.co","Alex5@m.co"},
                                 {"Ethan","Ethan0@m.co","Ethan3@m.co"},
                                 {"Gabe","Gabe0@m.co","Gabe2@m.co","Gabe3@m.co","Gabe4@m.co"},
                                 {"Kevin","Kevin2@m.co","Kevin4@m.co"}}
                                 ));

    assert(test_accounts_merge({{"John", "j@122.com", "j@123.com"}, 
                                {"Mary", "m@111.com", "m@333.com"},
                                {"John", "j@135.com", "j@123.com"},
                                {"Mary", "m@111.com"},
                                {"Sue", "s@1.com"}},
                                
                                {{"John", "j@122.com", "j@123.com", "j@135.com"},
                                 {"Mary", "m@111.com", "m@333.com"},
                                 {"Sue", "s@1.com"}}
                                ));
}

int main(int argc, char** argv) {
    test_accounts_merge();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
