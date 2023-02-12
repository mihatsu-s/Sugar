#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../doctest.h"

#include <sugar/internal/macro.hpp>

#include <string.h>
#define CHECK_STREQ(a, b) CHECK_STREQ_PRIMITIVE(a, b)
#define CHECK_STREQ_PRIMITIVE(a, b) CHECK(strcmp(#a, #b) == 0)

TEST_SUITE("SUGAR_CONCAT") {
    TEST_CASE("concats two tokens") {
        CHECK_STREQ(SUGAR_CONCAT(ABC, XYZ), ABCXYZ);
    }

    TEST_CASE("concats two tokens after expansion") {
#define REPEAT(x) x##x
        CHECK_STREQ(SUGAR_CONCAT(REPEAT(X), REPEAT(Y)), XXYY);
    }
}

TEST_SUITE("SUGAR_NOOP") {
    TEST_CASE("do nothing") {
        SUGAR_NOOP;
        CHECK(true);
    }
}
