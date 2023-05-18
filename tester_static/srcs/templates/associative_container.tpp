#ifndef ASSOCIATIVE_CONTAINER_TPP
# define ASSOCIATIVE_CONTAINER_TPP
# include <type_traits>
# ifndef NAMESPACE
# define NAMESPACE std
# endif
# include "includes/utility.hpp"
# include <utility>
#include "../utils/dummy_iterators.hpp"
#include "assignable.tpp"

template <class X,
		class	Key,
		class	ValueType,
		class	Compare,
		class	Allocator,
		bool	uniq>
void	associative_containers(const ValueType t, const Key k)
{
	static_assert(std::is_same<typename X::key_type, Key>::value, "key_type is not well defined");
	static_assert(std::is_assignable<typename X::key_type &, typename X::key_type>::value, "key_type is not assignable");
	Key tmp(k);
	assignable<typename X::key_type>(tmp);
	static_assert(std::is_same<typename X::key_compare, Compare>::value, "key_compare is not well defined");
	dummy_input_iterator<ValueType> i(t), j(t);
	Compare c;
	X a(c);
	const X const_a(c);
	(void)X();
	(void)X(i, j, c);
	(void)X(i, j);
	const_a.key_comp();
	static_assert(std::is_same<typename std::result_of<decltype(&X::key_comp)(X)>::type, Compare>::value, "key_comp() does not return a key_compare object");
	const_a.value_comp();
	static_assert(std::is_same<typename std::result_of<decltype(&X::value_comp)(X)>::type, typename X::value_compare>::value, "value_comp() does not return a value_compare object");
	a.insert(t);
	static_assert(std::is_same<decltype(a.insert(t)), typename std::conditional<uniq, NAMESPACE::pair<typename X::iterator, bool>, typename X::iterator>::type>::value, "Wrong return type for insert(value)");
	a.insert(a.begin(), t);
	static_assert(std::is_same<decltype(a.insert(a.begin(), t)), typename X::iterator>::value, "wrong return type for insert(it, val)");
	a.insert(i, j);
	static_assert(std::is_same<decltype(a.insert(i, j)), void>::value, "wrong return type for insert(it1, it2)");
	a.erase(k);
	static_assert(std::is_same<decltype(a.erase(k)), typename X::size_type>::value, "wrong return type for erase(key)");

	// these test will fail with std::map since the return type of erase change between c++98 and c++11 and the tester is compiled in c++11.
	a.erase(a.begin());
	static_assert(std::is_same<decltype(a.erase(a.begin())), void>::value, "wrong return type for erase(it)");
	a.erase(a.begin(), a.end());

	static_assert(std::is_same<decltype(a.erase(a.begin(), a.end())), void>::value, "wrong return type for erase(it1, it2)");
	a.find(k);
	static_assert(std::is_same<decltype(a.find(k)), typename X::iterator>::value, "wrong return type for find");
	const_a.find(k);
	static_assert(std::is_same<decltype(const_a.find(k)), typename X::const_iterator>::value, "wrong return type for find on const container");
	a.lower_bound(k);
	static_assert(std::is_same<decltype(a.lower_bound(k)), typename X::iterator>::value, "wrong return type for lower_bound");
	const_a.lower_bound(k);
	static_assert(std::is_same<decltype(const_a.lower_bound(k)), typename X::const_iterator>::value, "wrong return type for lower_bound on const container");
	a.upper_bound(k);
	static_assert(std::is_same<decltype(a.upper_bound(k)), typename X::iterator>::value, "wrong return type for upper_bound");
	const_a.upper_bound(k);
	static_assert(std::is_same<decltype(const_a.upper_bound(k)), typename X::const_iterator>::value, "wrong return type for upper_bound on const container");
	a.equal_range(k);
	static_assert(std::is_same<decltype(a.equal_range(k)), NAMESPACE::pair<typename X::iterator, typename X::iterator> >::value, "wrong return type for equal_range");
	const_a.equal_range(k);
	static_assert(std::is_same<decltype(const_a.equal_range(k)), NAMESPACE::pair<typename X::const_iterator, typename X::const_iterator> >::value, "wrong return type for equal_range on const container");

}

#endif