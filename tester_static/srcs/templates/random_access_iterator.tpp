#ifndef RANDOM_ACCESS_ITERATOR_TPP
#define RANDOM_ACCESS_ITERATOR_TPP
#include "bidirectional_iterator.tpp"
#include "iterator"

template <typename X, typename T>
void random_access_iterator(T t)
{
	bidirectional_iterator<X, T>(t);
	static_assert(std::is_convertible<typename std::iterator_traits<X>::iterator_category, std::random_access_iterator_tag>::value, "wrong type for iterator_category");

	X r;
	const X const_r = r;

	typedef typename std::iterator_traits<X>::difference_type Distance;
	const Distance n = 0;

	r += n;
	static_assert(std::is_same<decltype(r += n), X&>::value, "wrong return type for operator+=(difference_type)");
	(void)(X(r) + n);
	static_assert(std::is_same<decltype(X(r) + n), X>::value, "wrong return type for operator+(iterator, difference_type)");
	(void)(n + X(r));
	static_assert(std::is_same<decltype(n + X(r)), X>::value, "wrong return type for operator+(difference_type, iterator)");
	(void)(r -= n);
	static_assert(std::is_same<decltype(r -= n), X&>::value, "wrong return type for operator-=(difference_type)");
	(void)(X(r) - n);
	static_assert(std::is_same<decltype(X(r) - n), X>::value, "wrong return type for operator-(iterator, difference_type)");
	(void)(X(r) - X(r));
	static_assert(std::is_same<decltype(X(r) - X(r)), Distance>::value, "wrong return type for operator-(iterator, iterator)");

	(void)((X(r))[n]);
	static_assert(std::is_convertible<decltype((X(r))[n]), T>::value, "wrong return type for operator[]()");

	X a(r);
	X const_a(r);

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