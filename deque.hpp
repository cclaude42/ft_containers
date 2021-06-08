#ifndef deque_HPP
# define deque_HPP

# include "includes/containers.hpp"

namespace ft
{

template < class T, class Alloc = std::allocator<T> >
class deque {
public:

	//////////////////////////////
	// Iterator subclass
	//////////////////////////////

	template <bool IsConst>
	class dequeIterator {
	public:
		// Member types
		typedef typename		ft::conditional<IsConst, const T, T>::type			value_type;
		typedef					std::ptrdiff_t										difference_type;
		typedef					std::size_t											size_type;
		// -structors
		dequeIterator			(void)												{ _ptr = NULL; }
		dequeIterator			(value_type * const ptr)							{ _ptr = ptr; }
		~dequeIterator			(void)												{}
		// Const stuff
		template <bool B>		dequeIterator
			(const dequeIterator<B> & x, typename ft::enable_if<!B>::type* = 0)		{ _ptr = x.getPtr(); }

		// Assignment
		dequeIterator &			operator=	(const dequeIterator & x)				{ _ptr = x.getPtr(); return (*this); }
		dequeIterator &			operator+=	(int n)									{ _ptr += n; return (*this); }
		dequeIterator &			operator-=	(int n)									{ _ptr -= n; return (*this); }
		// Comparison
		template <bool B> bool	operator==	(const dequeIterator<B> & x) const		{ return (_ptr == x.getPtr()); }
		template <bool B> bool	operator!=	(const dequeIterator<B> & x) const		{ return (_ptr != x.getPtr()); }
		template <bool B> bool	operator<	(const dequeIterator<B> & x) const		{ return (_ptr < x.getPtr()); }
		template <bool B> bool	operator>	(const dequeIterator<B> & x) const		{ return (_ptr > x.getPtr()); }
		template <bool B> bool	operator<=	(const dequeIterator<B> & x) const		{ return (_ptr <= x.getPtr()); }
		template <bool B> bool	operator>=	(const dequeIterator<B> & x) const		{ return (_ptr >= x.getPtr()); }
		// -crementation
		dequeIterator &			operator++	(void)									{ _ptr++; return (*this); }
		dequeIterator &			operator--	(void)									{ _ptr--; return (*this); }
		dequeIterator			operator++	(int)									{ dequeIterator<IsConst> x(*this); _ptr++; return (x); }
		dequeIterator			operator--	(int)									{ dequeIterator<IsConst> x(*this); _ptr--; return (x); }
		// Operation
		dequeIterator			operator+	(int n) const							{ return (_ptr + n); }
		dequeIterator			operator-	(int n) const							{ return (_ptr - n); }
		difference_type			operator-	(const dequeIterator & x) const			{ return (_ptr - x.getPtr()); }
		// Dereference
		value_type &			operator[]	(size_type n) const						{ return (*(_ptr + n)); }
		value_type &			operator*	(void) const							{ return (*_ptr); }
		value_type *			operator->	(void) const							{ return (_ptr); }
		// Member functions
		value_type *			getPtr		(void) const							{ return (_ptr); }
		// Friend functions
		friend dequeIterator	operator+	(int n, const dequeIterator & x)		{ return (x.getPtr() + n); }

	private:
		value_type *			_ptr;
	};

	//////////////////////////////
	// Member types
	//////////////////////////////

	typedef		T												value_type;
	typedef		Alloc											allocator_type;
	typedef		typename allocator_type::reference				reference;
	typedef		typename allocator_type::const_reference		const_reference;
	typedef		typename allocator_type::pointer				pointer;
	typedef		typename allocator_type::const_pointer			const_pointer;
	typedef		dequeIterator<false>							iterator;
	typedef		dequeIterator<true>								const_iterator;
	typedef		ft::reverse_iterator<iterator>					reverse_iterator;
	typedef		ft::reverse_iterator<const_iterator>			const_reverse_iterator;
	typedef		typename dequeIterator<false>::difference_type	difference_type;
	typedef		typename dequeIterator<false>::size_type		size_type;

	//////////////////////////////
	// Constructors
	//////////////////////////////

	explicit deque (const allocator_type & alloc = allocator_type())
	{
		_alloc = alloc;

	}

	explicit deque (size_type n, const value_type & val = value_type(), const allocator_type & alloc = allocator_type())
	{
		_alloc = alloc;

	}

	template <class InputIterator>
	deque (InputIterator first, InputIterator last, const allocator_type & alloc = allocator_type(),
	typename ft::enable_if<!ft::is_same<InputIterator, int>::value>::type* = 0)
	{
		size_type		n = 0;
		for (InputIterator cpy = first ; cpy != last && n <= this->max_size() ; cpy++)
			n++;

		_alloc = alloc;

	}

	deque (const deque & x)
	{
		_alloc = x._alloc;

	}

	//////////////////////////////
	// Destructors
	//////////////////////////////

	~deque (void)
	{

	}

	//////////////////////////////
	// Assignment operator
	//////////////////////////////

	deque & operator= (const deque & x)
	{
		if (this == &x)
			return (*this);



		return (*this);
	}

	//////////////////////////////
	// Iterators
	//////////////////////////////

	iterator begin (void)
	{
		return (iterator());
	}

	const_iterator begin (void) const
	{
		return (const_iterator());
	}

	iterator end (void)
	{
		return (iterator());
	}

	const_iterator end (void) const
	{
		return (const_iterator());
	}

	//////////////////////////////
	// Reverse iterators
	//////////////////////////////

	reverse_iterator rbegin (void)
	{
		return (reverse_iterator());
	}

	const_reverse_iterator rbegin (void) const
	{
		return (const_reverse_iterator());
	}

	reverse_iterator rend (void)
	{
		return (reverse_iterator());
	}

	const_reverse_iterator rend (void) const
	{
		return (const_reverse_iterator());
	}

	//////////////////////////////
	// Capacity
	//////////////////////////////

	size_type size (void) const
	{
		return ();
	}

	size_type max_size (void) const
	{
		return (_alloc.max_size());
	}

	void resize (size_type n, value_type val = value_type())
	{

	}

	bool empty (void) const
	{
		return ();
	}

	//////////////////////////////
	// Member access
	//////////////////////////////

	reference operator[] (size_type n)
	{
		return ();
	}

	const_reference operator[] (size_type n) const
	{
		return ();
	}

	reference at (size_type n)
	{

		return ();
	}

	const_reference at (size_type n) const
	{

		return ();
	}

	reference front (void)
	{
		return ();
	}

	const_reference front (void) const
	{
		return ();
	}

	reference back (void)
	{
		return ();
	}

	const_reference back (void) const
	{
		return ();
	}

	//////////////////////////////
	// Assignment modifiers
	//////////////////////////////

	template <class InputIterator>
	void assign (InputIterator first, InputIterator last,
	typename ft::enable_if<!ft::is_same<InputIterator, int>::value>::type* = 0)
	{
		size_type		n = 0;
		for (InputIterator cpy = first ; cpy != last && n < 1000000 ; cpy++)
			n++;


	}

	void assign (size_type n, const value_type & val)
	{

	}

	//////////////////////////////
	// Insertion modifiers
	//////////////////////////////

	iterator insert (iterator position, const value_type & val)
	{

		return ();
	}

	void insert (iterator position, size_type n, const value_type & val)
	{

	}

	template <class InputIterator>
	void insert (iterator position, InputIterator first, InputIterator last,
	typename ft::enable_if<!ft::is_same<InputIterator, int>::value>::type* = 0)
	{
		size_type		n = 0;
		for (InputIterator cpy = first ; cpy != last && n <= this->max_size() ; cpy++)
			n++;


	}

	//////////////////////////////
	// Erasure modifiers
	//////////////////////////////

	iterator erase (iterator position)
	{

	}

	iterator erase (iterator first, iterator last)
	{

	}

	//////////////////////////////
	// Common modifiers
	//////////////////////////////

	void push_front (const value_type & val)
	{

	}

	void push_back (const value_type & val)
	{

	}

	void pop_front (void)
	{

	}

	void pop_back (void)
	{

	}

	void swap (deque & x)
	{
		ft::swap(_alloc, x._alloc);

	}

	void clear (void)
	{

	}

	//////////////////////////////
	// Allocator
	//////////////////////////////

	allocator_type get_allocator (void) const
	{
		return (allocator_type());
	}

	//////////////////////////////
	// Member variables
	//////////////////////////////

private:

};

	//////////////////////////////
	// Relational operators
	//////////////////////////////

	template <class T, class Alloc>
	bool operator== (const deque<T,Alloc> & lhs, const deque<T,Alloc> & rhs)
	{
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class T, class Alloc>
	bool operator< (const deque<T,Alloc> & lhs, const deque<T,Alloc> & rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class T, class Alloc>
	bool operator!= (const deque<T,Alloc> & lhs, const deque<T,Alloc> & rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T, class Alloc>
	bool operator<= (const deque<T,Alloc> & lhs, const deque<T,Alloc> & rhs)
	{
		return (!(rhs < lhs));
	}

	template <class T, class Alloc>
	bool operator> (const deque<T,Alloc> & lhs, const deque<T,Alloc> & rhs)
	{
		return (rhs < lhs);
	}

	template <class T, class Alloc>
	bool operator>= (const deque<T,Alloc> & lhs, const deque<T,Alloc> & rhs)
	{
		return (!(lhs < rhs));
	}

	template <class T, class Alloc>
	void swap (deque<T,Alloc> & x, deque<T,Alloc> & y)
	{
		x.swap(y);
	}

} // Namespace ft

#endif
