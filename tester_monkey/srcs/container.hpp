#ifndef CONTAINER_HPP
# define CONTAINER_HPP
# include "common.hpp"

namespace container {
	template<class C>
	void empty(C &a, C &b) {
		FNAME
		std::cout << "a.empty() = " << a.empty() << std::endl;
		std::cout << "b.empty() = " << b.empty() << std::endl;
	}

	template<class C>
	void swap(C &a, C &b) {
		FNAME
		std::cout << "a.swap(b)" << std::endl;
		a.swap(b);
	}

	template<class C>
	void default_constructor(C &a, C &)
	{
		FNAME
		std::cout << "a = C()" << std::endl;
		a = C();
	}

	template<class C>
	void copy_constructor(C &a, C &) {
		FNAME
		std::cout << "a = C(a)" << std::endl;
		a = C(a);
	}

	template<class C>
	void operator_assign(C &a, C &b) {
		FNAME
		C c = a;
		std::cout << "C c = a" << std::endl;
		std::cout << "print c:" << std::endl;
		monkey::print(c);

		a = b;
		std::cout << "a = b" << std::endl;
		std::cout << "print a:" << std::endl;
		monkey::print(a);
	}

	template<class C>
	void comparison(C &a, C &b) {
		FNAME
		std::cout << "a < b: " << (a < b) << std::endl;
		std::cout << "a > b: " << (a > b) << std::endl;
		std::cout << "a <= b: " << (a <= b) << std::endl;
		std::cout << "a >= b: " << (a >= b) << std::endl;
		std::cout << "a == b: " << (a == b) << std::endl;
		std::cout << "a != b: " << (a != b) << std::endl;
	}

	template <class C>
	void reverse_iterators(C &a, C &b)
	{
		FNAME
		std::cout << "reverse_printing a" << std::endl;
		for (typename C::reverse_iterator it = a.rbegin(); it != a.rend(); it++)
			std::cout << "-> [" << *it << "]" << std::endl;	}

	template <class C>
	void	clear(C &a, C &)
	{
		a.clear();
	}

	BUILD_TABLE(
			default_constructor<C>,
			empty<C>,
			swap<C>,
			copy_constructor<C>,
			operator_assign<C>,
			reverse_iterators<C>,
			clear<C>,
			comparison<C>
			)
}

#endif