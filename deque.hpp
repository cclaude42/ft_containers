#ifndef deque_HPP
# define deque_HPP

# include "includes/containers.hpp"

# ifndef NODE_SIZE
#  define NODE_SIZE 8
# endif

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
		dequeIterator			(value_type * const ptr, value_type ** const map)	{ _ptr = ptr; _map = map; }
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
		value_type *			getMap		(void) const							{ return (_map); }
		// Friend functions
		friend dequeIterator	operator+	(int n, const dequeIterator & x)		{ return (x.getPtr() + n); }

	private:
		value_type *			_ptr;
		const value_type **		_map;
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
		this->_init(alloc);
	}

	explicit deque (size_type n, const value_type & val = value_type(), const allocator_type & alloc = allocator_type())
	{
		this->_init(alloc);
		this->assign(n, val);
	}

	template <class InputIterator>
	deque (InputIterator first, InputIterator last, const allocator_type & alloc = allocator_type(),
	typename ft::enable_if<!ft::is_same<InputIterator, int>::value>::type* = 0)
	{
		this->_init(alloc);
		this->assign(first, last);
	}

	deque (const deque & x)
	{
		*this = x;
	}

	//////////////////////////////
	// Destructors
	//////////////////////////////

	~deque (void)
	{
		this->clear();
		delete [] _map;
	}

	//////////////////////////////
	// Assignment operator
	//////////////////////////////

	deque & operator= (const deque & x)
	{
		if (this == &x)
			return (*this);

		this->assign(x.begin(), x.end());
		return (*this);
	}

	//////////////////////////////
	// Iterators
	//////////////////////////////

	iterator begin (void)
	{
		return (iterator(this->_firstNode()[_start]);
	}

	const_iterator begin (void) const
	{
		return (const_iterator(this->_firstNode()[_start]));
	}

	iterator end (void)
	{
		return (iterator(this->_lastNode()[_end]));
	}

	const_iterator end (void) const
	{
		return (const_iterator(this->_lastNode()[_end]));
	}

	//////////////////////////////
	// Reverse iterators
	//////////////////////////////

	reverse_iterator rbegin (void)
	{
		return (++reverse_iterator(this->_lastNode()[_end]));
	}

	const_reverse_iterator rbegin (void) const
	{
		return (++const_reverse_iterator(this->_lastNode()[_end]));
	}

	reverse_iterator rend (void)
	{
		return (++reverse_iterator(this->_firstNode()[_start]));
	}

	const_reverse_iterator rend (void) const
	{
		return (++const_reverse_iterator(this->_firstNode()[_start]));
	}

	//////////////////////////////
	// Capacity
	//////////////////////////////

	size_type size (void) const
	{
		if (this->empty())
			return (0);
		return ((this->_nbNodes() - 1) * NODE_SIZE + _end - _start);
	}

	size_type max_size (void) const
	{
		return (_alloc.max_size());
	}

	void resize (size_type n, value_type val = value_type())
	{
		iterator it;
		for (it = this->begin() ; it != this->end() && n ; it++)
			n--;
		this->erase(it, this->end());
	}

	bool empty (void) const
	{
		return (this->_nbNodes() == 0);
	}

	//////////////////////////////
	// Member access
	//////////////////////////////

	reference operator[] (size_type n)
	{
		if (_start + n < NODE_SIZE)
			return (_map[0][_start + n]);
		else
			n = n + _start - NODE_SIZE;
		return (_map[n / NODE_SIZE + 1][n % NODE_SIZE]);
	}

	const_reference operator[] (size_type n) const
	{
		if (_start + n < NODE_SIZE)
			return (_map[0][_start + n]);
		else
			n = n + _start - NODE_SIZE;
		return (_map[n / NODE_SIZE + 1][n % NODE_SIZE]);
	}

	reference at (size_type n)
	{
		if (this->size() < n)
			throw std::out_of_range("deque");
		return (*this[n]);
	}

	const_reference at (size_type n) const
	{
		if (this->size() < n)
			throw std::out_of_range("deque");
		return (*this[n]);
	}

	reference front (void)
	{
		return (this->_firstNode()[_start]);
	}

	const_reference front (void) const
	{
		return (this->_firstNode()[_start]);
	}

	reference back (void)
	{
		return (this->_lastNode()[_end]);
	}

	const_reference back (void) const
	{
		return (this->_lastNode()[_end]);
	}

	//////////////////////////////
	// Assignment modifiers
	//////////////////////////////

	template <class InputIterator>
	void assign (InputIterator first, InputIterator last,
	typename ft::enable_if<!ft::is_same<InputIterator, int>::value>::type* = 0)
	{
		this->clear();
		while (first != last)
			this->push_back(*first++);
	}

	void assign (size_type n, const value_type & val)
	{
		this->clear();
		while (n--)
			this->push_back(val);
	}

	//////////////////////////////
	// Insertion modifiers
	//////////////////////////////

	iterator insert (iterator position, const value_type & val)
	{
		this->push_back(val);
		for (iterator it = position, next = ++iterator(it) ; next != this->end() ; it++, next++)
			*next = *it;
		*position = val;
		return (position);
	}

	void insert (iterator position, size_type n, const value_type & val)
	{
		while (n--)
			this->insert(position, val);
	}

	template <class InputIterator>
	void insert (iterator position, InputIterator first, InputIterator last,
	typename ft::enable_if<!ft::is_same<InputIterator, int>::value>::type* = 0)
	{
		while (first != last)
			this->insert(position, *first++);
	}

	//////////////////////////////
	// Erasure modifiers
	//////////////////////////////

	iterator erase (iterator position)
	{
		if (!this->empty())
		{
			for (iterator it = position++ ; position != this->end() ; it++, position++)
				*it = *position;
			this->pop_back();
		}
	}

	iterator erase (iterator first, iterator last)
	{
		for (size_type i = last - first ; i > 0 ; i--)
			this->erase(first);
	}

	//////////////////////////////
	// Common modifiers
	//////////////////////////////

	void push_back (const value_type & val)
	{
		_alloc.construct(this->_lastNode()[_end], val);
		if (_end == NODE_SIZE - 1)
			this->_expandBack();
		else
			_end++;
	}

	void push_front (const value_type & val)
	{
		if (_start == 0)
			this->_expandFront();
		else
			_start--;
		_alloc.construct(this->_firstNode()[_start], val);
	}

	void pop_back (void)
	{
		if (!this->empty())
		{
			if (_end == 0)
				this->_contractBack();
			else
				_end--;
			_alloc.destroy(this->_lastNode()[_end]);
		}
	}

	void pop_front (void)
	{
		if (!this->empty())
		{
			_alloc.destroy(this->_firstNode()[_start]);
			if (_start == NODE_SIZE - 1)
			this->_contractFront();
			else
			_start++;
		}
	}

	void swap (deque & x)
	{
		ft::swap(_alloc, x._alloc);
		ft::swap(_map, x._map);
		ft::swap(_start, x._start);
		ft::swap(_end, x._end);
	}

	void clear (void)
	{
		while (!this->empty())
			this->pop_back();
	}

	//////////////////////////////
	// Allocator
	//////////////////////////////

	allocator_type get_allocator (void) const
	{
		return (allocator_type());
	}

	//////////////////////////////
	// Private functions
	//////////////////////////////

private:
	void _init (allocator_type alloc)
	{
		_alloc = alloc;
		_map = new value_type * [1];
		_map[0] = _alloc.allocate(NODE_SIZE);
		_start = 0;
		_end = 0;
	}

	size_type _nbNodes (void) const
	{
		return (sizeof(_map) / sizeof(_map[0]));
	}

	value_type * _firstNode (void) const
	{
		return (_map[0]);
	}

	value_type * _lastNode (void) const
	{
		return (_map[this->_nbNodes() - 1]);
	}

	void _expandBack (void)
	{
		this->_resizeMap(this->_nbNodes() + 1, 0, 0);
		_map[this->_nbNodes()] = _alloc.allocate(NODE_SIZE);
		_end = 0;
	}

	void _expandFront (void)
	{
		this->_resizeMap(this->_nbNodes() + 1, 0, 1);
		_map[0] = _alloc.allocate(NODE_SIZE);
		_start = NODE_SIZE - 1;
	}

	void _contractBack (void)
	{
		this->_resizeMap(this->_nbNodes() - 1, 0, 0);
		_end = NODE_SIZE - 1;
	}

	void _contractFront (void)
	{
		this->_resizeMap(this->_nbNodes() - 1, 1, 0);
		_start = 0;
	}

	void _resizeMap (size_type new_size, size_type offmap, size_type offnew)
	{
		value_type ** _new = new value_type * [new_size];

		while (offmap < this->_nbNodes() && offnew < new_size)
			_new[offnew++] = _map[offmap++];

		delete [] map;
		_map = _new;
	}

	//////////////////////////////
	// Member variables
	//////////////////////////////

	allocator_type		_alloc;
	value_type **		_map;
	size_type			_start;
	size_type			_end;
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
