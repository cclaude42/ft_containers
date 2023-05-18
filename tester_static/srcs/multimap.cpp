#include "templates/associative_container.tpp"
#include "templates/container.tpp"
#include "templates/reversible_container.tpp"
#include "templates/bidirectional_iterator.tpp"
#include "utils/basic_type.hpp"
#include <map>
#include "map.hpp"

void test_multimap()
{
	using Key = basic_type;
	using Mapped = basic_type;
	using ValueType = NAMESPACE::pair<const Key,Mapped>;
	using Compare = basic_type::compare;
	using Allocator = std::allocator <NAMESPACE::pair<const Key, Mapped> >;
	using X = NAMESPACE::multimap<Key, Mapped, Compare, Allocator>;

	Key k;
	ValueType t = NAMESPACE::pair<Key, Mapped>(Key(), Mapped());

	container<NAMESPACE::multimap<int, int>, NAMESPACE::pair<const int, int> >();

	reversible_container<X, ValueType>();

	bidirectional_iterator<typename X::iterator, ValueType>(t);
	bidirectional_iterator<typename X::reverse_iterator, ValueType>(t);

	associative_containers<
	        X,
	        Key,
			ValueType,
			Compare,
			Allocator,
			false
			>(t, k);

	static_assert(std::is_same<typename NAMESPACE::multimap<int, int>::mapped_type, int>::value, "mapped_type is not well defined");

}