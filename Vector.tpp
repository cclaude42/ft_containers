#ifndef VECTOR_TPP
# define VECTOR_TPP

# include <iostream>
# include <stdint.h>
# include "Types.tpp"

namespace ft
{

template <class T, class Alloc = std::allocator<T> >
class Vector {
public:

	//////////////////////////////
	// Iterator subclass
	//////////////////////////////

	template <bool IsConst, bool IsRev>
	class VectorIterator {
	public:
		// Friend other instances
		template <bool U, bool V>
		friend class VectorIterator;
		// Member types
		typedef typename ft::conditional<IsConst, const T, T>::type			ValueType;
		typedef typename ft::conditional<IsConst,
		typename Alloc::const_pointer, typename Alloc::pointer>::type		PointerType;
		typedef typename ft::conditional<IsConst,
		typename Alloc::const_reference, typename Alloc::reference>::type	ReferenceType;

		// -structors
		VectorIterator		(void)											{ _ptr = NULL; }
		VectorIterator		(const PointerType ptr)							{ _ptr = ptr; }
		VectorIterator		(const VectorIterator & x)						{ _ptr = x._ptr; }
		~VectorIterator		(void)											{}
		// Cast non-const => const
		template <bool U, bool V>
		VectorIterator		(const VectorIterator<U, V> & x,
							typename ft::enable_if<!U>::type* = 0,
							typename ft::enable_if<IsRev == V>::type* = 0)	{ _ptr = x._ptr; }

		// Assignment
		VectorIterator &	operator=  (const VectorIterator & x)			{ _ptr = x._ptr; return (*this); }
		VectorIterator &	operator+= (int n)								{ _ptr = IsRev ? _ptr - n : _ptr + n; return (*this); }
		VectorIterator &	operator-= (int n)								{ _ptr = IsRev ? _ptr + n : _ptr - n; return (*this); }
		VectorIterator &	operator-= (const VectorIterator & x)			{ _ptr = IsRev ? x._ptr - _ptr : _ptr - x._ptr; return (*this); }
		// Comparison
		bool				operator== (const VectorIterator & x) const		{ return (_ptr == x._ptr); }
		bool				operator!= (const VectorIterator & x) const		{ return (_ptr != x._ptr); }
		bool				operator<  (const VectorIterator & x) const		{ return (IsRev ? _ptr > x._ptr : _ptr < x._ptr); }
		bool				operator>  (const VectorIterator & x) const		{ return (IsRev ? _ptr < x._ptr : _ptr > x._ptr); }
		bool				operator<= (const VectorIterator & x) const		{ return (IsRev ? _ptr >= x._ptr : _ptr <= x._ptr); }
		bool				operator>= (const VectorIterator & x) const		{ return (IsRev ? _ptr <= x._ptr : _ptr >= x._ptr); }
		// -crementation
		VectorIterator &	operator++ (void)								{ IsRev ? _ptr-- : _ptr++; return (*this); }
		VectorIterator &	operator-- (void)								{ IsRev ? _ptr++ : _ptr--; return (*this); }
		VectorIterator		operator++ (int)								{ VectorIterator x(*this); IsRev ? _ptr-- : _ptr++; return (x); }
		VectorIterator		operator-- (int)								{ VectorIterator x(*this); IsRev ? _ptr++ : _ptr--; return (x); }
		// Operation
		VectorIterator		operator+  (int n) const						{ return (IsRev ? _ptr - n : _ptr + n); }
		VectorIterator		operator-  (int n) const						{ return (IsRev ? _ptr + n : _ptr - n); }
		std::ptrdiff_t		operator-  (const VectorIterator & x) const		{ return (IsRev ? x._ptr - _ptr : _ptr - x._ptr); }
		// Dereference
		ReferenceType		operator*  (void)								{ return (*_ptr); }

	private:
		PointerType		_ptr;
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
	typedef		VectorIterator<false, false>					iterator;
	typedef		VectorIterator<true, false>						const_iterator;
	typedef		VectorIterator<false, true>						reverse_iterator;
	typedef		VectorIterator<true, true>						const_reverse_iterator;
	typedef		std::ptrdiff_t									difference_type;
	typedef		std::size_t										size_type;

	//////////////////////////////
	// Constructors
	//////////////////////////////

	explicit Vector (const allocator_type & alloc = allocator_type())
	{
		(void)alloc;
		_vct = NULL;
		_size = 0;
		_capacity = 0;
	}

	explicit Vector (size_type n, const value_type & val = value_type(), const allocator_type & alloc = allocator_type())
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
	Vector (InputIterator first, InputIterator last, const allocator_type & alloc = allocator_type(),
			typename ft::enable_if<!ft::is_same<InputIterator, int>::value>::type* = 0)
	{
		(void)alloc;
		if (last - first < 0)
			throw std::bad_alloc();

		size_type		n = last - first;

		_size = n;
		_capacity = n;
		if (n > 0)
			_vct = new T[n];
		else
			_vct = NULL;

		for (size_type i = 0 ; i < n ; i++)
			_vct[i] = *first++;
	}

	Vector (const Vector & x)
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

	~Vector (void)
	{
		if (_vct != NULL)
			delete [] _vct;
	}

	//////////////////////////////
	// Assignment operator
	//////////////////////////////

	Vector & operator= (const Vector & x)
	{
		if (_vct != NULL)
			delete [] _vct;

		_size = x._size;
		_capacity = x._capacity;
		_vct = new T[_capacity];

		for (size_type i = 0 ; i < _size ; i++)
			_vct[i] = x[i];
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
		size_type	i;

		if (n > _capacity)
		{
			if (n > _capacity * 2)
				_capacity = n;
			else
				_capacity = _capacity * 2;

			T *		new_vct = new T[_capacity];

			for ( i = 0 ; i < _size ; i++ )
				new_vct[i] = _vct[i];
			while (i < _capacity)
				new_vct[i++] = val;

			if (_vct)
				delete [] _vct;

			_size = n;
			_vct = new_vct;
		}
		else if (n > _size)
		{
			for ( i = _size ; i < n ; i++ )
				_vct[i] = val;

			_size = n;
		}
		else
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
			throw std::length_error("Vector::reserve : Size n > _max_size");

		if (n > _capacity)
		{
			T *		new_vct = new T[n];

			for ( size_type i = 0 ; i < _size ; i++ )
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
			throw std::out_of_range("Vector::at : Index n >= _size");
		return (_vct[n]);
	}

	const_reference at (size_type n) const
	{
		if (n >= _size)
			throw std::out_of_range("Vector::at : Index n >= _size");
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
	void assign (InputIterator first, InputIterator last)
	{
		if (last - first < 0)
			throw std::bad_alloc();

		size_type		n = last - first;

		_size = n;
		if (n > _capacity)
		{
			_capacity = n;
			if (_vct)
				delete [] _vct;

			if (n > 0)
				_vct = new T[n];
			else
				_vct = NULL;
		}

		for (size_type i = 0 ; i < n ; i++)
			_vct[i] = *first++;
	}

	void assign (size_type n, const value_type & val)
	{
		_size = n;
		if (n > _capacity)
			this->reserve(n);

		for (size_type i = 0 ; i < n ; i++)
			_vct[i] = val;
	}

	//////////////////////////////
	// Insertion modifiers
	//////////////////////////////

	iterator insert (iterator position, const value_type & val)
	{
		if (_size == _capacity)
		{
			if (_capacity)
				this->reserve(_capacity * 2);
			else
				this->reserve(1);
		}

		for ( size_type i = _size ; i > position - this->begin() ; i-- )
			_vct[i] = _vct[i - 1];

		_vct[position - this->begin()] = val;
		_size++;
	}

	void insert (iterator position, size_type n, const value_type & val)
	{
		while (_size + n > _capacity)
		{
			if (_capacity)
				this->reserve(_capacity * 2);
			else
				this->reserve(1);
		}

		for ( size_type i = _size + n - 1 ; i > position - this->begin() + n - 1 ; i-- )
			_vct[i] = _vct[i - n];

		for ( size_type j = position - this->begin() ; j < n ; j++ )
			_vct[j] = val;
		_size = _size + n;
	}

	template <class InputIterator>
	void insert (iterator position, InputIterator first, InputIterator last)
	{
		size_type		n = last - first;

		while (_size + n > _capacity)
		{
			if (_capacity)
				this->reserve(_capacity * 2);
			else
				this->reserve(1);
		}

		for ( size_type i = _size + n - 1 ; i > position - this->begin() + n - 1 ; i-- )
			_vct[i] = _vct[i - n];

		for ( size_type j = position - this->begin() ; j < n ; j++ )
			_vct[j] = *first++;
		_size = _size + n;
	}

	//////////////////////////////
	// Erasure modifiers
	//////////////////////////////

	iterator erase (iterator position)
	{
		for ( size_type i = position - this->begin() ; i < _size - 1 ; i++ )
			_vct[i] = _vct[i + 1];
		_size--;
	}

	iterator erase (iterator first, iterator last)
	{
		size_type	n = last - first;

		for ( size_type i = first - this->begin() ; i < _size - n ; i++ )
			_vct[i] = _vct[i + n];
		_size = _size - n;
	}

	//////////////////////////////
	// Common modifiers
	//////////////////////////////

	void push_back (const value_type & val)
	{
		if (_size == _capacity)
			this->reserve(_capacity * 2);

		_vct[_size] = val;
		_size++;
	}

	void pop_back (void)
	{
		_size--;
	}

	void swap (Vector & x)
	{
		Vector	tmp(x);

		x = *this;
		*this = tmp;
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
	const static size_type		_max_size = SIZE_MAX / 4;
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
