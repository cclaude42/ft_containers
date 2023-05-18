#ifndef REVERSIBLE_CONTAINER_HPP
# define REVERSIBLE_CONTAINER_HPP
#include <type_traits>

template <class X, typename T>
void reversible_container()
{
	X a;
	const X const_a;
	a.rbegin();
	static_assert(std::is_same<decltype(a.rbegin()), typename X::reverse_iterator>::value, "wrong return type for rbegin()");
	const_a.rbegin();
	static_assert(std::is_same<decltype(const_a.rbegin()), typename X::const_reverse_iterator>::value, "wrong return type for rbegin() on const container");
	a.rend();
	static_assert(std::is_same<decltype(a.rend()), typename X::reverse_iterator>::value, "wrong return type for rend()");
	const_a.rend();
	static_assert(std::is_same<decltype(const_a.rend()), typename X::const_reverse_iterator>::value, "wrong return type for rend() on const container");
}
#endif