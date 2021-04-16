#ifndef ITERATOR_HPP
# define ITERATOR_HPP

namespace ft
{
	template <class it>
	class reverse_iterator {
	public:
		// -structors
		reverse_iterator			(void)												{ _it = it(); }
		reverse_iterator			(const typename it::value_type * ptr)				{ _it = it(ptr); }
		reverse_iterator			(const reverse_iterator & x)						{ _it = x._it; }
		~reverse_iterator			(void)												{}
		// Assignment
		reverse_iterator &			operator=	(const reverse_iterator & x)			{ _it = x; return (*this); }
		reverse_iterator &			operator+=	(int n)									{ _it -= n; return (*this); }
		reverse_iterator &			operator-=	(int n)									{ _it += n; return (*this); }
		// Comparison
		bool						operator==	(const reverse_iterator & x) const		{ return (_it == x); }
		bool						operator!=	(const reverse_iterator & x) const		{ return (_it != x); }
		bool						operator<	(const reverse_iterator & x) const		{ return (_it > x); }
		bool						operator>	(const reverse_iterator & x) const		{ return (_it < x); }
		bool						operator<=	(const reverse_iterator & x) const		{ return (_it >= x); }
		bool						operator>=	(const reverse_iterator & x) const		{ return (_it <= x); }
		// -crementation
		reverse_iterator &			operator++	(void)									{ _it--; return (*this); }
		reverse_iterator &			operator--	(void)									{ _it++; return (*this); }
		reverse_iterator			operator++	(int)									{ reverse_iterator x(*this); _it--; return (x); }
		reverse_iterator			operator--	(int)									{ reverse_iterator x(*this); _it++; return (x); }
		// Operation
		reverse_iterator			operator+	(int n) const							{ return (_it - n); }
		reverse_iterator			operator-	(int n) const							{ return (_it + n); }
		std::ptrdiff_t				operator-	(const reverse_iterator & x) const		{ return (x._it - _it); }
		// Dereference
		typename it::value_type &	operator*	(void)									{ return (*_it); }
		typename it::value_type &	operator[]	(size_t n)								{ return (*(_it - n)); }

	private:
		it		_it;
	};
}

#endif
