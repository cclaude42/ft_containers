#ifndef LIST_HPP
# define LIST_HPP

# include <iostream>
# include "includes/iterator.hpp"
# include "includes/types.hpp"
# include "includes/utils.hpp"

namespace ft
{

template <class T, class Alloc = std::allocator<T> >
class list {
public:

	//////////////////////////////
	// Node
	//////////////////////////////

	typedef struct			s_node
	{
		T					data;
		struct s_node *		prev;
		struct s_node *		next;
	}						node;

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
		value_type &			operator*	(void)									{ return (_ptr->data); }
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

	explicit list (size_type n, const value_type & val = value_type(), const allocator_type & alloc = allocator_type())
	{
		_alloc = alloc;
		_end = new node;
		_end->prev = _end;
		_end->next = _end;

		for (node *prev_node = _end ; n > 0 ; n--)
		{
			node	*new_node = new node;
			prev_node->next = new_node;
			new_node->prev = prev_node;
			new_node->data = val;
			new_node->next = _end;
			_end->prev = new_node;
			prev_node = new_node;
		}
	}

	template <class InputIterator>
	list (InputIterator first, InputIterator last, const allocator_type & alloc = allocator_type())
	{
		_alloc = alloc;
		_end = new node;
		_end->prev = _end;
		_end->next = _end;

		for (node *prev_node = _end ; first != last ; first++)
		{
			node	*new_node = new node;
			prev_node->next = new_node;
			new_node->prev = prev_node;
			new_node->data = *first;
			new_node->next = _end;
			_end->prev = new_node;
			prev_node = new_node;
		}
	}

	list (const list & x)
	{
		*this = x;
	}

	//////////////////////////////
	// Destructors
	//////////////////////////////

	~list (void)
	{
		for (node *prev = _end->next, *next = _end->next->next ; prev != _end ; prev = next, next = next->next)
			delete prev;
		delete _end;
	}

	//////////////////////////////
	// Assignment operator
	//////////////////////////////

	list & operator= (const list & x)
	{
		_alloc = x._alloc;
		_end = new node;
		_end->prev = _end;
		_end->next = _end;

		node *	prev_node = _end;
		for (iterator it = x.begin() ; it != x.end() ; it++)
		{
			node	*new_node = new node;
			prev_node->next = new_node;
			new_node->prev = prev_node;
			new_node->data = *it;
			new_node->next = _end;
			_end->prev = new_node;
			prev_node = new_node;
		}
	}

	//////////////////////////////
	// Iterators
	//////////////////////////////

	iterator begin (void)
	{
		return (iterator(_end->next));
	}

	const_iterator begin (void) const
	{
		return (const_iterator(_end->next));
	}

	iterator end (void)
	{
		return (iterator(_end));
	}

	const_iterator end (void) const
	{
		return (const_iterator(_end));
	}

	//////////////////////////////
	// Reverse iterators
	//////////////////////////////

	reverse_iterator rbegin (void)
	{
		return (reverse_iterator(_end->prev));
	}

	const_reverse_iterator rbegin (void) const
	{
		return (const_reverse_iterator(_end->prev));
	}

	reverse_iterator rend (void)
	{
		return (reverse_iterator(_end));
	}

	const_reverse_iterator rend (void) const
	{
		return (const_reverse_iterator(_end));
	}

	//////////////////////////////
	// Capacity
	//////////////////////////////

	bool empty (void) const
	{
		return (_end == _end->next);
	}

	size_type size (void) const
	{
		size_type	n = 0;
		for (node *curr = _end->next ; curr != _end ; curr = curr->next)
			n++;
		return (n);
	}

	void resize (size_type n, value_type val = value_type())
	{
		iterator	it = this->begin();
		for ( ; it != this->end() && n > 0 ; it++)
			n--;
		for ( ; it != this->end() ; it++)
			this->push_back(val);
		for ( ; n > 0 ; n--)
			this->erase(it++);
	}

	size_type max_size (void) const
	{
		return (_alloc.max_size());
	}

	//////////////////////////////
	// Member access
	//////////////////////////////

	reference front (void)
	{
		return (_end->next);
	}

	const_reference front (void) const
	{
		return (_end->next);
	}

	reference back (void)
	{
		return (_end->prev);
	}

	const_reference back (void) const
	{
		return (_end->prev);
	}

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
