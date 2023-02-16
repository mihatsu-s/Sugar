#pragma once

#include "../internal/macro.hpp"

namespace sugar::_internal::for_impl {

enum class BreakState {
    none,
    completed,
    breaked
};
inline BreakState break_state = BreakState::none;
inline BreakState get_and_reset_break_state() noexcept {
    auto res = break_state;
    break_state = BreakState::none;
    return res;
}

}  // namespace sugar::_internal::for_impl

#define for(...) SUGAR_ALT_SELECTOR(SUGAR_FOR_IMPL, __VA_ARGS__)
#define SUGAR_FOR_IMPL_ALT(...) for (__VA_ARGS__)
#define SUGAR_FOR_IMPL(...) \
    SUGAR_FOR_IMPL2(SUGAR_CONCAT(_sugar_for_, __COUNTER__), sugar::_internal::for_impl, __VA_ARGS__)
#define SUGAR_FOR_IMPL2(label_name, ns, ...)                                        \
    label_name:                                                                     \
    if (ns::break_state == ns::BreakState::breaked)                                 \
        ns::break_state = ns::BreakState::none;                                     \
    else if (ns::get_and_reset_break_state() == ns::BreakState::none)               \
        for (int _sugar_loop_state = 0; _sugar_loop_state < 2; ++_sugar_loop_state) \
            if (_sugar_loop_state == 1) {                                           \
                ns::break_state = ns::BreakState::completed;                        \
                goto label_name;                                                    \
            } else                                                                  \
                for (__VA_ARGS__)

// dummy variables
inline int _sugar_loop_state = -1;
constexpr inline int SUGAR_BREAK_LABEL_RECIEVER = 0;

#define break SUGAR_BREAK_IMPL(SUGAR_CONCAT(_sugar_break_, __COUNTER__))
#define SUGAR_BREAK_IMPL(label_name)                                \
    if (_sugar_loop_state = 2; false)                               \
    label_name:                                                     \
        break;                                                      \
    else                                                            \
        for (SUGAR_ALT, int _sugar_i = 0; _sugar_i < 2; ++_sugar_i) \
            if (_sugar_i != 0)                                      \
                goto label_name;                                    \
            else                                                    \
                SUGAR_BREAK_LABEL_RECIEVER

#define SUGAR_BREAK_LABEL_RECIEVER(label)                                                          \
    do {                                                                                           \
        sugar::_internal::for_impl::break_state = sugar::_internal::for_impl::BreakState::breaked; \
        goto label;                                                                                \
    } while (false)
