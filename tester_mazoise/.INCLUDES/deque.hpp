#ifndef DEQUE_HPP
# define DEQUE_HPP

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
		dequeIterator			(void)												{ _ptr = NULL; _deq = NULL; }
		dequeIterator			(value_type * const ptr, const deque * deq)			{ this->init(ptr, deq); }
		~dequeIterator			(void)												{}
		// Const stuff
		template <bool B>		dequeIterator
			(const dequeIterator<B> & x, typename ft::enable_if<!B>::type* = 0)		{ this->init(x.getPtr(), x.getDeq()); }

		// Assignment
		dequeIterator &			operator=	(const dequeIterator & x)				{ this->init(x.getPtr(), x.getDeq()); return (*this); }
		dequeIterator &			operator+=	(int n)									{ this->plus(n); return (*this); }
		dequeIterator &			operator-=	(int n)									{ this->minus(n); return (*this); }
		// Comparison
		template <bool B> bool	operator==	(const dequeIterator<B> & x) const		{ return (_ptr == x.getPtr()); }
		template <bool B> bool	operator!=	(const dequeIterator<B> & x) const		{ return (_ptr != x.getPtr()); }
		template <bool B> bool	operator<	(const dequeIterator<B> & x) const		{ return (this->diff(x) < 0); }
		template <bool B> bool	operator>	(const dequeIterator<B> & x) const		{ return (this->diff(x) > 0); }
		template <bool B> bool	operator<=	(const dequeIterator<B> & x) const		{ return (this->diff(x) <= 0); }
		template <bool B> bool	operator>=	(const dequeIterator<B> & x) const		{ return (this->diff(x) >= 0); }
		// -crementation
		dequeIterator &			operator++	(void)									{ this->plus(1); return (*this); }
		dequeIterator &			operator--	(void)									{ this->minus(1); return (*this); }
		dequeIterator			operator++	(int)									{ dequeIterator<IsConst> x(*this); this->plus(1); return (x); }
		dequeIterator			operator--	(int)									{ dequeIterator<IsConst> x(*this); this->minus(1); return (x); }
		// Operation
		dequeIterator			operator+	(int n) const							{ dequeIterator<IsConst> x(*this); x.plus(n); return (x); }
		dequeIterator			operator-	(int n) const							{ dequeIterator<IsConst> x(*this); x.minus(n); return (x); }
		difference_type			operator-	(const dequeIterator & x) const			{ return (this->diff(x)); }
		// Dereference
		value_type &			operator[]	(size_type n) const						{ dequeIterator<IsConst> x(*this); x.plus(n); return (*(x.getPtr())); }
		value_type &			operator*	(void) const							{ return (*_ptr); }
		value_type *			operator->	(void) const							{ return (_ptr); }
		// Member functions
		value_type *			getPtr		(void) const							{ return (_ptr); }
		const deque *			getDeq		(void) const							{ return (_deq); }
		size_type				getI		(void) const							{ return (_i); }
		bool					getOut		(void) const							{ return (_out); }
		// Friend functions
		friend dequeIterator	operator+	(int n, const dequeIterator & x)		{ return (x + n); }

	private:
		value_type *			_ptr;
		const deque *			_deq;
		size_type				_i;
		bool					_out;

		void init (value_type * const ptr, const deque * deq)
		{
			_ptr = ptr;
			_deq = deq;
			_i = 0;
			_out = true;

			if (!_deq)
				return ;
			for (size_type i = 0 ; i < _deq->_size ; i++)
			{
				for (size_type j = 0 ; j < _deq->_node_size ; j++)
				{
					if (_ptr == _deq->_map[i] + j)
					{
						_i = i;
						_out = false;
					}
				}
			}
		}

		void plus (int n)
		{
			while (n > 0 && n--)
				this->next();
			while (n < 0 && n++)
				this->prev();
		}

		void minus (int n)
		{
			while (n > 0 && n--)
				this->prev();
			while (n < 0 && n++)
				this->next();
		}

		void next (void)
		{
			if (!_deq)
				return ;
			if (_ptr == _deq->_lastNode() + _deq->_node_size - 1)
				_out = true;
			else if (_ptr == _deq->_firstNode() - 1)
				_out = false;
			else if (_ptr == _deq->_map[_i] + _deq->_node_size - 1)
			{
				_ptr = _deq->_map[++_i];
				return ;
			}
			_ptr++;
		}

		void prev (void)
		{
			if (!_deq)
				return ;
			if (_ptr == _deq->_firstNode())
				_out = true;
			else if (_ptr == _deq->_lastNode() + _deq->_node_size)
				_out = false;
			else if (_ptr == _deq->_map[_i])
			{
				_ptr = _deq->_map[--_i] + _deq->_node_size - 1;
				return ;
			}
			_ptr--;
		}

		template <bool B>
		difference_type diff (const dequeIterator<B> & x) const
		{
			if (!_deq)
				return (0);
			if (_out || x.getOut())
				return (_ptr - x.getPtr());
			else
				return ((_i - x.getI()) * _deq->_node_size + _ptr - x.getPtr());
		}
	}; // Iterator

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
		this->_init(x._alloc);
		*this = x;
	}

	//////////////////////////////
	// Destructors
	//////////////////////////////

	~deque (void)
	{
		this->clear();
		_alloc.deallocate(_map[0], this->_node_size);
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
		return (iterator(this->_firstNode() + _start, this));
	}

	const_iterator begin (void) const
	{
		return (const_iterator(this->_firstNode() + _start, this));
	}

	iterator end (void)
	{
		return (iterator(this->_lastNode() + _end, this));
	}

	const_iterator end (void) const
	{
		return (const_iterator(this->_lastNode() + _end, this));
	}

	//////////////////////////////
	// Reverse iterators
	//////////////////////////////

	reverse_iterator rbegin (void)
	{
		return (reverse_iterator(this->end()));
	}

	const_reverse_iterator rbegin (void) const
	{
		return (const_reverse_iterator(this->end()));
	}

	reverse_iterator rend (void)
	{
		return (reverse_iterator(this->begin()));
	}

	const_reverse_iterator rend (void) const
	{
		return (const_reverse_iterator(this->begin()));
	}

	//////////////////////////////
	// Capacity
	//////////////////////////////

	size_type size (void) const
	{
		if (this->empty())
			return (0);
		return ((_size - 1) * this->_node_size + _end - _start);
	}

	size_type max_size (void) const
	{
		return (_alloc.max_size());
	}

	void resize (size_type n, value_type val = value_type())
	{
		if (n > this->size())
		{
			while (n > this->size())
				this->push_back(val);
		}
		else if (n < this->size())
		{
			while (n < this->size())
				this->pop_back();
		}
	}

	bool empty (void) const
	{
		return (_size == 1 && this->_start == this->_end);
	}

	//////////////////////////////
	// Member access
	//////////////////////////////

	reference operator[] (size_type n)
	{
		if (_start + n < this->_node_size)
			return (_map[0][_start + n]);
		else
			n = n + _start - this->_node_size;
		return (_map[n / this->_node_size + 1][n % this->_node_size]);
	}

	const_reference operator[] (size_type n) const
	{
		if (_start + n < this->_node_size)
			return (_map[0][_start + n]);
		else
			n = n + _start - this->_node_size;
		return (_map[n / this->_node_size + 1][n % this->_node_size]);
	}

	reference at (size_type n)
	{
		if (this->size() <= n)
		{
			if (MACOS_)
				throw std::out_of_range("deque");
			else
				throw std::out_of_range("deque::_M_range_check: __n (which is " + ft::to_string(n) + ")>= this->size() (which is " + ft::to_string(this->size()) + ")");
		}
		return ((*this)[n]);
	}

	const_reference at (size_type n) const
	{
		if (this->size() <= n)
		{
			if (MACOS_)
				throw std::out_of_range("deque");
			else
				throw std::out_of_range("deque::_M_range_check: __n (which is " + ft::to_string(n) + ")>= this->size() (which is " + ft::to_string(this->size()) + ")");
		}
		return ((*this)[n]);
	}

	reference front (void)
	{
		return (*this->begin());
	}

	const_reference front (void) const
	{
		return (*this->begin());
	}

	reference back (void)
	{
		return (*this->rbegin());
	}

	const_reference back (void) const
	{
		return (*this->rbegin());
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
		for (iterator it = --(this->end()), prev = --iterator(it) ; it != position ; it--, prev--)
			*it = *prev;
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
		{
			this->insert(position, *first++);
			position++;
		}
	}

	//////////////////////////////
	// Erasure modifiers
	//////////////////////////////

	iterator erase (iterator position)
	{
		if (!this->empty())
		{
			iterator next = position;
			for (iterator it = next++ ; position != this->end() && next != this->end() ; it++, next++)
				*it = *next;
			this->pop_back();
		}
		return (position);
	}

	iterator erase (iterator first, iterator last)
	{
		for (size_type i = last - first ; i > 0 ; i--)
			this->erase(first);
		return (first);
	}

	//////////////////////////////
	// Common modifiers
	//////////////////////////////

	void push_back (const value_type & val)
	{
		_alloc.construct(this->_lastNode() + _end, val);
		if (_end == this->_node_size - 1)
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
		_alloc.construct(this->_firstNode() + _start, val);
	}

	void pop_back (void)
	{
		if (!this->empty())
		{
			if (_end == 0)
				this->_contractBack();
			else
				_end--;
			_alloc.destroy(this->_lastNode() + _end);
		}
	}

	void pop_front (void)
	{
		if (!this->empty())
		{
			_alloc.destroy(this->_firstNode() + _start);
			if (_start == this->_node_size - 1)
				this->_contractFront();
			else
				_start++;
		}
	}

	void swap (deque & x)
	{
		ft::swap(_alloc, x._alloc);
		ft::swap(_map, x._map);
		ft::swap(_size, x._size);
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
		_map[0] = _alloc.allocate(this->_node_size);
		_size = 1;
		_start = 0;
		_end = 0;
	}

	value_type * _firstNode (void) const
	{
		return (_map[0]);
	}

	value_type * _lastNode (void) const
	{
		return (_map[_size - 1]);
	}

	void _expandBack (void)
	{
		this->_resizeMap(_size + 1, 0, 0);
		_map[_size] = _alloc.allocate(this->_node_size);
		_size++;
		_end = 0;
	}

	void _expandFront (void)
	{
		this->_resizeMap(_size + 1, 0, 1);
		_map[0] = _alloc.allocate(this->_node_size);
		_size++;
		_start = this->_node_size - 1;
	}

	void _contractBack (void)
	{
		_alloc.deallocate(_map[_size - 1], this->_node_size);
		this->_resizeMap(_size - 1, 0, 0);
		_size--;
		_end = this->_node_size - 1;
	}

	void _contractFront (void)
	{
		_alloc.deallocate(_map[0], this->_node_size);
		this->_resizeMap(_size - 1, 1, 0);
		_size--;
		_start = 0;
	}

	void _resizeMap (size_type new_size, size_type offmap, size_type offnew)
	{
		value_type ** _new = new value_type * [new_size];

		while (offmap < _size && offnew < new_size)
			_new[offnew++] = _map[offmap++];

		delete [] _map;
		_map = _new;
	}

	//////////////////////////////
	// Member variables
	//////////////////////////////

	allocator_type				_alloc;
	value_type **				_map;
	size_type					_size;
	size_type					_start;
	size_type					_end;
	static const size_type		_node_size = 8;
}; // Deque

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
