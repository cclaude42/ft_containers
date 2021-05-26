#ifndef TYPE_TRAITS_HPP
# define TYPE_TRAITS_HPP

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

	//////////////////////////////
	// Conditional
	//////////////////////////////

	template <bool B, class T = void, class U = void>
	struct conditional {};

	template <class T, class U>
	struct conditional<true, T, U> { typedef T type; };

	template <class T, class U>
	struct conditional<false, T, U> { typedef U type; };
}

#endif
