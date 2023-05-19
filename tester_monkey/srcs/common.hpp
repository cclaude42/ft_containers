#ifndef COMMON_HPP
# define COMMON_HPP
# include <iostream>
# include <vector>
# include <algorithm>
# include <queue>
# include <list>
# ifndef NAMESPACE
#  define NAMESPACE std
# endif
// the variable BASE_SIZE define the order of magnitude of the containers
// (for example when inserting a range, the size of the range will be something like rand() % BASE_SIZE)
# ifndef BASE_SIZE
#  define BASE_SIZE 20
# endif
// this macro will print the name of the calling function with a pretty formatting
# define FNAME {monkey::print_title(__FUNCTION__);}
// create a function get_table that return a table of function containing the functions passed as arguments
# define BUILD_TABLE(...)	\
template <class C> \
monkey::function_table<C> get_table () \
{\
	typename monkey::function_table<C>::function_type array[] = { __VA_ARGS__ };\
	return monkey::function_table<C>(array, sizeof(array) / sizeof (*array));\
}

#if defined(TEST_MAP) || defined(TEST_SET) || defined(TEST_MULTIMAP) || defined (TEST_MULTISET)
# ifdef TEST_FT
#  include "includes/utility.hpp"
# else
#  include <utility>
# endif
// print a pair
template<typename A, typename B>
std::ostream &operator<<(std::ostream &s, NAMESPACE::pair<A, B> p) {
	return s << "{" << p.first << ", " << p.second << "}";
}
#endif

namespace monkey {

	// this class return a random value of the desired type (can be used like a function)
	class get_value
	{
	public:
		operator int()
		{
			if (!(std::rand() % 3)) // return an identity value
				return (rand() % 10);
			else // return a completely random value
				return (rand());
		}
		operator std::string()
		{
			if (!(std::rand() % 3)) // return an identity value
			{
				std::string default_val[] =
				{
					"",
					"hola amigo",
					"amigo de la tornada",
					"amigo de pepito",
					"un",
					"dos",
					"atencion",
					"un dos tres quatro",
					"la pantera"
				};
				return (std::string(default_val[std::rand() % (sizeof(default_val) / sizeof(*default_val))]));
			} else // return a completely random value
			{
				std::string ret = "";
				for (int i = 0; i < 5; ++i)
					ret += (std::rand() % 26) + 'a';
				return (ret);
			}
		}
#if defined(TEST_MAP) || defined(TEST_SET) || defined(TEST_MULTIMAP) || defined (TEST_MULTISET)
		template <typename L, typename R>
		operator NAMESPACE::pair<L, R>()
		{
//			return NAMESPACE::pair<L, R>(*this, *this); since the ordering of equivalent keys in multi-associative containers is undefined we give the same mapped value to all elements
			return NAMESPACE::pair<L, R>(*this, R());
		}
#endif
	};

	// reimplementation of distance since we are in c++98
	template<typename It>
	int distance(It from, It to) {
		int ret = 0;
		for (; from != to; from++, ret++);
		return ret;
	}

	// reimplementation of prev since we are in c++98
	template< class BidirIt >
	BidirIt prev( BidirIt it, typename std::iterator_traits<BidirIt>::difference_type n = 1 )
	{
		for (;n > 0;--n)
			--it;
		for (;n < 0;++n)
			++it;
		return it;
	}

	// return a random iterator in the inclusive range [from, to]
	template<typename It>
	It get_random_it(It from, It to) {
		int d = monkey::distance(from, to) + 1;
		int pos = rand() % d;
		for (int i = 0; i < pos; i++, from++);
		return from;
	}

	// return a vector with random values of type T
	template<typename T>
	std::vector<T> get_random_vector() {
		std::vector<T> v;
		int size = rand() % BASE_SIZE;
		for (int i = 0; i < size; i++)
			v.push_back(monkey::get_value());
		return v;
	}

	// pretty print the range first, last without a newline
	template<typename It>
	void print_range(It first, It last) {
		std::cout << "[";
		for (It it = first; it != last; it++) {
			if (it != first)
				std::cout << ", ";
			std::cout << *it;
		}
		std::cout << "]";
	}

	// pretty print an iterator
	template<class C>
	void print_it(C &c, typename C::iterator it) {
		if (it == c.end())
			std::cout << "end iterator";
		else
			std::cout << "it -> [" << *it << "]";
	}

	// print the content of a container
	template<class C>
	void print(const C &c) {
		std::cout << "size: " << c.size() << std::endl;
		std::cout << "content:" << std::endl;
		for (typename C::const_iterator it = c.begin(); it != c.end(); it++)
			std::cout << "-> [" << *it << "]" << std::endl;
	}

#ifdef TEST_PRIORITY_QUEUE
	// specialization for priority_queue
	template<typename T, class C, class Compare>
	void print(const NAMESPACE::priority_queue<T, C, Compare> &c) {
		std::cout << "size: " << c.size() << std::endl;
		std::cout << "content:" << std::endl;
		NAMESPACE::priority_queue<T, C, Compare> copy(c);
		for (;!copy.empty(); copy.pop())
			std::cout << "-> [" << copy.top() << "]" << std::endl;
	}
#endif

	// pretty print name (with ==== on each side and in upper case)
	void print_title(std::string name) {
		int total_length = 80;
		int name_length = name.length();
		int lpad = ((total_length - name_length) / 2) - 1;
		int rpad = ((total_length - name_length) / 2) + ((total_length - name_length) % 2) - 1;
		std::transform(name.begin(), name.end(), name.begin(), ::toupper);
		std::replace(name.begin(), name.end(), '_', ' ');
		for (int i = 0; i < lpad; i++)
			std::cout << '=';
		std::cout << " " << name << " ";
		for (int i = 0; i < rpad; i++)
			std::cout << '=';
		std::cout << std::endl;
	}

	// class representing a table of test function
	template<typename C>
	class function_table
	{
	public:
		typedef void (*function_type)(C &, C&);
	private:
		std::list<function_type> internal;
	public:
		function_table(function_type array[], size_t n) {
			this->internal.assign(array, array + n);
		}
		operator std::vector<function_type>()
		{
			return std::vector<function_type>(this->internal.begin(), this->internal.end());
		}
		friend function_table operator+(const function_table<C> &l, const function_table<C> &r)
		{
			function_table ret = l;
			ret.internal.insert(ret.internal.end(), r.internal.begin(), r.internal.end());
			return ret;
		}
		friend function_table operator+(const function_table<C> &l, const function_type &r)
		{
			function_table ret = l;
			ret.internal.push_back(r);
			return ret;
		}
		friend function_table operator+(const function_type &r, const function_table<C> &l) {return l + r;}
		friend function_table operator-(const function_table<C> &l, const function_type &r)
		{
			function_table ret = l;
			ret.remove(r);
			return ret;
		}
	};

	// the core function, it tests all the function in the vector tests on two containers and do count tests
	template <class C>
	void	test_container(std::vector<void (*)(C &, C &)> tests, size_t count)
	{
		C c1;
		C c2;
		C *a = &c1;
		C *b = &c2;
		for (int i = 0; !count || i < count; i++)
		{
			if (rand() % 2)
				std::swap(a, b);
			print_title("before");
			std::cout << "a: " << std::endl;
			monkey::print(*a);
			std::cout << "b: " << std::endl;
			monkey::print(*b);
			tests[rand() % tests.size()](*b, *a);
			print_title("after");
			std::cout << "a: " << std::endl;
			monkey::print(*a);
			std::cout << "b: " << std::endl;
			monkey::print(*b);
		}
	}
}


#endif