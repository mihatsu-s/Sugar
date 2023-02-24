#pragma once

#include <iterator>
#include <memory>
#include <type_traits>
#include <utility>

namespace sugar::_internal {

template <typename T, int id>
struct all_impl {
   private:
    static std::unique_ptr<T> ptr;
    static int counter;

   public:
    static inline bool is_first() noexcept {
        return ++counter % 2 == 1;
    }

    // first call
    static inline auto begin(T&& val) {
        ptr = std::make_unique<T>(std::forward<T>(val));
        return begin();
    }
    static inline auto end(T&& val) {
        ptr = std::make_unique<T>(std::forward<T>(val));
        return end();
    }
    static inline auto rbegin(T&& val) {
        ptr = std::make_unique<T>(std::forward<T>(val));
        return rbegin();
    }
    static inline auto rend(T&& val) {
        ptr = std::make_unique<T>(std::forward<T>(val));
        return rend();
    }

    // second call
    static inline auto begin() {
        return std::begin(*ptr);
    }
    static inline auto end() {
        return std::end(*ptr);
    }
    static inline auto rbegin() {
        return std::rbegin(*ptr);
    }
    static inline auto rend() {
        return std::rend(*ptr);
    }

    // not called (written only for type consistency)
    static inline auto begin(T& val) {
        return std::begin(val);
    }
    static inline auto end(T& val) {
        return std::end(val);
    }
    static inline auto rbegin(T& val) {
        return std::rbegin(val);
    }
    static inline auto rend(T& val) {
        return std::rend(val);
    }
};
template <typename T, int id>
inline int all_impl<T, id>::counter = 0;
template <typename T, int id>
inline std::unique_ptr<T> all_impl<T, id>::ptr;

#define SUGAR_ALL(...) SUGAR_ALL_IMPL((__VA_ARGS__), begin, end)
#define SUGAR_RALL(...) SUGAR_ALL_IMPL((__VA_ARGS__), rbegin, rend)
#define SUGAR_ALL_IMPL(val, begin_name, end_name) \
    SUGAR_ALL_IMPL2(                              \
        val,                                      \
        begin_name,                               \
        end_name,                                 \
        sugar::_internal::all_impl,               \
        std::remove_reference_t<decltype(val)>,   \
        __COUNTER__)
#define SUGAR_ALL_IMPL2(val, begin_name, end_name, impl, T, id) \
    SUGAR_ALL_EXPR(begin_name, val, impl, T, id), SUGAR_ALL_EXPR(end_name, val, impl, T, id)
#define SUGAR_ALL_EXPR(name, val, impl, T, id)                                                            \
    (std::is_reference_v<decltype((val))> ? std::name(val)                                                \
     : impl<T, id>::is_first()            ? static_cast<decltype(std::name(val))>(impl<T, id>::name(val)) \
                                          : static_cast<decltype(std::name(val))>(impl<T, id>::name()))

}  // namespace sugar::_internal
