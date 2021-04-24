#ifndef UTILS_HPP
# define UTILS_HPP

# include <sstream>

# if __APPLE__
#  define OS 1
# else
#  define OS 0
# endif

# define MAC 1
# define LINUX 0

namespace ft
{
	//////////////////////////////
	// To string
	//////////////////////////////

	template <typename T>
	std::string to_string (T & n)
	{
		std::ostringstream	ss;
		ss << n;
		return (ss.str());
	}

	//////////////////////////////
	// Lexicographical compare
	//////////////////////////////

	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare (InputIterator1 lit, InputIterator1 lend, InputIterator2 rit, InputIterator2 rend)
	{
		while (lit != lend)
		{
			if (rit == rend || *rit < *lit)
				return (false);
			else if (*lit < *rit)
				return (true);
			++lit, ++rit;
		}

		return (rit != rend);
	}

	template <class T>
	bool lexicographical_compare (T & a, T & b)
	{
		return (a < b);
	}

	//////////////////////////////
	// Equal
	//////////////////////////////

	template <class InputIterator1, class InputIterator2>
	bool equal (InputIterator1 lit, InputIterator1 lend, InputIterator2 rit, InputIterator2 rend)
	{
		while (lit != lend)
		{
			if (rit == rend || *rit != *lit)
				return (false);
			++lit, ++rit;
		}

		return (rit == rend);
	}

	template <class T>
	bool equal (T & a, T & b)
	{
		return (a == b);
	}

	//////////////////////////////
	// Swap
	//////////////////////////////

	template <class T>
	void swap (T & a, T & b)
	{
		T	tmp = a;
		a = b;
		b = tmp;
	}
}

#endif
