#include "templates/sequence.tpp"
#include "templates/container.tpp"
#include "templates/reversible_container.tpp"
#include "templates/random_access_iterator.tpp"
#include "utils/basic_type.hpp"
#include "stack.hpp"
#include <set>
#include <vector>

template <class C, class Container>
class check_protected : public C {
public:
	static const bool value = std::is_same<decltype(check_protected::c), Container>::value;
};

void test_stack()
{
	using ValueType = basic_type;
	using Container = std::vector<ValueType>;
	using X = NAMESPACE::stack<ValueType, Container>;
	using Xint = NAMESPACE::stack<int>;


	static_assert(std::is_same<typename X::container_type, Container>::value, "container_type is not well defined");
	static_assert(std::is_same<typename X::value_type, typename Container::value_type>::value, "value_type is not well defined");
	static_assert(std::is_same<typename X::size_type, typename Container::size_type>::value, "size_type is not well defined");

	static_assert(check_protected<X, Container>::value, "wrong type or attribute for c");

	const ValueType t;
	typename X::size_type n;
	X a((Container()));
	const X const_a(a);

	const_a.size();
	static_assert(std::is_same<decltype(const_a.size()), typename X::size_type>::value, "wrong return type for size on const container");

	const_a.empty();
	static_assert(std::is_convertible<decltype(const_a.empty()), bool>::value, "wrong return type for empty on const container");


	a.top();
	static_assert(std::is_same<decltype(a.top()), typename X::container_type::value_type &>::value, "wrong return type for top");
	const_a.top();
	static_assert(std::is_same<decltype(const_a.top()), const typename X::container_type::value_type &>::value, "wrong return type for top on const container");

	a.push(t); // void
	static_assert(std::is_same<decltype(&X::push), void (X::*)(const typename X::container_type::value_type &)>::value, "wrong prototype for push");
	a.pop(); // void
	static_assert(std::is_same<decltype(&X::pop), void (X::*)()>::value, "wrong prototype for pop");

	Xint a_int;
	const Xint const_a_int;

	(void)(a_int < a_int );
	static_assert(std::is_convertible<decltype(a_int < a_int ), bool>::value, "wrong return type for operator<(container, container)");
	(void)(a_int <  const_a_int);
	static_assert(std::is_convertible<decltype(a_int <  const_a_int), bool>::value, "wrong return type for operator<(container, const container)");
	(void)(const_a_int < a_int );
	static_assert(std::is_convertible<decltype(const_a_int < a_int ), bool>::value, "wrong return type for operator<(const container, container)");
	(void)(const_a_int <  const_a_int);
	static_assert(std::is_convertible<decltype(const_a_int <  const_a_int), bool>::value, "wrong return type for operator<(const container, const container)");

	(void)(a_int > a_int );
	static_assert(std::is_convertible<decltype(a_int > a_int ), bool>::value, "wrong return type for operator>(container, container)");
	(void)(a_int >  const_a_int);
	static_assert(std::is_convertible<decltype(a_int >  const_a_int), bool>::value, "wrong return type for operator>(container, const container)");
	(void)(const_a_int > a_int );
	static_assert(std::is_convertible<decltype(const_a_int > a_int ), bool>::value, "wrong return type for operator>(const container, container)");
	(void)(const_a_int >  const_a_int);
	static_assert(std::is_convertible<decltype(const_a_int >  const_a_int), bool>::value, "wrong return type for operator>(const container, const container)");

	(void)(a_int <= a_int );
	static_assert(std::is_convertible<decltype(a_int <= a_int ), bool>::value, "wrong return type for operator<=(container, container)");
	(void)(a_int <=  const_a_int);
	static_assert(std::is_convertible<decltype(a_int <=  const_a_int), bool>::value, "wrong return type for operator<=(container, const container)");
	(void)(const_a_int <= a_int );
	static_assert(std::is_convertible<decltype(const_a_int <= a_int ), bool>::value, "wrong return type for operator<=(const container, container)");
	(void)(const_a_int <=  const_a_int);
	static_assert(std::is_convertible<decltype(const_a_int <=  const_a_int), bool>::value, "wrong return type for operator<=(const container, const container)");

	(void)(a_int >= a_int );
	static_assert(std::is_convertible<decltype(a_int >= a_int ), bool>::value, "wrong return type for operator>=(container, container)");
	(void)(a_int >=  const_a_int);
	static_assert(std::is_convertible<decltype(a_int >=  const_a_int), bool>::value, "wrong return type for operator>=(container, const container)");
	(void)(const_a_int >= a_int );
	static_assert(std::is_convertible<decltype(const_a_int >= a_int ), bool>::value, "wrong return type for operator>=(const container, container)");
	(void)(const_a_int >=  const_a_int);
	static_assert(std::is_convertible<decltype(const_a_int >=  const_a_int), bool>::value, "wrong return type for operator>=(const container, const container)");
}