#ifndef FUNCTIONAL_HPP
# define FUNCTIONAL_HPP

namespace ft
{
	//////////////////////////////
	// Size types
	//////////////////////////////

	typedef		long				ptrdiff_t;
	typedef		unsigned long		size_t;

	//////////////////////////////
	// Binary function
	//////////////////////////////

	template <class Arg1, class Arg2, class Result>
	struct binary_function {
		typedef		Arg1		first_argument_type;
		typedef		Arg2		second_argument_type;
		typedef		Result		result_type;
	};

	//////////////////////////////
	// Less
	//////////////////////////////

	template <class T>
	struct less : binary_function <T, T, bool> {
		bool operator ()		(const T & x, const T & y) const	{ return x < y; }
	};
}

# endif
