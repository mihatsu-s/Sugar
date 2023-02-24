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

TEST_SUITE("SUGAR_ALL macro") {
    TEST_CASE("provides .begin() and .end() of the container") {
        std::vector<int> v{3, 1, 4, 1, 5, 9, 2};

        auto v1 = v;
        std::sort(SUGAR_ALL(v1));

        auto v2 = v;
        std::sort(v2.begin(), v2.end());

        CHECK_EQ(v1, v2);
    }

    TEST_CASE("works properly for rvalue") {
        std::vector<int> v1(SUGAR_ALL(collatz(6)));

        auto temp = collatz(6);
        std::vector<int> v2(temp.begin(), temp.end());

        CHECK_EQ(v1, v2);
    }
}

TEST_SUITE("SUGAR_RALL macro") {
    TEST_CASE("provides .rbegin() and .rend() of the container") {
        std::vector<int> v{3, 1, 4, 1, 5, 9, 2};

        auto v1 = v;
        std::sort(SUGAR_RALL(v1));

        auto v2 = v;
        std::sort(v2.rbegin(), v2.rend());

        CHECK_EQ(v1, v2);
    }

    TEST_CASE("works properly for rvalue") {
        std::vector<int> v1(SUGAR_RALL(collatz(6)));

        auto temp = collatz(6);
        std::vector<int> v2(temp.rbegin(), temp.rend());

        CHECK_EQ(v1, v2);
    }
}
