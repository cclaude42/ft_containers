#ifndef FORWARD_ITERATOR_TPP
# define FORWARD_ITERATOR_TPP
#include <type_traits>
#include <iterator>

template <typename X, typename T>
void forward_iterator(T t)
{
	static_assert(std::is_convertible<typename std::iterator_traits<X>::iterator_category, std::forward_iterator_tag>::value, "wrong type for iterator_category");

	X a;
	const X const_a = a;
	(void)X();
	(void)X(a);
	(void)X(const_a);
	X u(a);
	(void)u;
	X u2(const_a);
	(void)u2;
	X v = a;
	(void)v;
	X w = const_a;
	(void)w;

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

	a = a;
	static_assert(std::is_same<decltype(a = a), X&>::value, "wrong return type for operator=()");
	a = const_a;
	static_assert(std::is_same<decltype(a = const_a), X&>::value, "wrong return type for operator=(const)");

	(void)*a;
	static_assert(std::is_same<decltype(*a), T&>::value, "wrong return type for operator*()");
//	a.operator->();
//	static_assert(std::is_same<decltype(a.operator->()), T*>::value, "wrong return type for operator->()");

	++a;
	static_assert(std::is_same<decltype(++a), X&>::value, "wrong return type for operator++()");
	(void)(a++);
	static_assert(std::is_convertible<decltype(a++), const X&>::value, "wrong return type for operator++(int)");
	(void)*a++;
	static_assert(std::is_same<decltype(*a++), T&>::value, "wrong return type for *it++");


}

#endif