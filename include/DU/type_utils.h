#ifndef DU_TYPE_UTILS_H_
#define DU_TYPE_UTILS_H_

#include <type_traits>

namespace DU
{
template <typename T, typename... Rest>
constexpr bool allSame = false;

template <typename T>
constexpr bool allSame<T> = true;

template <typename T, typename U>
constexpr bool allSame<T, U> = std::isSame_v<T, U>;

template <typename T, typename U, typename... Rest>
constexpr bool allSame<T, U, Rest...> = allSame<T, U> && allSame<U, Rest...>;
}

#endif // DU_TYPE_UTILS_H_
