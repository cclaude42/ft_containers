#ifndef TYPES_TPP
# define TYPES_TPP

# include <iostream>

namespace ft
{
	//////////////////////////////
	// Enable If
	//////////////////////////////

	template <bool B, class T = void>
	struct enable_if {};

	template <class T>
	struct enable_if<true, T> { typedef T type; };

	//////////////////////////////
	// Is Same
	//////////////////////////////

	template <class T, class U>
	struct is_same { static const bool value = false; };

	template <class T>
	struct is_same<T, T> { static const bool value = true; };
}

#endif
