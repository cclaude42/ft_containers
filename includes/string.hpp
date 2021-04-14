#ifndef STRING_HPP
# define STRING_HPP

# include <sstream>

namespace ft
{
	template <typename T>
	std::string	to_string(T n)
	{
		std::ostringstream	ss;
		ss << n;
		return (ss.str());
	}
}

#endif
