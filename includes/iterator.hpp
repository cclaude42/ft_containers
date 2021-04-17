#ifndef ITERATOR_HPP
# define ITERATOR_HPP

namespace ft
{
	template <class it>
	class reverse_iterator {
	public:
		// -structors
		reverse_iterator			(void)												{ _it = it(); }
		reverse_iterator			(typename it::value_type * ptr)						{ _it = it(ptr); }
		reverse_iterator			(const it & x)										{ _it = x - 1; }
		~reverse_iterator			(void)												{}
		// Conversion
		template <class U>			friend class										reverse_iterator;
		template <class U>
		reverse_iterator			(const reverse_iterator<U> & x)						{ _it = x._it; }

		// Assignment
		reverse_iterator &			operator=	(const reverse_iterator & x)			{ _it = x._it; return (*this); }
		reverse_iterator &			operator+=	(int n)									{ _it -= n; return (*this); }
		reverse_iterator &			operator-=	(int n)									{ _it += n; return (*this); }
		// Comparison
		template <class U> bool		operator==	(const reverse_iterator<U> & x) const	{ return (_it == x._it); }
		template <class U> bool		operator!=	(const reverse_iterator<U> & x) const	{ return (_it != x._it); }
		template <class U> bool		operator<	(const reverse_iterator<U> & x) const	{ return (_it > x._it); }
		template <class U> bool		operator>	(const reverse_iterator<U> & x) const	{ return (_it < x._it); }
		template <class U> bool		operator<=	(const reverse_iterator<U> & x) const	{ return (_it >= x._it); }
		template <class U> bool		operator>=	(const reverse_iterator<U> & x) const	{ return (_it <= x._it); }
		// -crementation
		reverse_iterator &			operator++	(void)									{ _it--; return (*this); }
		reverse_iterator &			operator--	(void)									{ _it++; return (*this); }
		reverse_iterator			operator++	(int)									{ reverse_iterator<it> x(*this); _it--; return (x); }
		reverse_iterator			operator--	(int)									{ reverse_iterator<it> x(*this); _it++; return (x); }
		// Operation
		reverse_iterator			operator+	(int n) const							{ return (_it - n + 1); }
		reverse_iterator			operator-	(int n) const							{ return (_it + n + 1); }
		std::ptrdiff_t				operator-	(const reverse_iterator & x) const		{ return (x._it - _it); }
		// Dereference
		typename it::value_type &	operator[]	(size_t n)								{ return (*(_it - n)); }
		typename it::value_type &	operator*	(void)									{ return (*_it); }
		typename it::value_type *	operator->	(void)									{ return (&(*_it)); }
		// Member functions
		it							base		(void)									{ return (_it + 1); }
		// Non-member functions
		friend reverse_iterator		operator+	(int n, const reverse_iterator & x)		{ return (x._it - n + 1); }

	private:
		it		_it;
	};
}

#endif