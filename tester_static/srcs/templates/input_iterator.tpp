#ifndef INPUT_ITERATOR_HPP
# define INPUT_ITERATOR_HPP
#include <type_traits>
#include <iterator>

template <typename X, typename T>
void input_iterator(X a)
{
	static_assert(std::is_convertible<typename std::iterator_traits<X>::iterator_category, std::input_iterator_tag>::value, "wrong type for iterator_category");

	X u(a);
	const X const_a(a);
	u = a;

	a = a;
	static_assert(std::is_same<decltype(a = a), X&>::value, "wrong return type for operator=()");
	a = const_a;
	static_assert(std::is_same<decltype(a = const_a), X&>::value, "wrong return type for operator=(const)");

	(void)(a == a);
	static_assert(std::is_convertible<decltype(a == a), bool>::value, "wrong return type for operator==(iterator, iterator)");
	(void)(a == const_a);
	static_assert(std::is_convertible<decltype(a == const_a), bool>::value, "wrong return type for operator==(iterator, const iterator)");
	(void)(const_a == a);
	static_assert(std::is_convertible<decltype(const_a == a), bool>::value, "wrong return type for operator==(const iterator, iterator)");
	(void)(const_a == const_a);
	static_assert(std::is_convertible<decltype(const_a == const_a), bool>::value, "wrong return type for operator==(const iterator, const iterator)");

	(void)(a != a);
	static_assert(std::is_convertible<decltype(a != a), bool>::value, "wrong return type for operator!=(iterator, iterator)");
	(void)(a != const_a);
	static_assert(std::is_convertible<decltype(a != const_a), bool>::value, "wrong return type for operator!=(iterator, const iterator)");
	(void)(const_a != a);
	static_assert(std::is_convertible<decltype(const_a != a), bool>::value, "wrong return type for operator!=(const iterator, iterator)");
	(void)(const_a != const_a);
	static_assert(std::is_convertible<decltype(const_a != const_a), bool>::value, "wrong return type for operator!=(const iterator, const iterator)");

	*a;
	static_assert(std::is_convertible<decltype(*a), T>::value, "wrong return type for operator*()");
//	a.operator->();
//	static_assert(std::is_convertible<decltype(a.operator->()), T*>::value, "wrong return type for operator->()");

	++a;
	static_assert(std::is_same<decltype(++a), X&>::value, "wrong return type for operator++()");
	(void)(a++);
	*a++;
	static_assert(std::is_same<decltype(*a++), T>::value, "wrong return type for *it++");
}

#endif