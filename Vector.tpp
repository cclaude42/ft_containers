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

		template <bool IsConst = false>
		class VectorIterator {
		public:
			// typedef		typename std::conditional<IsConst, typename Alloc::const_pointer, typename Alloc::pointer>::type		RealPointer;
			// -structors
			VectorIterator (void) { _ptr = NULL; }
			VectorIterator (const typename Alloc::pointer ptr) { _ptr = ptr; }
			VectorIterator (const VectorIterator & x) { _ptr = x._ptr; }
			~VectorIterator (void) {}
			// Assignment
			VectorIterator &	operator=  (const VectorIterator & x)			{ _ptr = x._ptr; return (*this); }
			VectorIterator &	operator+= (int n)								{ _ptr += n; return (*this); }
			VectorIterator &	operator-= (int n)								{ _ptr -= n; return (*this); }
			VectorIterator &	operator+= (const VectorIterator & x)			{ _ptr += x._ptr; return (*this); }
			VectorIterator &	operator-= (const VectorIterator & x)			{ _ptr -= x._ptr; return (*this); }
			// Comparison
			bool				operator== (const VectorIterator & x) const		{ return (_ptr == x._ptr); }
			bool				operator!= (const VectorIterator & x) const		{ return (_ptr != x._ptr); }
			bool				operator<  (const VectorIterator & x) const		{ return (_ptr < x._ptr); }
			bool				operator>  (const VectorIterator & x) const		{ return (_ptr > x._ptr); }
			bool				operator<= (const VectorIterator & x) const		{ return (_ptr <= x._ptr); }
			bool				operator>= (const VectorIterator & x) const		{ return (_ptr >= x._ptr); }
			// -crementation
			VectorIterator &	operator++ (void)								{ _ptr++; return (*this); }
			VectorIterator &	operator-- (void)								{ _ptr--; return (*this); }
			VectorIterator		operator++ (int)								{ VectorIterator x(*this); _ptr++; return (x); }
			VectorIterator		operator-- (int)								{ VectorIterator x(*this); _ptr--; return (x); }
			// Operation
			VectorIterator		operator+  (int n) const						{ return (_ptr + n); }
			VectorIterator		operator-  (int n) const						{ return (_ptr - n); }
			int					operator-  (const VectorIterator & x) const		{ return (_ptr - x._ptr); }
			// Indirection
			T &					operator*  (void) const							{ return (*_ptr); }

		// private:
			typename Alloc::pointer	_ptr;
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
		typedef		VectorIterator<false>						iterator;
		typedef		VectorIterator<true>						const_iterator;
		// typedef		int											reverse_iterator;
		// typedef		int											const_reverse_iterator;
		typedef		std::ptrdiff_t									difference_type;
		typedef		size_t										size_type;

		//////////////////////////////
		// Constructors
		//////////////////////////////

		explicit Vector (const allocator_type & alloc = allocator_type())
		{
			(void)alloc;
			_vct = NULL;
			_occupied = 0;
			_allocated = 0;

			std::cerr << "DEFAULT CONSTRUCTOR : allocating " << _allocated << " blocks for " << _occupied << " elements." << std::endl;
		}

		explicit Vector (size_type n, const value_type & val = value_type(), const allocator_type & alloc = allocator_type())
		{
			(void)alloc;
			_occupied = n;
			_allocated = _occupied / _factor * _factor + _factor;
			_vct = new T[_allocated];

			for (int i = 0 ; i < _occupied ; i++)
				_vct[i] = val;

			std::cerr << "FILL CONSTRUCTOR : allocating " << _allocated << " blocks for " << _occupied << " elements." << std::endl;
		}

		template <class InputIterator>
		Vector (InputIterator first, InputIterator last, const allocator_type & alloc = allocator_type(), typename ft::enable_if<!ft::is_same<InputIterator, int>::value>::type* = 0)
		{
			(void)alloc;
			if (last - first < 0)
				throw std::bad_alloc();

			_occupied = last - first;
			_allocated = _occupied / _factor * _factor + _factor;
			_vct = new T[_allocated];

			for (int i = 0 ; first != last ; i++)
				_vct[i] = *first++;

			std::cerr << "RANGE CONSTRUCTOR : allocating " << _allocated << " blocks for " << _occupied << " elements." << std::endl;
		}

		Vector (const Vector & x)
		{
			_occupied = x._occupied;
			_allocated = x._allocated;
			_vct = new T[_allocated];

			for (int i = 0 ; i < _occupied ; i++)
				_vct[i] = x[i];

			std::cerr << "COPY CONSTRUCTOR : allocating " << _allocated << " blocks for " << _occupied << " elements." << std::endl;
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

			std::cerr << "Allocating " << _allocated << " blocks for " << _occupied << " elements." << std::endl;
		}

		//////////////////////////////
		// Iterators
		//////////////////////////////

		// iterator begin()
		// {
		// 	return (iterator(_vct));
		// }

		const_iterator begin() const
		{
			return (const_iterator(_vct));
		}

		// iterator end()
		// {
		// 	return (iterator(_vct + _occupied));
		// }

		const_iterator end() const
		{
			return (const_iterator(_vct + _occupied));
		}

		//////////////////////////////
		// Reverse iterators
		//////////////////////////////

		// reverse_iterator rbegin()
		// {
		// 	return (_vct + _occupied - 1);
		// }
		//
		// const_reverse_iterator rbegin() const
		// {
		// 	return (_vct + _occupied - 1);
		// }
		//
		// reverse_iterator rend()
		// {
		// 	return (_vct - 1);
		// }
		//
		// const_reverse_iterator rend() const
		// {
		// 	return (_vct - 1);
		// }

	private:
		const static unsigned int	_factor = 10;
		unsigned int				_occupied;
		unsigned int				_allocated;
		T							*_vct;
	};

}

#endif
