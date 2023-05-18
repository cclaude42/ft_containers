#include "templates/sequence.tpp"
#include "templates/container.tpp"
#include "templates/reversible_container.tpp"
#include "templates/random_access_iterator.tpp"
#include "utils/basic_type.hpp"
#include "queue.hpp"
#include <set>
#include <vector>

template <class C, class Container, class Compare>
class check_protected : public C {
public:
	static const bool check_c = std::is_same<decltype(check_protected::c), Container>::value;
	static const bool check_comp = std::is_same<decltype(check_protected::comp), Compare>::value;
};

void test_vector()
{
	using ValueType = basic_type;
	using Container = std::vector<ValueType>;
	using Compare = basic_type::compare;
	using X = NAMESPACE::priority_queue<ValueType, Container, basic_type::compare>;


	static_assert(std::is_same<typename X::container_type, Container>::value, "container_type is not well defined");
	static_assert(std::is_same<typename X::value_type, typename Container::value_type>::value, "value_type is not well defined");
	static_assert(std::is_same<typename X::size_type, typename Container::size_type>::value, "size_type is not well defined");

	static_assert(check_protected<X, Container, Compare>::check_c, "wrong type or attribute for c");
	static_assert(check_protected<X, Container, Compare>::check_comp, "wrong type or attribute for comp");

	const ValueType t;
	typename X::size_type n;
	X a((Compare()), (Container()));
	const X const_a(a);
	dummy_input_iterator<ValueType> i(t), j(t);
	(void)(X(i, j, Compare(), Container()));

	const_a.size();
	static_assert(std::is_same<decltype(const_a.size()), typename X::size_type>::value, "wrong return type for size on const container");

	const_a.empty();
	static_assert(std::is_convertible<decltype(const_a.empty()), bool>::value, "wrong return type for empty on const container");


	const_a.top();
	static_assert(std::is_same<decltype(&X::top), const typename X::container_type::value_type & (X::*)() const>::value, "wrong prototype for top");

	a.push(t);
	static_assert(std::is_same<decltype(&X::push), void (X::*)(const typename X::container_type::value_type &)>::value, "wrong prototype for push");
	a.pop();
	static_assert(std::is_same<decltype(&X::pop), void (X::*)()>::value, "wrong prototype for pop");
}