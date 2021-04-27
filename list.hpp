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
		struct s_node *		prev;
		struct s_node *		next;
	}						node;

	typedef struct			s_datanode : public node
	{
		T					data;
	}						datanode;

	//////////////////////////////
	// Iterator subclass
	//////////////////////////////

	template <bool IsConst>
	class listIterator {
		template <class it>
		friend class			reverse_iterator;
		friend class			list;
	public:
		// Member types
		typedef typename		ft::conditional<IsConst, const T, T>::type					value_type;
		typedef typename		ft::conditional<IsConst, const node, node>::type			node_type;
		typedef typename		ft::conditional<IsConst, const datanode, datanode>::type	datanode_type;
		typedef					std::ptrdiff_t												difference_type;
		typedef					std::size_t													size_type;
		// -structors
		listIterator			(void)														{ _ptr = NULL; }
		listIterator			(node_type * const ptr)										{ _ptr = ptr; }
		~listIterator			(void)														{}
		// Const stuff
		template <bool B>		friend class												listIterator;
		friend class			list;
		template <bool B>		listIterator
			(const listIterator<B> & x, typename ft::enable_if<!B>::type* = 0)				{ _ptr = x._ptr; }

		// Assignment
		listIterator &			operator=	(const listIterator & x)						{ _ptr = x._ptr; return (*this); }
		// Comparison
		template <bool B> bool	operator==	(const listIterator<B> & x) const				{ return (_ptr == x._ptr); }
		template <bool B> bool	operator!=	(const listIterator<B> & x) const				{ return (_ptr != x._ptr); }
		// -crementation
		listIterator &			operator++	(void)											{ _ptr = _ptr->next; return (*this); }
		listIterator &			operator--	(void)											{ _ptr = _ptr->prev; return (*this); }
		listIterator			operator++	(int)											{ listIterator<IsConst> x(*this); _ptr = _ptr->next; return (x); }
		listIterator			operator--	(int)											{ listIterator<IsConst> x(*this); _ptr = _ptr->prev; return (x); }
		// Dereference
		value_type &			operator*	(void)											{ return (static_cast<datanode_type *>(_ptr)->data); }
		value_type *			operator->	(void)											{ return (&static_cast<datanode_type *>(_ptr)->data); }

	protected:
		node_type *			_ptr;
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
		this->_new_end_node();
	}

	explicit list (size_type n, const value_type & val = value_type(), const allocator_type & alloc = allocator_type())
	{
		_alloc = alloc;
		this->_new_end_node();

		while (n-- > 0)
			this->push_back(val);
	}

	template <class InputIterator>
	list (InputIterator first, InputIterator last, const allocator_type & alloc = allocator_type(),
	typename ft::enable_if<!ft::is_same<InputIterator, int>::value>::type* = 0)
	{
		_alloc = alloc;
		this->_new_end_node();

		while (first != last)
			this->push_back(*first++);
	}

	list (const list & x)
	{
		this->_new_end_node();
		*this = x;
	}

	//////////////////////////////
	// Destructors
	//////////////////////////////

	~list (void)
	{
		this->clear();
		delete _end;
	}

	//////////////////////////////
	// Assignment operator
	//////////////////////////////

	list & operator= (const list & x)
	{
		this->clear();
		_alloc = x._alloc;

		for (const_iterator it = x.begin() ; it != x.end() ; it++)
			this->push_back(*it);
		return (*this);
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
		for ( ; n > 0 && it != this->end() ; n--)
			this->erase(it++);
	}

	size_type max_size (void) const
	{
		std::allocator<datanode>	al;
		return (al.max_size());
	}

	//////////////////////////////
	// Member access
	//////////////////////////////

	reference front (void)
	{
		return (static_cast<datanode *>(_end->next)->data);
	}

	const_reference front (void) const
	{
		return (static_cast<datanode *>(_end->next)->data);
	}

	reference back (void)
	{
		return (static_cast<datanode *>(_end->prev)->data);
	}

	const_reference back (void) const
	{
		return (static_cast<datanode *>(_end->prev)->data);
	}

	//////////////////////////////
	// Assignment modifiers
	//////////////////////////////

	template <class InputIterator>
	void assign (InputIterator first, InputIterator last,
	typename ft::enable_if<!ft::is_same<InputIterator, int>::value>::type* = 0)
	{
		*this = list(first, last);
	}

	void assign (size_type n, const value_type & val)
	{
		*this = list(n, val);
	}

	//////////////////////////////
	// Insertion modifiers
	//////////////////////////////

	iterator insert (iterator position, const value_type & val)
	{
		datanode *	new_node = new datanode;
		new_node->prev = position->next->prev;
		new_node->data = val;
		new_node->next = position->next;
		position->next = new_node;
		new_node->next->prev = new_node;
		return (new_node);
	}

	void insert (iterator position, size_type n, const value_type & val)
	{
		while (n-- > 0)
			position = this->insert(position, val);
	}

	template <class InputIterator>
	void insert (iterator position, InputIterator first, InputIterator last,
	typename ft::enable_if<!ft::is_same<InputIterator, int>::value>::type* = 0)
	{
		while (first != last)
			position = this->insert(position, *first++);
	}

	//////////////////////////////
	// Erasure modifiers
	//////////////////////////////

	iterator erase (iterator position)
	{
		node *	position_node = position->next->prev;
		position->next->prev = position->prev;
		position->prev->next = position->next;
		position = position->next;
		delete position_node;
		return (position);
	}

	iterator erase (iterator first, iterator last)
	{
		for (iterator it = first++ ; it != last ; it = first++)
			this->erase(it);
		return (last);
	}

	//////////////////////////////
	// Common modifiers
	//////////////////////////////

	void push_front (const value_type & val)
	{
		this->insert(_end->next, val);
	}

	void pop_front (void)
	{
		this->erase(_end->next);
	}

	void push_back (const value_type & val)
	{
		this->insert(_end->prev, val);
	}

	void pop_back (void)
	{
		this->erase(_end->prev);
	}

	void swap (list & x)
	{
		ft::swap(_alloc, x._alloc);
		ft::swap(_end, x._end);
	}

	void clear (void)
	{
		for (node *prev = _end->next, *next = _end->next->next ; prev != _end ; prev = next, next = next->next)
			delete prev;
		_end->prev = _end;
		_end->next = _end;
	}

	//////////////////////////////
	// Splicing operations
	//////////////////////////////

	void splice (iterator position, list & x)
	{
		if (!x.empty())
		{
			x._end->next->prev = position;
			x._end->prev->next = position->next;
			position->next->prev = x._end->prev;
			position->next = x._end->next;
			x._end->next = x._end;
			x._end->prev = x._end;
		}
	}

	void splice (iterator position, list & x, iterator i)
	{
		if (!x.empty())
		{
			i->next->prev = i->prev;
			i->prev->next = i->next;
			i->prev = position;
			i->next = position->next;
			position->next->prev = i;
			position->next = i;
		}
	}

	void splice (iterator position, list & x, iterator first, iterator last)
	{
		if (!x.empty())
		{
			position->next->prev = last->prev;
			last->prev = first->prev;
			first->prev->next = last;
			first->prev = position;
			last->next = position->next;
			position->next = first;
		}
	}

	//////////////////////////////
	// Removal operations
	//////////////////////////////

	void remove (const value_type & val)
	{
		for (iterator it = this->begin() ; it != this->end() ; )
		{
			iterator	cpy = it++;
			if (cpy->data == val)
				this->erase(cpy);
		}
	}

	template <class Predicate>
	void remove_if (Predicate pred)
	{
		for (iterator it = this->begin() ; it != this->end() ; it++)
		{
			iterator	cpy = it;
			if (pred(cpy->data))
				this->erase(cpy);
		}
	}

	//////////////////////////////
	// Uniquify operations
	//////////////////////////////

	void unique (void)
	{
		this->unique(&ft::equal);
	}

	template <class BinaryPredicate>
	void unique (BinaryPredicate binary_pred)
	{
		for (iterator it = this->begin()->next ; it != this->end() ; it++)
		{
			if (binary_pred(it->data, it->prev->data))
			{
				this->erase(it);
				it = this->begin();
			}
		}
	}

	//////////////////////////////
	// Merging operations
	//////////////////////////////

	void merge (list & x)
	{
		this->merge(x, &ft::lexicographical_compare);
	}

	template <class Compare>
	void merge (list & x, Compare comp)
	{
		for (iterator it = this->begin() ; it != this->end() ; it++)
		{
			iterator	it2 = x->begin();
			if (it2 != x->end() && comp(it2->data, it->data))
				this->splice(it, x, it2);
		}
	}

	//////////////////////////////
	// Sorting operations
	//////////////////////////////

	void sort (void)
	{
		this->_quicksort(&ft::lexicographical_compare, this->begin(), this->end());
	}

	template <class Compare>
	void sort (Compare comp)
	{
		this->_quicksort(comp, this->begin(), this->end());
	}

	void reverse (void)
	{
		for (iterator it = this->begin() ; it != this->end() ; it--)
			swap(it->prev, it->next);
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
	void _new_end_node (void)
	{
		_end = new node;
		_end->prev = _end;
		_end->next = _end;
	}

	template <class Compare>
	void _quicksort (Compare comp, iterator first, iterator last)
	{
		if (first != last && first->next != last)
		{
			iterator	it = this->_partition(comp, first, last);
			this->_quicksort(first, it);
			it++;
			this->_quicksort(it, last);
		}
	}

	template <class Compare>
	void _partition (Compare comp, iterator first, iterator last)
	{
		iterator	prev = first;
		for (iterator it = first ; it != last->prev ; it++)
		{
			if (!comp(last->prev->data, it->data))
				ft::swap((prev++)->data, it->data);
		}
		ft::swap(prev->data, last->prev->data);
	}

	//////////////////////////////
	// Member variables
	//////////////////////////////

	allocator_type		_alloc;
	node *				_end;
};

	//////////////////////////////
	// Relational operators
	//////////////////////////////

	template <class T, class Alloc>
	bool operator== (const list<T,Alloc> & lhs, const list<T,Alloc> & rhs)
	{
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class T, class Alloc>
	bool operator<  (const list<T,Alloc> & lhs, const list<T,Alloc> & rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class T, class Alloc>
	bool operator!= (const list<T,Alloc> & lhs, const list<T,Alloc> & rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T, class Alloc>
	bool operator<= (const list<T,Alloc> & lhs, const list<T,Alloc> & rhs)
	{
		return (!(rhs < lhs));
	}

	template <class T, class Alloc>
	bool operator>  (const list<T,Alloc> & lhs, const list<T,Alloc> & rhs)
	{
		return (rhs < lhs);
	}

	template <class T, class Alloc>
	bool operator>= (const list<T,Alloc> & lhs, const list<T,Alloc> & rhs)
	{
		return (!(lhs < rhs));
	}

	template <class T, class Alloc>
	void swap (list<T,Alloc> & x, list<T,Alloc> & y)
	{
		x.swap(y);
	}

} // Namespace ft

#endif
