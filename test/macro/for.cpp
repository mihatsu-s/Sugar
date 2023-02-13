#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../doctest.h"

#include <sugar/macro/for.hpp>

#include <vector>
#define BEGIN_TRACE() std::vector<int> _footprints
#define TRACE(...) _footprints.push_back(__VA_ARGS__)
#define CHECK_TRACE(...) CHECK_EQ(_footprints, std::vector<int>({__VA_ARGS__}))

TEST_SUITE("for-else statement") {
    TEST_CASE("else block is executed last") {
        BEGIN_TRACE();
        for (int i = 0; i < 5; ++i) {
            TRACE(i);
        }
        else {
            TRACE(-1);
        }
        CHECK_TRACE(0, 1, 2, 3, 4, -1);
    }

    TEST_CASE("else block is skipped by break") {
        BEGIN_TRACE();
        for (int i = 0; i < 5; ++i) {
            if (i == 3) break;
            TRACE(i);
        }
        else {
            TRACE(-1);
        }
        CHECK_TRACE(0, 1, 2);
    }

    TEST_CASE("outer loop can be continued from else block") {
        BEGIN_TRACE();
        for (int i = 0; i < 5; ++i) {
            TRACE(i);
            for (; false;) {
                TRACE(-1);
            }
            else {
                continue;
            }
            TRACE(-2);
        }
        CHECK_TRACE(0, 1, 2, 3, 4);
    }
}

TEST_SUITE("break macro") {
    TEST_CASE("break macro without an argument behaves like a break statement") {
        int x = 1;
        while (true) {
            x *= 2;
            if (x > 5) break;
        }
        CHECK(x == 8);
    }

    TEST_CASE("break macro with an argument breaks given for statement") {
        BEGIN_TRACE();
    loop_i:
        for (int i = 1; i < 5; ++i) {
        loop_j:
            for (int j = 1; j < 5; ++j) {
                for (int k = 1; k < 5; ++k) {
                    TRACE(i * 100 + j * 10 + k);
                    if (k >= 3) break;
                    if (j + k >= 4) break(loop_j);
                    if (i + j + k >= 5) break(loop_i);
                }
            }
        }
        CHECK_TRACE(111, 112, 113, 121, 122, 211, 212);
    }
}
