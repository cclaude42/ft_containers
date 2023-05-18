#ifndef ASSOCIATIVE_HPP
# define ASSOCIATIVE_HPP
# include "common.hpp"
# include "utils/input_iterator.hpp"


namespace associative
{
	template <class C>
	void	range_constructor(C &a, C &)
	{
		FNAME
		std::vector<typename C::value_type> v = monkey::get_random_vector<typename C::value_type>();

		std::cout << "a = C(range) with range: " << std::endl;
		monkey::print_range(v.begin(), v.end());

		a = C(input_iterator<typename std::vector<typename C::value_type>::iterator>(v.begin()), input_iterator<typename std::vector<typename C::value_type>::iterator>(v.end()));
	}

	template <class C>
	void key_comp(C &a, C &b)
	{
		FNAME
		std::cout << "a.key_comp() == b.key_comp(): " << (a.key_comp() == b.key_comp()) << std::endl;
	}

	// little hack to handle the two version of insert(value) (multi and uniq)
	template <class C>
	void print_insert_value_ret(C &a, typename C::iterator ret)
	{
		std::cout << "ret = ";
		monkey::print_it(a, ret);
		std::cout << std::endl;
	}

	template <class C>
	void print_insert_value_ret(C &a, NAMESPACE::pair<typename C::iterator, bool> ret)
	{
		std::cout << "ret = ";
		monkey::print_it(a, ret.first);
		std::cout << ", " << ret.second << std::endl;
	}

	template <class C>
	void	insert_value(C &a, C &)
	{
		FNAME
		typename C::value_type value((monkey::get_value()));

		std::cout << "a.insert(value) with value = [" << value << "]" << std::endl;
		print_insert_value_ret<C>(a, a.insert(value));
	}

	template <class C>
	void	insert_hint(C &a, C &)
	{
		FNAME
		typename C::value_type value((monkey::get_value()));
		typename C::iterator hint = monkey::get_random_it(a.begin(), a.end());
		std::cout << "a.insert(hint, value) with hint: ";
		monkey::print_it(a, hint);
		std::cout << " and value: [" << value << "]" << std::endl;
		typename C::iterator ret = a.insert(hint, value);
		std::cout << "ret = ";
		monkey::print_it(a, ret);
		std::cout << std::endl;
	}

	template <class C>
	void	insert_range(C &a, C &)
	{
		FNAME
		std::vector<typename C::value_type> range = monkey::get_random_vector<typename C::value_type>();
		std::cout << "a.insert(range) with range: ";
		monkey::print_range(range.begin(), range.end());
		std::cout << std::endl;

		a.insert(input_iterator<typename std::vector<typename C::value_type>::iterator>(range.begin()), input_iterator<typename std::vector<typename C::value_type>::iterator>(range.end()));
	}

	template <class C>
	void	erase_value(C &a, C &)
	{
		FNAME
		typename C::key_type value((monkey::get_value()));

		std::cout << "a.erase(value) with value = [" << value << "]" << std::endl;
		typename C::size_type ret = a.erase(value);
		std::cout << "ret = " << ret << std::endl;
	}

	template <class C>
	void	erase_it(C &a, C &)
	{
		FNAME
		if (a.size() == 0)
			return;
		typename C::iterator it = monkey::get_random_it(a.begin(), --a.end());

		std::cout << "a.erase(it) with it = ";
		monkey::print_it(a, it);
		std::cout << std::endl;
		a.erase(it);
	}

	template <class C>
	void	erase_range(C &a, C &)
	{
		FNAME
		typename C::iterator it1 = monkey::get_random_it(a.begin(), a.end());
		typename C::iterator it2 = monkey::get_random_it(it1, a.end());

		std::cout << "a.erase(it1, it2) with it1 = ";
		monkey::print_it(a, it1);
		std::cout << " and it2 = ";
		monkey::print_it<C>(a, it2);
		std::cout << std::endl;
		a.erase(it1, it2);
	}


	template <class C>
	void	find(C &a, C &)
	{
		FNAME
		typename C::key_type key((monkey::get_value()));
		std::cout << "a.find(key) with k = " << key << std::endl;
		typename C::iterator ret = a.find(key);
		std::cout << "ret = ";
		monkey::print_it(a, ret);
		std::cout << std::endl;
	}

	template <class C>
	void	lower_bound(C &a, C &)
	{
		FNAME
		typename C::key_type key((monkey::get_value()));
		std::cout << "a.lower_bound(key) with k = " << key << std::endl;
		typename C::iterator ret = a.lower_bound(key);
		std::cout << "ret = ";
		monkey::print_it(a, ret);
		std::cout << std::endl;
	}

	template <class C>
	void	upper_bound(C &a, C &)
	{
		FNAME
		typename C::key_type key((monkey::get_value()));
		std::cout << "a.upper_bound(key) with k = " << key << std::endl;
		typename C::iterator ret = a.upper_bound(key);
		std::cout << "ret = ";
		monkey::print_it(a, ret);
		std::cout << std::endl;
	}

	template <class C>
	void	equal_range(C &a, C &)
	{
		FNAME
		typename C::key_type key((monkey::get_value()));
		std::cout << "a.equal_range(key) with k = " << key << std::endl;
		NAMESPACE::pair<typename C::iterator, typename C::iterator> ret = a.equal_range(key);
		std::cout << "ret = {";
		monkey::print_it(a, ret.first);
		std::cout << ", ";
		monkey::print_it(a, ret.second);
		std::cout << "}" << std::endl;
	}

	BUILD_TABLE(
			associative::key_comp<C>,
			associative::insert_hint<C>,
			associative::insert_hint<C>,
			associative::insert_range<C>,
			associative::insert_range<C>,
			associative::insert_value<C>,
			associative::insert_value<C>,
			associative::insert_value<C>,
			associative::erase_it<C>,
			associative::erase_range<C>,
			associative::erase_value<C>,
			associative::find<C>,
			associative::lower_bound<C>,
			associative::upper_bound<C>,
			associative::equal_range<C>
	)
}

#endif