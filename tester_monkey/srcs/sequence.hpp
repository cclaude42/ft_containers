#ifndef SEQUENCE_HPP
# define SEQUENCE_HPP
# include "common.hpp"
# include "utils/input_iterator.hpp"
#ifdef TEST_FT
# include "exception.hpp"
#else
# include <exception>
#endif


namespace sequence
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
	void	count_constructor(C &a, C &)
	{
		FNAME
		typename C::value_type	value = monkey::get_value();
		typename C::size_type	count = rand() % BASE_SIZE;

		std::cout << "a = C(count, value) with count = " << count << " and value = " << value << std::endl;
		a = C(count, value);
	}

	template <class C>
	void	insert_value(C &a, C &)
	{
		FNAME
		typename C::value_type value((monkey::get_value()));
		typename C::iterator pos = monkey::get_random_it(a.begin(), a.end());
		std::cout << "a.insert(pos, value) with pos: ";
		monkey::print_it(a, pos);
		std::cout << " and value: [" << value << "]" << std::endl;
		typename C::iterator ret = a.insert(pos, value);
		std::cout << "ret = ";
		monkey::print_it(a, ret);
		std::cout << std::endl;
	}


	template <class C>
	void	insert_range(C &a, C &)
	{
		FNAME
		typename C::iterator pos = monkey::get_random_it(a.begin(), a.end());
		std::vector<typename C::value_type> range = monkey::get_random_vector<typename C::value_type>();
		std::cout << "a.insert(range) with range = ";
		monkey::print_range(range.begin(), range.end());
		std::cout << " and pos = " << std::endl;
		monkey::print_it(a, pos);
		a.insert(pos, input_iterator<typename std::vector<typename C::value_type>::iterator>(range.begin()), input_iterator<typename std::vector<typename C::value_type>::iterator>(range.end()));
	}


	template <class C>
	void	insert_count(C &a, C &)
	{
		FNAME
		typename C::iterator pos = monkey::get_random_it(a.begin(), a.end());
		typename C::size_type	count = rand() % BASE_SIZE;
		typename C::value_type	value = monkey::get_value();
		std::cout << "a.insert(pos, count, value) with pos = ";
		monkey::print_it(a, pos);
		std::cout << ", count = " << count << " and value = " << value << std::endl;
		a.insert(pos, count, value);
	}

	template <class C>
	void	erase_it(C &a, C &)
	{
		FNAME
		if (a.size() == 0)
			return;
		typename C::iterator it = monkey::get_random_it(a.begin(), monkey::prev(a.end()));

		std::cout << "a.erase(it) with it = ";
		monkey::print_it(a, it);
		std::cout << std::endl;
		typename C::iterator ret = a.erase(it);
		std::cout << "ret = ";
		monkey::print_it(a, ret);
		std::cout << std::endl;
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
		typename C::iterator ret = a.erase(it1, it2);
		std::cout << "ret = ";
		monkey::print_it(a, ret);
		std::cout << std::endl;
	}

	template <class C>
	void	at(C &a, C &)
	{
		FNAME
		typename C::size_type	pos = rand() % BASE_SIZE;


		std::cout << "a.at(pos) with pos = " << pos << std::endl;
		try {
			std::cout << " ret = " << a.at(pos) << std::endl;
		}
		catch (NAMESPACE::exception)
		{
			std::cout << "exception thrown" << std::endl;
		}
	}

	template <class C>
	void	operator_at(C &a, C &)
	{
		FNAME
		if (a.empty())
			return;
		typename C::size_type	pos = rand() % a.size();

		std::cout << "a[pos] with pos = " << pos << std::endl;
		std::cout << "ret = " << a[pos] << std::endl;
	}

	template <class C>
	void	front(C &a, C &)
	{
		FNAME
		if (a.empty())
			return;
		std::cout << "a.front() = " << a.front() << std::endl;
	}

	template <class C>
	void	back(C &a, C &)
	{
		FNAME
		if (a.empty())
			return;
		std::cout << "a.back() = " << a.back() << std::endl;
	}

	template <class C>
	void	push_back(C &a, C &)
	{
		FNAME
		typename C::value_type value((monkey::get_value()));
		std::cout << "a.push_back(value) with value = [" << value << "]" << std::endl;
		a.push_back(value);
	}

	template <class C>
	void	pop_back(C &a, C &)
	{
		FNAME
		if (a.empty())
			return;
		std::cout << "a.pop_back()" << std::endl;
		a.pop_back();
	}

	template <class C>
	void	push_front(C &a, C &)
	{
		FNAME
		typename C::value_type value((monkey::get_value()));
		std::cout << "a.push_front(value) with value = [" << value << "]" << std::endl;
		a.push_front(value);
	}

	template <class C>
	void	pop_front(C &a, C &)
	{
		FNAME
		if (a.empty())
			return;
		std::cout << "a.pop_front()" << std::endl;
		a.pop_front();
	}

	template <class C>
	void	resize(C &a, C &)
	{
		FNAME
		typename C::size_type	count = rand() % BASE_SIZE;
		typename C::value_type	value = monkey::get_value();
		std::cout << "a.resize(n, value) with n = " << count  << " and value = " << value << std::endl;
	}


	BUILD_TABLE(
			erase_range<C>,
			erase_it<C>,
			insert_count<C>,
			insert_range<C>,
			insert_value<C>,
			count_constructor<C>,
			range_constructor<C>,

			front<C>,
			back<C>,
			push_back<C>,
			pop_back<C>,
			resize<C>
	)
}

#endif