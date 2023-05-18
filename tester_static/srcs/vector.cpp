#include "templates/sequence.tpp"
#include "templates/container.tpp"
#include "templates/reversible_container.tpp"
#include "templates/random_access_iterator.tpp"
#include "utils/basic_type.hpp"
#include <set>
#include "vector.hpp"

void test_vector()
{
	using ValueType = basic_type;
	using Allocator = std::allocator <ValueType>;
	using X = NAMESPACE::vector<ValueType, Allocator>;
	using Xint = NAMESPACE::vector<int>;

	ValueType t;

	container<Xint, int>();

	reversible_container<X, ValueType>();

	random_access_iterator<typename X::iterator, ValueType>(t);
	random_access_iterator<typename X::reverse_iterator, ValueType>(t);

	sequence<
			X,
			ValueType
	>(t);


	typename X::size_type n;
	X a;
	const X const_a;

	a.front(); // reference
	static_assert(std::is_same<decltype(a.front()), typename X::reference>::value, "wrong return type for front()");

	const_a.front(); // const_reference
	static_assert(std::is_same<decltype(const_a.front()), typename X::const_reference>::value, "wrong return type for front() with const container");

	a.back(); // reference
	static_assert(std::is_same<decltype(a.back()), typename X::reference>::value, "wrong return type for back()");
	const_a.back(); // const_reference
	static_assert(std::is_same<decltype(const_a.back()), typename X::const_reference>::value, "wrong return type for back() with const container");

	a.push_back(t); // void
	static_assert(std::is_same<decltype(a.push_back(t)), void>::value, "wrong return type for push_back()");
	a.pop_back(); // void
	static_assert(std::is_same<decltype(a.pop_back()), void>::value, "wrong return type for pop_back()");

	a[n]; // reference
	static_assert(std::is_same<decltype(a[n]), typename X::reference>::value, "wrong return type for operator[](n)");
	const_a[n]; // const_reference
	static_assert(std::is_same<decltype(const_a[n]), typename X::const_reference>::value, "wrong return type for operator[](n) with const container");

	a.at(n); // reference
	static_assert(std::is_same<decltype(a.at(n)), typename X::reference>::value, "wrong return type for operator[](n)");
	const_a.at(n); // const_reference
	static_assert(std::is_same<decltype(const_a.at(n)), typename X::const_reference>::value, "wrong return type for operator[](n) with const container");

	a.resize(n);
	static_assert(std::is_same<decltype(a.resize(n)), void>::value, "wrong return type for resize(n)");
	a.resize(n, t);
	static_assert(std::is_same<decltype(a.resize(n, t)), void>::value, "wrong return type for resize(n, t)");

	const_a.capacity();
	static_assert(std::is_same<decltype(const_a.capacity()), typename X::size_type>::value, "wrong return type for capacity()");

	a.reserve(n);
	static_assert(std::is_same<decltype(a.reserve(n)), void>::value, "wrong return type for resize(n)");
}