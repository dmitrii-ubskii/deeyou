#pragma once

#include <type_traits>

#include "DU/type_utils.h"

namespace DU
{
template <typename T>
constexpr T hashCombine(T u)
{
    return u;
}

template <typename T, typename... Ts>
constexpr T hashCombine(T u, Ts... vs)
	requires std::is_integral_v<T> && allSame<std::remove_cvref_t<T>, std::remove_cvref_t<Ts>...>
{
    return u ^ (hashCombine(vs...) + 0x9e3779b9 + (u << 6) + (u >> 2));  // Boost's hash_combine()
}
}
