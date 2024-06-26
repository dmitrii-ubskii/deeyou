#pragma once

#include <type_traits>
#include <utility>

namespace DU
{
template <typename T, typename... Rest>
constexpr bool allSame = false;

template <typename T>
constexpr bool allSame<T> = true;

template <typename T, typename U>
constexpr bool allSame<T, U> = std::is_same_v<T, U>;

template <typename T, typename U, typename... Rest>
constexpr bool allSame<T, U, Rest...> = allSame<T, U> && allSame<U, Rest...>;

template <typename T, typename Tag>
struct StrongTypedef: public T
{
	template <typename... Args>
	explicit StrongTypedef(Args&&... args): T{std::forward<Args>(args)...} {}

	constexpr friend auto operator<=>(StrongTypedef<T, Tag> const&, StrongTypedef<T, Tag> const&) = default;
};

template <typename To, typename From>
struct ConstnessAs
{
	using Type = std::remove_const_t<To>;
};

template <typename To, typename From>
struct ConstnessAs<To, From const>
{
	using Type = std::add_const_t<To>;
};

template <typename To, typename From>
using ConstnessAsT = typename ConstnessAs<To, From>::Type;

template <typename T, typename... Rest>
struct FirstOfPack
{
	using Type = T;
};

template <typename... Ts>
using FirstOfPackT = typename FirstOfPack<Ts...>::Type;
}
