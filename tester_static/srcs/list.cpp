#include "templates/sequence.tpp"
#include "templates/container.tpp"
#include "templates/reversible_container.tpp"
#include "templates/bidirectional_iterator.tpp"
#include "utils/basic_type.hpp"
#include <set>
#include "list.hpp"
#include <functional>

void test_vector()
{
	using ValueType = basic_type;
	using Allocator = std::allocator <ValueType>;
	using X = NAMESPACE::list<ValueType>;
	using Xint = NAMESPACE::list<int>;

	ValueType t;

	container<Xint, int>();

	reversible_container<X, ValueType>();

	bidirectional_iterator<typename X::iterator, ValueType>(t);
	bidirectional_iterator<typename X::reverse_iterator, ValueType>(t);

	sequence<
			X,
			ValueType
	>(t);


	typename X::size_type n;
	X a;
	const X const_a;
	Xint a_int;

	a.front(); // reference
	static_assert(std::is_same<decltype(a.front()), typename X::reference>::value, "wrong return type for front()");

	const_a.front(); // const_reference
	static_assert(std::is_same<decltype(const_a.front()), typename X::const_reference>::value, "wrong return type for front() with const container");

	a.back(); // reference
	static_assert(std::is_same<decltype(a.back()), typename X::reference>::value, "wrong return type for back()");
	const_a.back(); // const_reference
	static_assert(std::is_same<decltype(const_a.back()), typename X::const_reference>::value, "wrong return type for back() with const container");

	a.push_front(t); // void
	static_assert(std::is_same<decltype(a.push_front(t)), void>::value, "wrong return type for push_front()");
	a.push_back(t); // void
	static_assert(std::is_same<decltype(a.push_back(t)), void>::value, "wrong return type for push_back()");
	a.pop_front(); // void
	static_assert(std::is_same<decltype(a.pop_front()), void>::value, "wrong return type for pop_front()");
	a.pop_back(); // void
	static_assert(std::is_same<decltype(a.pop_back()), void>::value, "wrong return type for pop_back()");

	a.resize(n);
	static_assert(std::is_same<decltype(a.resize(n)), void>::value, "wrong return type for resize(n)");
	a.resize(n, t);
	static_assert(std::is_same<decltype(a.resize(n, t)), void>::value, "wrong return type for resize(n, t)");

	a.splice(a.begin(), a);
	static_assert(std::is_same<decltype(a.splice(a.begin(), a)), void>::value, "wrong return type for splice(it, other)");
	a.splice(a.begin(), a, a.begin());
	static_assert(std::is_same<decltype(a.splice(a.begin(), a, a.begin())), void>::value, "wrong return type for splice(it, other, other_it)");
	a.splice(a.begin(), a, a.begin(), a.begin());
	static_assert(std::is_same<decltype(a.splice(a.begin(), a, a.begin(), a.begin())), void>::value, "wrong return type for splice(it, other, other_first, other_last)");

	a_int.remove(0);
	static_assert(std::is_same<decltype(a_int.remove(0)), void>::value, "wrong return type for remove(value)");
	a.remove_if(basic_type::unary_predicate());
	static_assert(std::is_same<decltype(a.remove_if(basic_type::unary_predicate())), void>::value, "wrong return type for remove_if(pred)");

	a_int.unique();
	static_assert(std::is_same<decltype(a_int.unique()), void>::value, "wrong return type for unique()");
	a.unique<basic_type::compare>(basic_type::compare());
	static_assert(std::is_same<decltype(a.unique<basic_type::compare >(basic_type::compare())), void>::value, "wrong return type for unique(pred)");

	a_int.merge(a_int);
	static_assert(std::is_same<decltype(a_int.merge(a_int)), void>::value, "wrong return type for merge(other)");
	// a.merge(a, basic_type::compare());
	// static_assert(std::is_same<decltype(a.merge(a, basic_type::compare())), void>::value, "wrong return type for merge(other, compare)");

	a.reverse();
	static_assert(std::is_same<decltype(a.reverse()), void>::value, "wrong return type for reverse()");


	a_int.sort();
	static_assert(std::is_same<decltype(a_int.sort()), void>::value, "wrong return type for sort()");
	a.sort(basic_type::compare());
	static_assert(std::is_same<decltype(a.sort(basic_type::compare())), void>::value, "wrong return type for sort(compare)");

}