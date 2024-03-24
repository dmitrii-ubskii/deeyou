#pragma once

#include <array>

namespace DU
{
namespace detail
{
template<typename Rep>
struct Vector2D
{
	using Type = Vector2D<Rep>;

	Rep x;
	Rep y;

	Vector2D()
		: Vector2D(0, 0)
	{}

	Vector2D(Rep x_, Rep y_)
		: x{x_}
		, y{y_}
	{}

	Vector2D(Type const& other) = default;
	Vector2D(Type&& other) = default;
	Type& operator=(Type const& other) = default;
	Type& operator=(Type&& other) = default;
	~Vector2D() = default;

	constexpr auto operator<=>(Type const& other) const = default;

	constexpr Type operator+(Type const& other) const
	{
		return {x + other.x, y + other.y};
	}
};
}

using IntVector2D = detail::Vector2D<int>;
}
