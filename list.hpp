#ifndef LIST_HPP
# define LIST_HPP

# include <iostream>
# include "includes/iterator.hpp"
# include "includes/types.hpp"
# include "includes/utils.hpp"

namespace ft
{

typedef struct			s_node
{
	T					data;
	struct s_node *		prev;
	struct s_node *		next;
}						node;

template <class T, class Alloc = std::allocator<T> >
class list {
public:

	//////////////////////////////
	// Iterator subclass
	//////////////////////////////

	template <bool IsConst>
	class listIterator {
		template <class it>
		friend class		reverse_iterator;
		friend class		list;
	public:
		// Member types
		typedef typename		ft::conditional<IsConst, const node, node>::type	value_type;
		typedef					std::ptrdiff_t										difference_type;
		typedef					std::size_t											size_type;
		// -structors
		listIterator			(void)												{ _ptr = NULL; }
		~listIterator			(void)												{}
		// Const stuff
		template <bool B>		friend class										listIterator;
		friend class			list;
		template <bool B>		listIterator
			(const listIterator<B> & x, typename ft::enable_if<!B>::type* = 0)		{ _ptr = x._ptr; }

		// Assignment
		listIterator &			operator=	(const listIterator & x)				{ _ptr = x._ptr; return (*this); }
		// Comparison
		template <bool B> bool	operator==	(const listIterator<B> & x) const		{ return (_ptr == x._ptr); }
		template <bool B> bool	operator!=	(const listIterator<B> & x) const		{ return (_ptr != x._ptr); }
		// -crementation
		listIterator &			operator++	(void)									{ _ptr = _ptr->next; return (*this); }
		listIterator &			operator--	(void)									{ _ptr = _ptr->prev; return (*this); }
		listIterator			operator++	(int)									{ listIterator<IsConst> x(*this); _ptr++; return (x); }
		listIterator			operator--	(int)									{ listIterator<IsConst> x(*this); _ptr--; return (x); }
		// Dereference
		value_type &			operator*	(void)									{ return (*_ptr); }
		value_type *			operator->	(void)									{ return (_ptr); }

# if __APPLE__
	private:
# endif
		listIterator			(value_type * const ptr)							{ _ptr = ptr; }

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
	typedef		listIterator<false>								iterator;
	typedef		listIterator<true>								const_iterator;
	typedef		ft::reverse_iterator<iterator>					reverse_iterator;
	typedef		ft::reverse_iterator<const_iterator>			const_reverse_iterator;
	typedef		typename listIterator<false>::difference_type	difference_type;
	typedef		typename listIterator<false>::size_type			size_type;

	//////////////////////////////
	// Constructors
	//////////////////////////////

	explicit list (const allocator_type & alloc = allocator_type())
	{
		_alloc = alloc;
		_end = new node;
		_end->prev = _end;
		_end->next = _end;
	}

	//////////////////////////////
	// Destructors
	//////////////////////////////



	//////////////////////////////
	// Assignment operator
	//////////////////////////////



	//////////////////////////////
	// Iterators
	//////////////////////////////



	//////////////////////////////
	// Reverse iterators
	//////////////////////////////



	//////////////////////////////
	// Capacity
	//////////////////////////////



	//////////////////////////////
	// Member access
	//////////////////////////////



	//////////////////////////////
	// Assignment modifiers
	//////////////////////////////



	//////////////////////////////
	// Insertion modifiers
	//////////////////////////////



	//////////////////////////////
	// Erasure modifiers
	//////////////////////////////



	//////////////////////////////
	// Common modifiers
	//////////////////////////////



	//////////////////////////////
	// Allocator
	//////////////////////////////



	//////////////////////////////
	// Member variables
	//////////////////////////////

private:
	allocator_type		_alloc;
	node *				_end;
};

	//////////////////////////////
	// Relational operators
	//////////////////////////////



} // Namespace ft

#endif
