#pragma once

#define SUGAR_NOOP \
    do {           \
    } while (false)

#define SUGAR_CONCAT(a, b) SUGAR_CONCAT_PRIMITIVE(a, b)
#define SUGAR_CONCAT_PRIMITIVE(a, b) a##b

#define SUGAR_FIRST(_1, ...) _1
#define SUGAR_11TH(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, ...) _11
#define SUGAR_NARGS(...) SUGAR_11TH(__VA_ARGS__, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)

#define SUGAR_ALT(...) 0, 0
#define SUGAR_CHECK_ALT(...) SUGAR_NARGS(__VA_ARGS__)
#define SUGAR_ALT_SELECTOR(macro_name, ...)                                            \
    SUGAR_CONCAT(SUGAR_ALT_SELECTOR_IMPL, SUGAR_CHECK_ALT(SUGAR_FIRST(__VA_ARGS__)())) \
    (macro_name, __VA_ARGS__)
#define SUGAR_ALT_SELECTOR_IMPL1(macro_name, ...) macro_name(__VA_ARGS__)
#define SUGAR_ALT_SELECTOR_IMPL2(macro_name, alt_label, ...) macro_name##_ALT(__VA_ARGS__)
