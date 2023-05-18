#ifndef LIST_HPP
# define LIST_HPP

# include "includes/containers.hpp"

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
	public:
		// Member types
		typedef typename		ft::conditional<IsConst, const T, T>::type					value_type;
		typedef typename		ft::conditional<IsConst, const node, node>::type			node_type;
		typedef					std::ptrdiff_t												difference_type;
		typedef					std::size_t													size_type;
		typedef typename		Alloc::reference											reference;
		typedef typename		Alloc::pointer												pointer;
		typedef					std::random_access_iterator_tag								iterator_category;
		// -structors
		listIterator			(void)														{ _ptr = NULL; }
		listIterator			(node_type * const ptr)										{ _ptr = ptr; }
		~listIterator			(void)														{}
		// Const stuff
		template <bool B>		listIterator
			(const listIterator<B> & x, typename ft::enable_if<!B>::type* = 0)				{ _ptr = x.getPtr(); }

		// Assignment
		listIterator &			operator=	(const listIterator & x)						{ _ptr = x.getPtr(); return (*this); }
		// Comparison
		template <bool B> bool	operator==	(const listIterator<B> & x) const				{ return (_ptr == x.getPtr()); }
		template <bool B> bool	operator!=	(const listIterator<B> & x) const				{ return (_ptr != x.getPtr()); }
		// -crementation
		listIterator &			operator++	(void)											{ _ptr = _ptr->next; return (*this); }
		listIterator &			operator--	(void)											{ _ptr = _ptr->prev; return (*this); }
		listIterator			operator++	(int)											{ listIterator<IsConst> x(*this); _ptr = _ptr->next; return (x); }
		listIterator			operator--	(int)											{ listIterator<IsConst> x(*this); _ptr = _ptr->prev; return (x); }
		// Dereference
		value_type &			operator*	(void) const									{ return (_ptr->data); }
		value_type *			operator->	(void) const									{ return (&_ptr->data); }
		// Member functions
		node_type *				getPtr		(void) const									{ return (_ptr); }

	private:
		node_type *				_ptr;
	}; // Iterator

	//////////////////////////////
	// Member types
	//////////////////////////////

	typedef		T												value_type;
	typedef		typename Alloc::template rebind<node>::other	allocator_type;
	typedef		typename Alloc::reference						reference;
	typedef		typename Alloc::const_reference					const_reference;
	typedef		typename Alloc::pointer							pointer;
	typedef		typename Alloc::const_pointer					const_pointer;
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
		_alloc.destroy(_end);
		_alloc.deallocate(_end, 1);
	}

	//////////////////////////////
	// Assignment operator
	//////////////////////////////

	list & operator= (const list & x)
	{
		if (this == &x)
			return (*this);

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
		return (reverse_iterator(_end));
	}

	const_reverse_iterator rbegin (void) const
	{
		return (const_reverse_iterator(_end));
	}

	reverse_iterator rend (void)
	{
		return (reverse_iterator(_end->next));
	}

	const_reverse_iterator rend (void) const
	{
		return (const_reverse_iterator(_end->next));
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
		while (this->size() < n)
			this->push_back(val);
		while (this->size() > n)
			this->erase(this->end().getPtr()->prev);
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
		return (_end->next->data);
	}

	const_reference front (void) const
	{
		return (_end->next->data);
	}

	reference back (void)
	{
		return (_end->prev->data);
	}

	const_reference back (void) const
	{
		return (_end->prev->data);
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
		node *	new_node = _alloc.allocate(1);
		this->_construct(new_node, position.getPtr()->prev, position.getPtr(), val);
		position.getPtr()->prev = new_node;
		new_node->prev->next = new_node;
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
			this->insert(position, *(first++));
	}

	//////////////////////////////
	// Erasure modifiers
	//////////////////////////////

	iterator erase (iterator position)
	{
		node *	position_node = position.getPtr();
		position = position.getPtr()->next;
		position_node->next->prev = position_node->prev;
		position_node->prev->next = position_node->next;
		_alloc.destroy(position_node);
		_alloc.deallocate(position_node, 1);
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
		this->insert(_end, val);
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
		{
			_alloc.destroy(prev);
			_alloc.deallocate(prev, 1);
		}
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
			x._end->next->prev = position.getPtr()->prev;
			x._end->prev->next = position.getPtr();
			position.getPtr()->prev->next = x._end->next;
			position.getPtr()->prev = x._end->prev;
			x._end->next = x._end;
			x._end->prev = x._end;
		}
	}

	void splice (iterator position, list & x, iterator i)
	{
		if (!x.empty())
		{
			i.getPtr()->next->prev = i.getPtr()->prev;
			i.getPtr()->prev->next = i.getPtr()->next;
			i.getPtr()->prev = position.getPtr()->prev;
			i.getPtr()->next = position.getPtr();
			position.getPtr()->prev->next = i.getPtr();
			position.getPtr()->prev = i.getPtr();
		}
	}

	void splice (iterator position, list & x, iterator first, iterator last)
	{
		if (!x.empty() && first != last)
		{
			last.getPtr()->prev->next = position.getPtr();
			first.getPtr()->prev->next = last.getPtr();
			position.getPtr()->prev->next = first.getPtr();
			node *	a = first.getPtr()->prev;
			node *	b = position.getPtr()->prev;
			node *	c = last.getPtr()->prev;
			last.getPtr()->prev = a;
			first.getPtr()->prev = b;
			position.getPtr()->prev = c;
		}
	}

	//////////////////////////////
	// Removal operations
	//////////////////////////////

	void remove (const value_type & val)
	{
		for (iterator it = this->begin(), next = ++this->begin() ; it != this->end() ; it = next++)
		{
			if (*it == val)
				this->erase(it);
		}
	}

	template <class Predicate>
	void remove_if (Predicate pred)
	{
		for (iterator it = this->begin(), next = ++this->begin() ; it != this->end() ; it = next++)
		{
			if (pred(*it))
				this->erase(it);
		}
	}

	//////////////////////////////
	// Uniquify operations
	//////////////////////////////

	void unique (void)
	{
		for (iterator it = ++this->begin() ; it != this->end() ; it++)
		{
			if (*it == *iterator(it.getPtr()->prev))
			{
				this->erase(it);
				it = this->begin();
			}
		}
	}

	template <class BinaryPredicate>
	void unique (BinaryPredicate binary_pred)
	{
		for (iterator it = ++this->begin() ; it != this->end() ; it++)
		{
			if (binary_pred(it.getPtr()->prev->data, *it))
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
		if (*this == x)
			return ;
		for (iterator it = this->begin() ; it != this->end() ; )
		{
			iterator	it2 = x.begin();
			if (it2 != x.end() && *it2 < *it)
				this->splice(it, x, it2);
			else
				it++;
		}
		this->splice(this->end(), x, x.begin(), x.end());
	}

	template <class Compare>
	void merge (list & x, Compare comp)
	{
		if (*this == x)
			return ;
		for (iterator it = this->begin() ; it != this->end() ; )
		{
			iterator	it2 = x.begin();
			if (it2 != x.end() && comp(*it2, *it))
				this->splice(it, x, it2);
			else
				it++;
		}
		this->splice(this->end(), x, x.begin(), x.end());
	}

	//////////////////////////////
	// Sorting operations
	//////////////////////////////

	void sort (void)
	{
		this->_quicksort(this->begin(), this->end());
	}

	template <class Compare>
	void sort (Compare comp)
	{
		this->_quicksort(comp, this->begin(), this->end());
	}

	void reverse (void)
	{
		for (iterator it = this->begin() ; it != this->end() ; it--)
			ft::swap(it.getPtr()->prev, it.getPtr()->next);
		ft::swap(_end->prev, _end->next);
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
		_end = _alloc.allocate(1);
		this->_construct(_end, _end, _end);
	}

	void _construct (node * ptr, node * prev, node * next, value_type data = value_type())
	{
		node	tmp;
		tmp.data = data;
		tmp.prev = prev;
		tmp.next = next;
		_alloc.construct(ptr, tmp);
	}

	void _swap_nodes (iterator & first, iterator & second)
	{
		node *	first_prev = first.getPtr()->prev;
		node *	first_next = first.getPtr()->next;
		node *	second_prev = second.getPtr()->prev;
		node *	second_next = second.getPtr()->next;
		ft::swap(first_prev->next, second_prev->next);
		ft::swap(first_next->prev, second_next->prev);
		ft::swap(first.getPtr()->prev, second.getPtr()->prev);
		ft::swap(first.getPtr()->next, second.getPtr()->next);
		ft::swap(first, second);
	}

	//////////////////////////////
	// Quicksort
	//////////////////////////////

	void _quicksort (iterator first, iterator last)
	{
		if (first != last && iterator(first.getPtr()->next) != last)
		{
			iterator	it = this->_partition(first, last);
			this->_quicksort(first, it++);
			this->_quicksort(it, last);
		}
	}

	iterator _partition (iterator & first, iterator & last)
	{
		iterator	prev = first;
		last--;
		for (iterator it = first ; it != last ; it++)
		{
			if (*it < *last)
			{
				this->_swap_nodes(prev, it);
				if (first == it)
					first = prev;
				prev++;
			}
		}
		this->_swap_nodes(prev, last);
		if (first == last)
			first = prev;
		last++;
		return (prev);
	}

	//////////////////////////////
	// Quicksort (with compare function)
	//////////////////////////////

	template <class Compare>
	void _quicksort (Compare comp, iterator first, iterator last)
	{
		if (first != last && iterator(first.getPtr()->next) != last)
		{
			iterator	it = this->_partition(comp, first, last);
			this->_quicksort(comp, first, it++);
			this->_quicksort(comp, it, last);
		}
	}

	template <class Compare>
	iterator _partition (Compare comp, iterator & first, iterator & last)
	{
		iterator	prev = first;
		last--;
		for (iterator it = first ; it != last ; it++)
		{
			if (comp(*it, *last))
			{
				this->_swap_nodes(prev, it);
				if (first == it)
					first = prev;
				prev++;
			}
		}
		this->_swap_nodes(prev, last);
		if (first == last)
			first = prev;
		last++;
		return (prev);
	}

	//////////////////////////////
	// Member variables
	//////////////////////////////

	allocator_type		_alloc;
	node *				_end;
}; // List

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
