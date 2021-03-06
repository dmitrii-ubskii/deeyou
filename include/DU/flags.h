#pragma once

#include <bitset>

#include "DU/enum_utils.h"

namespace DU
{
template <typename Enum>
class Flags
{
	public:
		Flags() = default;
		Flags(std::initializer_list<Enum> flags)
		{
			for (auto f: flags)
			{
				set(f);
			}
		}

		void set(Enum f) { bits[static_cast<std::size_t>(f)] = true; }
		void unset(Enum f) { bits[static_cast<std::size_t>(f)] = false; }
		auto operator[](Enum f) const { return bits[static_cast<std::size_t>(f)]; }

		std::string toString() const { return bits.to_string(); }

	private:
		std::bitset<enumLength<Enum>()> bits;
};
}
