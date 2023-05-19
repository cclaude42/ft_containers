#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include "utility.hpp"

namespace ft
{
	//////////////////////////////
	// Iterator tags
	//////////////////////////////

	typedef		std::input_iterator_tag				input_iterator_tag;
	typedef		std::output_iterator_tag			output_iterator_tag;
	typedef		std::forward_iterator_tag			forward_iterator_tag;
	typedef		std::bidirectional_iterator_tag		bidirectional_iterator_tag;
	typedef		std::random_access_iterator_tag		random_access_iterator_tag;

	//////////////////////////////
	// Reverse iterator
	//////////////////////////////

	template <class it>
	class reverse_iterator {
	public:
		// Member types
		typedef typename			it::value_type										value_type;
		typedef typename			it::difference_type									difference_type;
		typedef typename			it::size_type										size_type;
		typedef typename			it::reference										reference;
		typedef typename			it::pointer											pointer;
		typedef typename			it::iterator_category								iterator_category;
		// -structors
		reverse_iterator			(void)												{ _it = it(); }
		reverse_iterator			(value_type * ptr)									{ _it = it(ptr); }
		reverse_iterator			(const it & x)										{ _it = x; --_it; }
		~reverse_iterator			(void)												{}
		// Conversion
		template <class U>			friend class										reverse_iterator;
		template <class U>
		reverse_iterator			(const reverse_iterator<U> & x)						{ _it = x.getIt(); }

		// Assignment
		reverse_iterator &			operator=	(const reverse_iterator & x)			{ _it = x.getIt(); return (*this); }
		reverse_iterator &			operator+=	(int n)									{ _it -= n; return (*this); }
		reverse_iterator &			operator-=	(int n)									{ _it += n; return (*this); }
		// Comparison
		template <class U> bool		operator==	(const reverse_iterator<U> & x) const	{ return (_it == x.getIt()); }
		template <class U> bool		operator!=	(const reverse_iterator<U> & x) const	{ return (_it != x.getIt()); }
		template <class U> bool		operator<	(const reverse_iterator<U> & x) const	{ return (_it > x.getIt()); }
		template <class U> bool		operator>	(const reverse_iterator<U> & x) const	{ return (_it < x.getIt()); }
		template <class U> bool		operator<=	(const reverse_iterator<U> & x) const	{ return (_it >= x.getIt()); }
		template <class U> bool		operator>=	(const reverse_iterator<U> & x) const	{ return (_it <= x.getIt()); }
		// -crementation
		reverse_iterator &			operator++	(void)									{ --_it; return (*this); }
		reverse_iterator &			operator--	(void)									{ ++_it; return (*this); }
		reverse_iterator			operator++	(int)									{ reverse_iterator<it> x(*this); --_it; return (x); }
		reverse_iterator			operator--	(int)									{ reverse_iterator<it> x(*this); ++_it; return (x); }
		// Operation
		reverse_iterator			operator+	(int n) const							{ return (_it - n + 1); }
		reverse_iterator			operator-	(int n) const							{ return (_it + n + 1); }
		ft::ptrdiff_t				operator-	(const reverse_iterator & x) const		{ return (x.getIt() - _it); }
		// Dereference
		reference					operator[]	(size_t n) const						{ return (*(_it - n)); }
		reference					operator*	(void) const							{ return (*_it); }
		pointer						operator->	(void) const							{ return (&(*_it)); }
		// Member functions
		it							base		(void)									{ return (++it(_it)); }
		it							getIt		(void) const							{ return (_it); }
		// Non-member functions
		friend reverse_iterator		operator+	(int n, const reverse_iterator & x)		{ return (x.getIt() - n + 1); }

	private:
		it		_it;
	};
}

#endif
