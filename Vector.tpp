

#ifndef VECTOR_TPP
# define VECTOR_TPP

# include <iostream>

template <class T, class Alloc = std::allocator<T>>
class Vector {
public:
	// Member types
	typedef		value_type				T;
	typedef		allocator_type			Alloc;
	typedef		reference				allocator_type::reference;
	typedef		const_reference			allocator_type::const_reference;
	typedef		pointer					allocator_type::pointer;
	typedef		const_pointer			allocator_type::const_pointer;
	typedef		iterator				???;
	typedef		const_iterator			???;
	typedef		reverse_iterator		reverse_iterator<iterator>;
	typedef		const_reverse_iterator	reverse_iterator<const_iterator>;
	typedef		difference_type			iterator_traits<iterator>::difference_type;
	typedef		size_type				size_t???;

private:
	T		*_vct;
	int		_size;
};

#endif
