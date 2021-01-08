

#ifndef VECTOR_TPP
# define VECTOR_TPP

# include <iostream>

template <class T, class Alloc = std::allocator<T>>
class Vector {
public:

	//////////////////////////////
	// Iterator subclass
	//////////////////////////////

	class MyIterator {
	public:


	private:
		typename allocator_type::pointer	_ptr;
	};

	//////////////////////////////
	// Member types
	//////////////////////////////

	typedef		T											value_type;
	typedef		Alloc										allocator_type;
	typedef		typename allocator_type::reference			reference;
	typedef		typename allocator_type::const_reference	const_reference;
	typedef		typename allocator_type::pointer			pointer;
	typedef		typename allocator_type::const_pointer		const_pointer;
	typedef		MyIterator									iterator;
	typedef		int											const_iterator;
	typedef		int											reverse_iterator;
	typedef		int											const_reverse_iterator;
	typedef		ptrdiff_t									difference_type;
	typedef		size_t										size_type;

	//////////////////////////////
	// Constructors
	//////////////////////////////

	explicit Vector (const allocator_type & alloc = allocator_type())
	{
		_vct = NULL;
		_occupied = 0;
		_allocated = 0;

		std::cout << "Allocating " << _allocated << " blocks for " << _occupied << " elements." << std::endl;
	}

	explicit Vector (size_type n, const value_type & val = value_type(), const allocator_type & alloc = allocator_type())
	{
		_occupied = n;
		_allocated = _occupied / _factor * _factor + _factor;
		_vct = new T[_allocated];

		std::cout << "Allocating " << _allocated << " blocks for " << _occupied << " elements." << std::endl;

		for (int i = 0 ; i < _occupied ; i++)
			_vct[i] = val;
	}

	template <class InputIterator>
	Vector (InputIterator first, InputIterator last, const allocator_type & alloc = allocator_type())
	{
		InputIterator	copy = first;
		unsigned int	size;

		while (copy++ != last)
			size++;

		_occupied = size;
		_allocated = _occupied / _factor * _factor + _factor;
		_vct = new T[_allocated];

		std::cout << "Allocating " << _allocated << " blocks for " << _occupied << " elements." << std::endl;

		for (int i = 0 ; first != last ; i++)
			_vct[i] = *first++;
	}

	Vector (const Vector & x)
	{
		_occupied = x._occupied;
		_allocated = x._allocated;
		_vct = new T[_allocated];

		std::cout << "Allocating " << _allocated << " blocks for " << _occupied << " elements." << std::endl;

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

		std::cout << "Allocating " << _allocated << " blocks for " << _occupied << " elements." << std::endl;

		for (int i = 0 ; i < _occupied ; i++)
			_vct[i] = x[i];
	}

	//////////////////////////////
	// Iterators
	//////////////////////////////

	iterator begin()
	{
		return (_vct);
	}

	const_iterator begin() const
	{
		return (_vct);
	}

	iterator end()
	{
		return (_vct + _occupied);
	}

	const_iterator end() const
	{
		return (_vct + _occupied);
	}

	//////////////////////////////
	// Reverse iterators
	//////////////////////////////

	reverse_iterator rbegin()
	{
		return (_vct + _occupied - 1);
	}

	const_reverse_iterator rbegin() const
	{
		return (_vct + _occupied - 1);
	}

	reverse_iterator rend()
	{
		return (_vct - 1);
	}

	const_reverse_iterator rend() const
	{
		return (_vct - 1);
	}

private:
	unsigned int	_factor = 10;
	unsigned int	_occupied;
	unsigned int	_allocated;
	T				*_vct;
};

#endif
