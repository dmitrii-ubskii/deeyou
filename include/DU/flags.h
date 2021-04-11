#ifndef FLAGS_HPP_
#define FLAGS_HPP_

#include <bitset>

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
		auto operator[](Enum f) { return bits[static_cast<std::size_t>(f)]; }

		std::string to_string() { return bits.to_string(); }

	private:
		std::bitset<static_cast<std::size_t>(Enum::COUNT_)> bits;
};


#endif // FLAGS_HPP_
