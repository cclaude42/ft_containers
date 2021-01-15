#ifndef VECTOR_TPP
# define VECTOR_TPP

# include <iostream>
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
		_occupied = 0;
		_allocated = 0;
	}

	explicit Vector (size_type n, const value_type & val = value_type(), const allocator_type & alloc = allocator_type())
	{
		(void)alloc;
		_occupied = n;
		_allocated = _occupied / _factor * _factor + _factor;
		_vct = new T[_allocated];

		for (int i = 0 ; i < _occupied ; i++)
			_vct[i] = val;
	}

	template <class InputIterator>
	Vector (InputIterator first, InputIterator last, const allocator_type & alloc = allocator_type(),
			typename ft::enable_if<!ft::is_same<InputIterator, int>::value>::type* = 0)
	{
		(void)alloc;
		if (last - first < 0)
			throw std::bad_alloc();

		_occupied = last - first;
		_allocated = _occupied / _factor * _factor + _factor;
		_vct = new T[_allocated];

		for (int i = 0 ; first != last ; i++)
			_vct[i] = *first++;
	}

	Vector (const Vector & x)
	{
		_occupied = x._occupied;
		_allocated = x._allocated;
		_vct = new T[_allocated];

		for (int i = 0 ; i < _occupied ; i++)
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

		_occupied = x._occupied;
		_allocated = x._allocated;
		_vct = new T[_allocated];

		for (int i = 0 ; i < _occupied ; i++)
			_vct[i] = x[i];
	}

	//////////////////////////////
	// Iterators
	//////////////////////////////

	iterator begin()
	{
		return (iterator(_vct));
	}

	const_iterator begin() const
	{
		return (const_iterator(_vct));
	}

	iterator end()
	{
		return (iterator(_vct + _occupied));
	}

	const_iterator end() const
	{
		return (const_iterator(_vct + _occupied));
	}

	//////////////////////////////
	// Reverse iterators
	//////////////////////////////

	reverse_iterator rbegin()
	{
		return (reverse_iterator(_vct + _occupied - 1));
	}

	const_reverse_iterator rbegin() const
	{
		return (const_reverse_iterator(_vct + _occupied - 1));
	}

	reverse_iterator rend()
	{
		return (reverse_iterator(_vct - 1));
	}

	const_reverse_iterator rend() const
	{
		return (const_reverse_iterator(_vct - 1));
	}

private:
	const static unsigned int	_factor = 10;
	unsigned int				_occupied;
	unsigned int				_allocated;
	T *							_vct;
};

} // Namespace ft

#endif
