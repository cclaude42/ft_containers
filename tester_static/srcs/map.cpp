#include "templates/associative_container.tpp"
#include "templates/container.tpp"
#include "templates/reversible_container.tpp"
#include "templates/bidirectional_iterator.tpp"
#include <map>
#include "utils/basic_type.hpp"
#include "map.hpp"

void test_map()
{
	using Key = basic_type;
	using Mapped = basic_type;
	using ValueType = NAMESPACE::pair<const Key,Mapped>;
	using Compare = basic_type::compare;
	using Allocator = std::allocator <NAMESPACE::pair<const Key, Mapped> >;
	using X = NAMESPACE::map<Key, Mapped, Compare>;

	ValueType t = NAMESPACE::pair<const Key, Mapped>(Key(), Key());
	Key k;

	container<NAMESPACE::map<int, int>, NAMESPACE::pair<const int, int> >();

	reversible_container<X, ValueType>();

	bidirectional_iterator<typename X::iterator, ValueType>(t);
	bidirectional_iterator<typename X::reverse_iterator, ValueType>(t);

	associative_containers<
	        X,
	        Key,
			ValueType,
			Compare,
			Allocator,
			true
			>(t, k);

	static_assert(std::is_same<typename NAMESPACE::map<int, int>::mapped_type, int>::value, "mapped_type is not well defined");
	NAMESPACE::map<int, int> m;

	(void)m[(const int)1];
	static_assert(std::is_same<decltype(m[(const int)1]), int& >::value, "wrong return type for operator[]");

}