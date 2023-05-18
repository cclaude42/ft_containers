#ifndef CONTAINER_HPP
# define CONTAINER_HPP
#include <type_traits>
#include "iterator.tpp"

template <class X, typename T>
void container()
{
	static_assert(std::is_same<typename X::value_type, T>::value, "value_type is not well defined");
	static_assert(std::is_same<typename X::reference, T &>::value, "value_type is not well defined");
	static_assert(std::is_same<typename X::const_reference, const T &>::value, "value_type is not well defined");
	static_assert(std::is_signed<typename X::difference_type>::value, "difference_type is not a signed type");
	static_assert(std::is_integral<typename X::difference_type>::value, "difference_type is not an integral type");
	static_assert(std::is_unsigned<typename X::size_type>::value, "size_type is not an unsigned type");
	static_assert(std::is_integral<typename X::size_type>::value, "size_type is not an integral type");

	iterator<typename X::iterator, T, T>();
	iterator<typename X::const_iterator, T, const T>();

	X a;
	const X const_a;
	(void)X();
	(void)X(a);
	{ X u(a); }
	{
		X u = a;
	}

	a.begin();
	static_assert(std::is_same<decltype(a.begin()), typename X::iterator>::value, "wrong return type for begin()");
	const_a.begin();
	static_assert(std::is_same<decltype(const_a.begin()), typename X::const_iterator>::value, "wrong return type for begin() on const container");
	a.end();
	static_assert(std::is_same<decltype(a.end()), typename X::iterator>::value, "wrong return type for end()");
	const_a.end();
	static_assert(std::is_same<decltype(const_a.end()), typename X::const_iterator>::value, "wrong return type for end() on const container");

	(void)(a == a);
	static_assert(std::is_convertible<decltype(a == a), bool>::value, "wrong return type for operator==(container, container)");
	(void)(a == const_a);
	static_assert(std::is_convertible<decltype(a == const_a), bool>::value, "wrong return type for operator==(container, const container)");
	(void)(const_a == a);
	static_assert(std::is_convertible<decltype(const_a == a), bool>::value, "wrong return type for operator==(const container, container)");
	(void)(const_a == const_a);
	static_assert(std::is_convertible<decltype(const_a == const_a), bool>::value, "wrong return type for operator==(const container, const container)");

	(void)(a != a);
	static_assert(std::is_convertible<decltype(a != a), bool>::value, "wrong return type for operator!=(container, container)");
	(void)(a != const_a);
	static_assert(std::is_convertible<decltype(a != const_a), bool>::value, "wrong return type for operator!=(container, const container)");
	(void)(const_a != a);
	static_assert(std::is_convertible<decltype(const_a != a), bool>::value, "wrong return type for operator!=(const container, container)");
	(void)(const_a != const_a);
	static_assert(std::is_convertible<decltype(const_a != const_a), bool>::value, "wrong return type for operator!=(const container, const container)");

	a.swap(a);
	static_assert(std::is_same<decltype(a.swap(a)), void>::value, "wrong return type for swap");

	a = a;
	static_assert(std::is_same<decltype(a = a), X&>::value, "wrong return type for operator=()");
	a = const_a;
	static_assert(std::is_same<decltype(a = const_a), X&>::value, "wrong return type for operator=(const)");


	a.size();
	static_assert(std::is_same<decltype(a.size()), typename X::size_type>::value, "wrong return type for size");
	const_a.size();
	static_assert(std::is_same<decltype(const_a.size()), typename X::size_type>::value, "wrong return type for size on const container");

	a.max_size();
	static_assert(std::is_same<decltype(a.max_size()), typename X::size_type>::value, "wrong return type for max_size");
	const_a.max_size();
	static_assert(std::is_same<decltype(const_a.max_size()), typename X::size_type>::value, "wrong return type for max_size on const container");

	const_a.empty();
	static_assert(std::is_convertible<decltype(const_a.empty()), bool>::value, "wrong return type for empty on const container");

	a.clear();
	static_assert(std::is_same<decltype(a.clear()), void>::value, "Wrong return type for clear()");

	(void)(a < a);
	static_assert(std::is_convertible<decltype(a < a), bool>::value, "wrong return type for operator<(container, container)");
	(void)(a < const_a);
	static_assert(std::is_convertible<decltype(a < const_a), bool>::value, "wrong return type for operator<(container, const container)");
	(void)(const_a < a);
	static_assert(std::is_convertible<decltype(const_a < a), bool>::value, "wrong return type for operator<(const container, container)");
	(void)(const_a < const_a);
	static_assert(std::is_convertible<decltype(const_a < const_a), bool>::value, "wrong return type for operator<(const container, const container)");

	(void)(a > a);
	static_assert(std::is_convertible<decltype(a > a), bool>::value, "wrong return type for operator>(container, container)");
	(void)(a > const_a);
	static_assert(std::is_convertible<decltype(a > const_a), bool>::value, "wrong return type for operator>(container, const container)");
	(void)(const_a > a);
	static_assert(std::is_convertible<decltype(const_a > a), bool>::value, "wrong return type for operator>(const container, container)");
	(void)(const_a > const_a);
	static_assert(std::is_convertible<decltype(const_a > const_a), bool>::value, "wrong return type for operator>(const container, const container)");

	(void)(a <= a);
	static_assert(std::is_convertible<decltype(a <= a), bool>::value, "wrong return type for operator<=(container, container)");
	(void)(a <= const_a);
	static_assert(std::is_convertible<decltype(a <= const_a), bool>::value, "wrong return type for operator<=(container, const container)");
	(void)(const_a <= a);
	static_assert(std::is_convertible<decltype(const_a <= a), bool>::value, "wrong return type for operator<=(const container, container)");
	(void)(const_a <= const_a);
	static_assert(std::is_convertible<decltype(const_a <= const_a), bool>::value, "wrong return type for operator<=(const container, const container)");

	(void)(a >= a);
	static_assert(std::is_convertible<decltype(a >= a), bool>::value, "wrong return type for operator>=(container, container)");
	(void)(a >= const_a);
	static_assert(std::is_convertible<decltype(a >= const_a), bool>::value, "wrong return type for operator>=(container, const container)");
	(void)(const_a >= a);
	static_assert(std::is_convertible<decltype(const_a >= a), bool>::value, "wrong return type for operator>=(const container, container)");
	(void)(const_a >= const_a);
	static_assert(std::is_convertible<decltype(const_a >= const_a), bool>::value, "wrong return type for operator>=(const container, const container)");
}

#endif