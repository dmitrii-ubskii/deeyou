#pragma once

namespace DU
{
template <typename T>
constexpr int sign(T a)
{
	return (a > 0) - (a < 0);
}

constexpr int floorDiv(int const divident, int const divisor)
{
	auto quot = divident / divisor;
	auto rem = divident % divisor;

	// a: dividend
	// b: divisor
	//
	// q: quotient
	// r: remainder
	//
	// qt: truncating quotient
	// rt: truncating remainder
	//
	// C++ division truncates towards 0. (a / b == qt, a % b == rt)
	//
	// In a proper flooring division the remainder `r` has the same sign as the divisor.
	// If the truncating remainder is non-zero and has a different sign from the divisor,
	// then r == rt + b, q = qt - 1; (to account for 1 lot of b being "moved" to the remainder).

	return quot - (rem != 0 && sign(rem) != sign(divisor));
}
}
