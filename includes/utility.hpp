#ifndef UTILITY_HPP
# define UTILITY_HPP

namespace ft
{
	//////////////////////////////
	// Pair
	//////////////////////////////

	template <class T1, class T2>
	struct pair {
		typedef			T1			first_type;
		typedef			T2			second_type;

						pair		(void)											{ first = first_type(); second = second_type(); }
		template <class U, class V>
						pair		(const pair<U,V> & pr)							{ *this = pr; }
						pair		(const first_type & a, const second_type & b)	{ first = a; second = b; }
		pair &			operator=	(const pair & pr)								{ first = pr.first; second = pr.second; }

		first_type		first;
		second_type		second;
	};

		template <class T1, class T2>
		bool operator== (const pair<T1,T2> & lhs, const pair<T1,T2> & rhs)
		{ return (lhs.first == rhs.first && lhs.second == rhs.second); }

		template <class T1, class T2>
		bool operator<  (const pair<T1,T2> & lhs, const pair<T1,T2> & rhs)
		{ return (lhs.first < rhs.first || (lhs.first == rhs.first && lhs.second < rhs.second)); }

		template <class T1, class T2>
		bool operator!= (const pair<T1,T2> & lhs, const pair<T1,T2> & rhs)
		{ return (!(lhs == rhs)); }

		template <class T1, class T2>
		bool operator<= (const pair<T1,T2> & lhs, const pair<T1,T2> & rhs)
		{ return (!(rhs < lhs)); }

		template <class T1, class T2>
		bool operator>  (const pair<T1,T2> & lhs, const pair<T1,T2> & rhs)
		{ return (rhs < lhs); }

		template <class T1, class T2>
		bool operator>= (const pair<T1,T2> & lhs, const pair<T1,T2> & rhs)
		{ return (!(lhs < rhs)); }

	//////////////////////////////
	// Swap
	//////////////////////////////

	template <class T>
	void swap (T & a, T & b)
	{
		T	tmp(a);
		a = b;
		b = tmp;
	}
}

# endif
