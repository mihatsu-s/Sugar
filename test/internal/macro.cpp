#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../doctest.h"

#include <sugar/internal/macro.hpp>

#include <string.h>
#define CHECK_STR_EQ(a, b) CHECK_STR_EQ_PRIMITIVE(a, b)
#define CHECK_STR_EQ_PRIMITIVE(a, b) CHECK(strcmp(#a, #b) == 0)

TEST_CASE("SUGAR_NOOP do nothing") {
    SUGAR_NOOP;
    CHECK(true);
}

TEST_CASE("SUGAR_CONCAT concats two tokens after macro expansion") {
#define REPEAT(x) x##x
    CHECK_STR_EQ(SUGAR_CONCAT(REPEAT(X), REPEAT(Y)), XXYY);
#undef REPEAT
}

TEST_CASE("SUGAR_NARGS counts given arguments") {
    // CHECK_STR_EQ(SUGAR_NARGS(), 0);  // not supported
    CHECK_STR_EQ(SUGAR_NARGS(X), 1);
    CHECK_STR_EQ(SUGAR_NARGS(X, Y), 2);
    CHECK_STR_EQ(SUGAR_NARGS(X, Y, Z), 3);
}

TEST_CASE("SUGAR_ALT_SELECTOR detects SUGAR_ALT specifier and branches to *_ALT macro") {
#define REPEAT(x) x##x
#define REPEAT_ALT(x) x##x##x
#define TEST(...) SUGAR_ALT_SELECTOR(REPEAT, __VA_ARGS__)
    CHECK_STR_EQ(TEST(X), XX);
    CHECK_STR_EQ(TEST(SUGAR_ALT, X), XXX);
#undef TEST
#undef REPEAT
#undef REPEAT_ALT
}
