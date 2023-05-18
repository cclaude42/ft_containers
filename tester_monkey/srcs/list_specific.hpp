#ifndef LIST_SPECIFIC_HPP
# define LIST_SPECIFIC_HPP
# include "common.hpp"
# include "utils/input_iterator.hpp"


namespace list_specific
{
	template <class C>
	void	merge(C &a, C &b)
	{
		FNAME
		std::cout << "a.sort(); C c = b; c.sort(); a.merge(c)" << std::endl;
		C c = b;
		a.sort();
		c.sort();
		a.merge(c);
		std::cout << "c:" << std::endl;
		monkey::print(c);
	}

	template <class C>
	void	splice(C &a, C &b)
	{
		FNAME
		typename C::iterator pos = monkey::get_random_it(a.begin(), a.end());
		std::cout << "a.splice(pos, b) with pos = ";
		monkey::print_it(a, pos);
		std::cout << std::endl;
		a.splice(pos, b);
	}

	template <class C>
	void	remove(C &a, C &)
	{
		FNAME
		typename C::value_type value((monkey::get_value()));
		std::cout << "a.remove(value) with value = [" << value << "]" << std::endl;
		a.remove(value);
	}

	template <class C>
	void	remove_if(C &a, C &)
	{
		FNAME
		typename C::value_type value((monkey::get_value()));
		std::cout << "a.remove_if(std::bind1st(std::less<std::string>(), value)) with value = [" << value << "]" << std::endl;
		a.remove_if(std::bind1st(std::less<std::string>(), value));
	}

	template <class C>
	void	reverse(C &a, C &)
	{
		FNAME
		std::cout << "a.reverse()" << std::endl;
		a.reverse();
	}

	template <class C>
	void	sort(C &a, C &)
	{
		FNAME
		std::cout << "a.sort()" << std::endl;
		a.sort();
	}

	template <class C>
	void	unique(C &a, C &)
	{
		FNAME
		std::cout << "a.unique()" << std::endl;
		a.unique();
	}

	BUILD_TABLE(
			merge<C>,
			splice<C>,
			remove<C>,
			remove_if<C>,
			reverse<C>,
			sort<C>,
			unique<C>
	)
}

#endif