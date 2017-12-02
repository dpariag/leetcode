// Leetcode: https://leetcode.com/problems/evaluate-division/description/
// Given equations of the form A / B = k, where k is a floating point number,
// and some queries, return the answers. If the answer does not exist, return -1.0.
// Example: Given a / b = 2.0, b / c = 3.0. 
// queries are: a / c = ?, b / a = ?, a / e = ?, a / a = ?, x / x = ? .
// return [6.0, 0.5, -1.0, 1.0, -1.0 ].

// Approach: Given a query, find all fractions with the same numerator.
// Starting with the numerator set, perform breadth-first-search to replace the denominator
// of each candidate (a/b * b/c = a/c) until the query is satisfied or the search is exhausted.

#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <assert.h>

struct Fraction {
    std::string numer;
    std::string denom;
    double value;
    Fraction(std::string numerator, std::string denominator, double result):
        numer(numerator), denom(denominator), value(result) {}
    bool operator==(const Fraction& other) const {
        return numer == other.numer && denom == other.denom;
    }
};
using Fractions = std::vector<Fraction>;

struct FractionHash {
    size_t operator()(const Fraction& f) const {
        std::hash<std::string> string_hash;
        return string_hash(f.numer) * 19 + string_hash(f.denom) * 17;
    }
};


using FractionMap = std::unordered_map<std::string, Fractions>;  // numerator/denominator -> Fractions with numerator/denominator
using FractionSet = std::unordered_set<Fraction, FractionHash>;

using Equation = std::pair<std::string, std::string>;
using Equations = std::vector<Equation>;
using Values = std::vector<double>;

// Accepted. 0ms. Beats 61.44% of submissions, ties 38.56% of submissions
class Solution {
public:

    double bfs(const Fraction& query, FractionMap& by_denom, FractionMap& by_numer, FractionSet& cache) {
        std::queue<Fraction> q;
        FractionSet visited;

        double result = -1.0;
        const auto& same_numerator = by_numer[query.numer];
        for (int i = 0; i < int(same_numerator.size()); ++i) {
            q.emplace(same_numerator[i]);
            visited.emplace(same_numerator[i]);
        }

        while (!q.empty()) {
            auto f = q.front();
            q.pop();

            auto to_multiply = by_numer[f.denom]; // (a/b) * (b/c) produces (a/c)
            for (int i = 0; i < int(to_multiply.size()); ++i) {
                auto& g = to_multiply[i];
                Fraction next(f.numer, g.denom, f.value * g.value);
                cache.emplace(next);

                if (next == query) {
                    result = next.value;
                    break;
                }
                if (visited.count(next) == 0) {
                    q.push(next);
                    visited.emplace(next);
                }
            }
        }
        return result;
    }

    Values calcEquation(Equations& equations, Values& values, const Equations& queries) {
        FractionSet cache(equations.size()*2);
        FractionMap by_denom, by_numer;

        for (int i = 0; i < int(equations.size()); ++i) {
            auto eqn = equations[i];
            std::string n = eqn.first, d = eqn.second;
            
            cache.emplace(n, d, values[i]);
            by_numer[n].emplace_back(Fraction(n,d, values[i]));
            by_denom[d].emplace_back(Fraction(n,d, values[i]));

            if (values[i] != 0.0) {
                auto reciprocal = 1.0 / values[i];
                cache.emplace(d, n, reciprocal);
                by_numer[d].emplace_back(Fraction(d,n, reciprocal));
                by_denom[n].emplace_back(Fraction(d,n, reciprocal));
            }
        }

        Values result;
        for (int i = 0; i < int(queries.size()); ++i) {
            auto query = queries[i];
            Fraction f(query.first, query.second, 0.0);

            if (f.numer == f.denom && (by_numer.count(f.numer) > 0 || by_denom.count(f.denom) > 0)) {
                result.emplace_back(1.0);
                continue;
            }

            auto found = cache.find(f);
            if (found != cache.end()) {
                result.emplace_back(found->value);
                continue;
            }

            result.emplace_back(bfs(f, by_denom, by_numer, cache));
        }
        return result;
    }
};

void test_division() {
    Solution soln;

    Equations equations({{"a","b"}, {"b","c"}});
    Values values({2.0,3.0});
    Equations queries({{"a","c"}, {"b","a"}, {"a","e"}, {"a","a"}, {"x","x"}});
    assert(soln.calcEquation(equations, values, queries) == Values({6.0, 0.5, -1.0, 1.0, -1.0 }));
}

int main(int argc, char** argv) {
    test_division();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}