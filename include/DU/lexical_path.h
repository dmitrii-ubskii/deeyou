#ifndef DU_LEXICAL_PATH_H_
#define DU_LEXICAL_PATH_H_

#include <string>

namespace DU
{
class LexicalPath
{
public:
	LexicalPath(std::string_view path_ = ""): path{path_} {}

	LexicalPath& operator/=(std::string_view other)
	{
		if (path == "")
		{
			path = other;
		}
		else
		{
			path += "/";
			path += other;
		}
		return *this;
	}

	LexicalPath& operator/=(LexicalPath const& other)
	{
		return *this /= other.path;
	}

	friend LexicalPath operator/(LexicalPath const& lhs, std::string_view rhs)
	{
		auto newPath = lhs;
		return newPath /= rhs;
	}
	friend LexicalPath operator/(LexicalPath const& lhs, LexicalPath const& rhs)
	{
		return lhs / rhs.path;
	}
	friend LexicalPath operator/(std::string_view lhs, LexicalPath const& rhs)
	{
		return LexicalPath{lhs} / rhs.path;
	}

	LexicalPath commonPrefix(LexicalPath& other)
	{
		auto prefix = LexicalPath{};
		for (
			auto it1 = begin(), it2 = other.begin();
			it1 != end() && it2 != other.end() && *it1 == *it2;
			++it1, ++it2
		)
		{
			prefix /= *it1;
		}
		return prefix;
	}

	std::string const& toString() const { return path; }

	auto operator<=>(LexicalPath const& other) const { return path <=> other.path; }
	auto operator==(LexicalPath const& other) const { return path == other.path; }

	class Iterator
	{
	public:
		Iterator(std::string::const_iterator begin, std::string::const_iterator end_)
			: elementBegin(begin)
			, end{end_}
		{
			findElementEnd();
		}

		Iterator& operator++()
		{
			elementBegin = elementEnd;
			while (elementBegin != end && *elementBegin == '/')
			{
				elementBegin++;
			}
			findElementEnd();

			return *this;
		}

		std::string_view operator*() const { return {elementBegin, elementEnd}; }
		std::string_view operator->() const { return operator*(); }

		bool operator!=(Iterator const& other) const { return elementBegin != other.elementBegin; }

	private:
		std::string::const_iterator elementBegin;
		std::string::const_iterator elementEnd;
		std::string::const_iterator end;

		void findElementEnd() { elementEnd = std::find(elementBegin, end, '/'); }
	};

	Iterator begin() const { return {path.begin(), path.end()}; }
	Iterator end() const { return {path.end(), path.end()}; }

private:
	std::string path;
};
}

namespace std
{
template <> struct hash<DU::LexicalPath>
{
	typedef DU::LexicalPath argument_type;
	typedef std::size_t result_type;
	result_type operator()(argument_type const& p) const noexcept
	{
		return std::hash<std::string>{}(p.toString());
	}
};
}

#endif // DU_LEXICAL_PATH_H_
