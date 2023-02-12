#pragma once

#include "../internal/macro.hpp"

namespace sugar::_internal::_for {

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

}  // namespace sugar::_internal::_for

inline int _sugar_loop_state = -1;  // dummy

#define for(...) \
    SUGAR_FOR_IMPL(SUGAR_CONCAT(_sugar_for_, __COUNTER__), sugar::_internal::_for, __VA_ARGS__)
#define SUGAR_FOR_IMPL(label_name, ns, ...)                                         \
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

#define break                         \
    if (_sugar_loop_state = 2; false) \
        SUGAR_NOOP;                   \
    else                              \
        break

#define break_of(label)                                                                    \
    do {                                                                                   \
        sugar::_internal::_for::break_state = sugar::_internal::_for::BreakState::breaked; \
        goto label;                                                                        \
    } while (false)
