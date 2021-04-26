#ifndef DU_ENUM_UTILS_H_
#define DU_ENUM_UTILS_H_

#include <climits>
#include <cstring>
#include <utility>

namespace DU
{
namespace Impl
{
template <typename Enum, Enum Value>
constexpr bool isValid()
{
	// Ex.: enum class Fruit { Banana = 10, Apple = 20 };
	// "bool isValid() [Enum = Fruit, Value = Fruit::Banana]" for valid values.
	// "bool isValid() [Enum = Fruit, Value = 15]" for invalid values in some cases.
	// "bool isValid() [Enum = Fruit, Value = (Fruit)15]" for invalid values in other cases.
	auto name = __PRETTY_FUNCTION__;
	auto i = strlen(name);
	for (; i >= 0; i--)
	{
		if (name[i] == ' ' || name[i] == ')')  // looking for either a space or a C-style cast
		{
			break;
		}
	}
	auto ch = name[i+1];
	// A valid identifier must begin with a non-digit character; a digit indicates an invalid enum value.
	return ch < '0' || ch > '9';
}

template <typename Enum>
constexpr int countValid()
{
	return 0;
}

template <typename Enum, Enum First, Enum... Rest>
constexpr int countValid()
{
	return isValid<Enum, First>() + countValid<Enum, Rest...>();
}

template <typename Enum, int... I>
constexpr int enumLengthImpl(std::integer_sequence<int, I...>)
{
	return countValid<Enum, static_cast<Enum>(I)...>();
}
}

template <typename Enum, int Max = 256>
constexpr std::size_t enumLength()
{
	return Impl::enumLengthImpl<Enum>(std::make_integer_sequence<int, Max>());
}
}

#endif // DU_ENUM_UTILS_H_
