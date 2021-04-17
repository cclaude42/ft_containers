#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <stdint.h>
# include "includes/os.hpp"
# include "includes/iterator.hpp"
# include "includes/types.hpp"
# include "includes/string.hpp"

# if __APPLE__
#  define SIZE_OR_CAP _capacity
# else
#  define SIZE_OR_CAP _size
# endif

namespace ft
{

template <class T, class Alloc = std::allocator<T> >
class vector {
public:

	//////////////////////////////
	// Iterator subclass
	//////////////////////////////

	template <bool IsConst>
	class vectorIterator {
	public:
		// Member types
		typedef typename		ft::conditional<IsConst, const T, T>::type			value_type;
		// -structors
		vectorIterator			(void)												{ _ptr = NULL; }
		vectorIterator			(value_type * const ptr)							{ _ptr = ptr; }
		~vectorIterator			(void)												{}
		// Const stuff
		template <bool B>		friend class										vectorIterator;
		template <bool B>		vectorIterator
			(const vectorIterator<B> & x, typename ft::enable_if<!B>::type* = 0)	{ _ptr = x._ptr; }

		// Assignment
		vectorIterator &		operator=	(const vectorIterator & x)				{ _ptr = x._ptr; return (*this); }
		vectorIterator &		operator+=	(int n)									{ _ptr += n; return (*this); }
		vectorIterator &		operator-=	(int n)									{ _ptr -= n; return (*this); }
		// Comparison
		template <bool B> bool	operator==	(const vectorIterator<B> & x) const		{ return (_ptr == x._ptr); }
		template <bool B> bool	operator!=	(const vectorIterator<B> & x) const		{ return (_ptr != x._ptr); }
		template <bool B> bool	operator<	(const vectorIterator<B> & x) const		{ return (_ptr < x._ptr); }
		template <bool B> bool	operator>	(const vectorIterator<B> & x) const		{ return (_ptr > x._ptr); }
		template <bool B> bool	operator<=	(const vectorIterator<B> & x) const		{ return (_ptr <= x._ptr); }
		template <bool B> bool	operator>=	(const vectorIterator<B> & x) const		{ return (_ptr >= x._ptr); }
		// -crementation
		vectorIterator &		operator++	(void)									{ _ptr++; return (*this); }
		vectorIterator &		operator--	(void)									{ _ptr--; return (*this); }
		vectorIterator			operator++	(int)									{ vectorIterator<IsConst> x(*this); _ptr++; return (x); }
		vectorIterator			operator--	(int)									{ vectorIterator<IsConst> x(*this); _ptr--; return (x); }
		// Operation
		vectorIterator			operator+	(int n) const							{ return (_ptr + n); }
		vectorIterator			operator-	(int n) const							{ return (_ptr - n); }
		std::ptrdiff_t			operator-	(const vectorIterator & x) const		{ return (_ptr - x._ptr); }
		// Dereference
		value_type &			operator[]	(size_t n)								{ return (*(_ptr + n)); }
		value_type &			operator*	(void)									{ return (*_ptr); }
		value_type *			operator->	(void)									{ return (_ptr); }
		// Non-member functions
		friend vectorIterator	operator+	(int n, const vectorIterator & x)		{ return (x._ptr + n); }

	protected:
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
	typedef		vectorIterator<false>							iterator;
	typedef		vectorIterator<true>							const_iterator;
	typedef		ft::reverse_iterator<iterator>					reverse_iterator;
	typedef		ft::reverse_iterator<const_iterator>			const_reverse_iterator;
	typedef		std::ptrdiff_t									difference_type;
	typedef		std::size_t										size_type;

	//////////////////////////////
	// Constructors
	//////////////////////////////

	explicit vector (const allocator_type & alloc = allocator_type())
	{
		(void)alloc;
		_vct = NULL;
		_size = 0;
		_capacity = 0;
	}

	explicit vector (size_type n, const value_type & val = value_type(), const allocator_type & alloc = allocator_type())
	{
		(void)alloc;
		_size = n;
		_capacity = n;
		if (n)
			_vct = new T[n];
		else
			_vct = NULL;

		for (size_type i = 0 ; i < n ; i++)
			_vct[i] = val;
	}

	template <class InputIterator>
	vector (InputIterator first, InputIterator last, const allocator_type & alloc = allocator_type(),
			typename ft::enable_if<!ft::is_same<InputIterator, int>::value>::type* = 0)
	{
		(void)alloc;
		// if (last - first < 0)
		// 	throw std::bad_alloc();

		size_type		n = 0;
		for (InputIterator cpy = first ; cpy != last ; cpy++)
			n++;

		_size = n;
		_capacity = n;
		if (n > 0)
			_vct = new T[n];
		else
			_vct = NULL;

		for (size_type i = 0 ; i < n ; i++)
			_vct[i] = *first++;
	}

	vector (const vector & x)
	{
		_size = x._size;
		_capacity = x._capacity;
		_vct = new T[_capacity];

		for (size_type i = 0 ; i < _size ; i++)
			_vct[i] = x[i];
	}

	//////////////////////////////
	// Destructors
	//////////////////////////////

	~vector (void)
	{
		if (_vct != NULL)
			delete [] _vct;
	}

	//////////////////////////////
	// Assignment operator
	//////////////////////////////

	vector & operator= (const vector & x)
	{
		if (_vct != NULL && x._size > _capacity)
			delete [] _vct;

		if (_vct == NULL || x._size > _capacity)
		{
			_capacity = x._size;
			_vct = new T[_capacity];
		}

		_size = x._size;
		for (size_type i = 0 ; i < _size ; i++)
			_vct[i] = x[i];

		return (*this);
	}

	//////////////////////////////
	// Iterators
	//////////////////////////////

	iterator begin (void)
	{
		return (iterator(_vct));
	}

	const_iterator begin (void) const
	{
		return (const_iterator(_vct));
	}

	iterator end (void)
	{
		return (iterator(_vct + _size));
	}

	const_iterator end (void) const
	{
		return (const_iterator(_vct + _size));
	}

	//////////////////////////////
	// Reverse iterators
	//////////////////////////////

	reverse_iterator rbegin (void)
	{
		return (reverse_iterator(_vct + _size - 1));
	}

	const_reverse_iterator rbegin (void) const
	{
		return (const_reverse_iterator(_vct + _size - 1));
	}

	reverse_iterator rend (void)
	{
		return (reverse_iterator(_vct - 1));
	}

	const_reverse_iterator rend (void) const
	{
		return (const_reverse_iterator(_vct - 1));
	}

	//////////////////////////////
	// Capacity
	//////////////////////////////

	size_type size (void) const
	{
		return (_size);
	}

	size_type max_size (void) const
	{
		return (_max_size);
	}

	void resize (size_type n, value_type val = value_type())
	{
		if (n > _size)
		{
			if (n > _capacity)
			{
				if (n > SIZE_OR_CAP * 2)
					this->reserve(n);
				else if (SIZE_OR_CAP > 0)
					this->reserve(SIZE_OR_CAP * 2);
				else
					this->reserve(1);
			}

			for (size_type i = _size ; i < n ; i++)
				_vct[i] = val;
		}

		_size = n;
	}

	size_type capacity (void) const
	{
		return (_capacity);
	}

	bool empty (void) const
	{
		return (_size == 0);
	}

	void reserve (size_type n)
	{
		if (n > _max_size)
		{
			if (OS == MAC)
				throw std::length_error("allocator<T>::allocate(size_t n) 'n' exceeds maximum supported size");
			else
				throw std::length_error("vector::reserve");
		}

		if (n > _capacity)
		{
			T *		new_vct = new T[n];

			for (size_type i = 0 ; i < _size && i < n ; i++)
				new_vct[i] = _vct[i];

			if (_vct)
				delete [] _vct;

			_capacity = n;
			_vct = new_vct;
		}
	}

	//////////////////////////////
	// Member access
	//////////////////////////////

	reference operator[] (size_type n)
	{
		return (_vct[n]);
	}

	const_reference operator[] (size_type n) const
	{
		return (_vct[n]);
	}

	reference at (size_type n)
	{
		if (n >= _size)
		{
			if (OS == MAC)
				throw std::out_of_range("vector");
			else
				throw std::out_of_range("vector::_M_range_check: __n (which is " + ft::to_string(n) + ") >= this->size() (which is " + ft::to_string(_size) + ")");
		}
		return (_vct[n]);
	}

	const_reference at (size_type n) const
	{
		if (n >= _size)
		{
			if (OS == MAC)
				throw std::out_of_range("vector");
			else
				throw std::out_of_range("vector::_M_range_check: __n (which is " + ft::to_string(n) + ") >= this->size() (which is " + ft::to_string(_size) + ")");
		}
		return (_vct[n]);
	}

	reference front (void)
	{
		return (_vct[0]);
	}

	const_reference front (void) const
	{
		return (_vct[0]);
	}

	reference back (void)
	{
		return (_vct[_size - 1]);
	}

	const_reference back (void) const
	{
		return (_vct[_size - 1]);
	}

	//////////////////////////////
	// Assignment modifiers
	//////////////////////////////

	template <class InputIterator>
	void assign (InputIterator first, InputIterator last,
				typename ft::enable_if<!ft::is_same<InputIterator, int>::value>::type* = 0)
	{
		size_type		n = 0;
		for (InputIterator cpy = first ; cpy != last ; cpy++)
			n++;

		if (n > _capacity)
			this->reserve(n);

		for (size_type i = 0 ; i < n ; i++)
			_vct[i] = *first++;
		_size = n;
	}

	void assign (size_type n, const value_type & val)
	{
		if (n > _capacity)
			this->reserve(n);

		for (size_type i = 0 ; i < n ; i++)
			_vct[i] = val;
		_size = n;
	}

	//////////////////////////////
	// Insertion modifiers
	//////////////////////////////

	iterator insert (iterator position, const value_type & val)
	{
		size_type		off = position - this->begin();

		if (_size + 1 > _capacity)
		{
			if (SIZE_OR_CAP > 0)
				this->reserve(SIZE_OR_CAP * 2);
			else
				this->reserve(1);
		}

		for (size_type i = _size ; i > off ; i--)
			_vct[i] = _vct[i - 1];

		_vct[off] = val;
		_size++;

		return (iterator(_vct + off));
	}

	void insert (iterator position, size_type n, const value_type & val)
	{
		size_type		off = position - this->begin();

		if (_size + n > _capacity)
		{
			if (_size + n > SIZE_OR_CAP * 2)
				this->reserve(_size + n);
			else if (SIZE_OR_CAP > 0)
				this->reserve(SIZE_OR_CAP * 2);
			else
				this->reserve(1);
		}

		for (size_type i = _size - 1 + n ; i >= off + n ; i--)
			_vct[i] = _vct[i - n];

		for (size_type i = off ; i - off < n ; i++)
			_vct[i] = val;
		_size = _size + n;
	}

	template <class InputIterator>
	void insert (iterator position, InputIterator first, InputIterator last,
				typename ft::enable_if<!ft::is_same<InputIterator, int>::value>::type* = 0)
	{
		size_type		off = position - this->begin();
		size_type		n = 0;
		for (InputIterator cpy = first ; cpy != last ; cpy++)
			n++;

		if (_size + n > _capacity)
		{
			if (_size + n > SIZE_OR_CAP * 2)
				this->reserve(_size + n);
			else if (SIZE_OR_CAP > 0)
				this->reserve(SIZE_OR_CAP * 2);
			else
				this->reserve(1);
		}

		for (size_type i = _size - 1 + n ; i >= off + n ; i--)
			_vct[i] = _vct[i - n];

		for (size_type i = off ; i - off < n ; i++)
			_vct[i] = *first++;
		_size = _size + n;
	}

	//////////////////////////////
	// Erasure modifiers
	//////////////////////////////

	iterator erase (iterator position)
	{
		size_type		off = position - this->begin();

		for (size_type i = off ; i < _size - 1 ; i++)
			_vct[i] = _vct[i + 1];
		_size--;

		return (iterator(_vct + off));
	}

	iterator erase (iterator first, iterator last)
	{
		size_type		off = first - this->begin();
		size_type		n = 0;
		for (iterator cpy = first ; cpy != last ; cpy++)
			n++;

		for (size_type i = off ; i < _size - n ; i++)
			_vct[i] = _vct[i + n];
		_size = _size - n;

		return (iterator(_vct + off));
	}

	//////////////////////////////
	// Common modifiers
	//////////////////////////////

	void push_back (const value_type & val)
	{
		if (_size + 1 > _capacity)
		{
			if (SIZE_OR_CAP > 0)
				this->reserve(SIZE_OR_CAP * 2);
			else
				this->reserve(1);
		}

		_vct[_size] = val;
		_size++;
	}

	void pop_back (void)
	{
		_size--;
	}

	void swap (vector & x)
	{
		size_type	tmpsize = x._size;
		size_type	tmpcap = x._capacity;
		T *			tmptr = x._vct;

		x._size = this->_size;
		x._capacity = this->_capacity;
		x._vct = this->_vct;
		this->_size = tmpsize;
		this->_capacity = tmpcap;
		this->_vct = tmptr;
	}

	void clear (void)
	{
		_size = 0;
	}

	//////////////////////////////
	// Allocator
	//////////////////////////////

	allocator_type get_allocator() const
	{
		return (allocator_type());
	}

	//////////////////////////////
	// Member variables
	//////////////////////////////

private:
	const static size_type		_max_size = SIZE_MAX / sizeof(T);
	size_type					_size;
	size_type					_capacity;
	T *							_vct;
};

	//////////////////////////////
	// Relational operators
	//////////////////////////////

	// TBD

} // Namespace ft

#endif
