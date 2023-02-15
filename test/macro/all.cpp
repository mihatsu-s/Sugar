#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../doctest.h"

#include <sugar/macro/all.hpp>

#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

std::set<int> collatz(int n) {
    std::set<int> s;
    s.insert(n);
    while (n != 1) {
        n = n % 2 ? 3 * n + 1 : n / 2;
        s.insert(n);
    }
    return s;
}

TEST_SUITE("all macro") {
    TEST_CASE("provides .begin() and .end() of the container") {
        std::vector<int> v{3, 1, 4, 1, 5, 9, 2};
        std::sort(all(v));
        CHECK_EQ(v, std::vector<int>({1, 1, 2, 3, 4, 5, 9}));
    }

    TEST_CASE("works properly for rvalue") {
        CHECK_EQ(
            std::vector<int>(all(collatz(6))),
            std::vector<int>({1, 2, 3, 4, 5, 6, 8, 10, 16}));
    }
}

TEST_SUITE("rall macro") {
    TEST_CASE("provides .rbegin() and .rend() of the container") {
        std::vector<int> v{3, 1, 4, 1, 5, 9, 2};
        std::sort(rall(v));
        CHECK_EQ(v, std::vector<int>({9, 5, 4, 3, 2, 1, 1}));
    }

    TEST_CASE("works properly for rvalue") {
        CHECK_EQ(
            std::vector<int>(rall(collatz(6))),
            std::vector<int>({16, 10, 8, 6, 5, 4, 3, 2, 1}));
    }
}
