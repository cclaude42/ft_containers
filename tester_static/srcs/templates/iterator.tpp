#ifndef ITERATOR_TPP
# define ITERATOR_TPP
# include <type_traits>
# include <iterator>

template <typename X, typename T, typename Pointed>
void iterator()
{
	static_assert(std::is_integral<typename std::iterator_traits<X>::difference_type>::value, "iterator difference_type is not integral");
	static_assert(std::is_signed<typename std::iterator_traits<X>::difference_type>::value, "iterator difference_type is not signed");
//	static_assert(std::is_same<typename std::iterator_traits<X>::value_type, T>::value, "wrong type for iterator value_type");
//	static_assert(std::is_same<typename std::iterator_traits<X>::pointer, Pointed*>::value, "wrong type for iterator pointer");
//	static_assert(std::is_same<typename std::iterator_traits<X>::reference, Pointed&>::value, "wrong type for iterator reference");
}

#endif