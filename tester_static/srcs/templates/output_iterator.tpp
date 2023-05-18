#ifndef OUTPUT_ITERATOR_TPP
# define OUTPUT_ITERATOR_TPP
#include <type_traits>
#include <iterator>

template <typename X, typename T>
void output_iterator(X a, T t)
{
	static_assert(std::is_convertible<typename std::iterator_traits<X>::iterator_category, std::output_iterator_tag>::value, "wrong type for iterator_category");

	(void)X(a);
	X u(a);
	X v = a;
	*a = t;

	++a;
	static_assert(std::is_same<decltype(++a), X&>::value, "wrong return type for operator++()");
	(void)(a++);
	static_assert(std::is_convertible<decltype(a++), const X&>::value, "wrong return type for operator++(int)");
	*a++ = t;
}

#endif