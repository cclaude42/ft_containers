#ifndef MULTISET_HPP
# define MULTISET_HPP

# include "includes/containers.hpp"

namespace ft
{

template <class T, class Compare = std::less<T>, class Alloc = std::allocator<T> >
class multiset {
public:

	//////////////////////////////
	// Node
	//////////////////////////////

	typedef struct				s_node
	{
# if __APPLE__
		const T					data;
		bool					color;
		struct s_node *			left;
		struct s_node *			right;
		struct s_node *			parent;
# else
		const T					data;
		struct s_node *			left;
		struct s_node *			right;
		struct s_node *			parent;
		bool					color;
# endif

		s_node (const T data) : data(data) {}
	}							node;

	//////////////////////////////
	// Iterator subclass
	//////////////////////////////

	template <bool IsConst>
	class multisetIterator {
	public:
		// Member types
		typedef					const T													value_type;
		typedef					node													node_type;
		typedef					std::ptrdiff_t											difference_type;
		typedef					std::size_t												size_type;
		typedef typename		Alloc::reference										reference;
		typedef typename		Alloc::pointer											pointer;
		typedef					std::random_access_iterator_tag							iterator_category;
		// -structors
		multisetIterator		(void)													{ _ptr = NULL; }
		multisetIterator		(node_type * const ptr)									{ _ptr = ptr; }
		~multisetIterator		(void)													{}
		// Const stuff
		template <bool B>		multisetIterator
			(const multisetIterator<B> & x)												{ _ptr = x.getPtr(); }

		// Assignment
		multisetIterator &		operator=	(const multisetIterator & x)				{ _ptr = x.getPtr(); return (*this); }
		// Comparison
		template <bool B> bool	operator==	(const multisetIterator<B> & x) const		{ return (_ptr == x.getPtr()); }
		template <bool B> bool	operator!=	(const multisetIterator<B> & x) const		{ return (_ptr != x.getPtr()); }
		// -crementation
		multisetIterator &		operator++	(void)										{ this->nextNode(); return (*this); }
		multisetIterator &		operator--	(void)										{ this->prevNode(); return (*this); }
		multisetIterator		operator++	(int)										{ multisetIterator<IsConst> x(*this); this->nextNode(); return (x); }
		multisetIterator		operator--	(int)										{ multisetIterator<IsConst> x(*this); this->prevNode(); return (x); }
		// Dereference
		value_type &			operator*	(void) const								{ return (_ptr->data); }
		value_type *			operator->	(void) const								{ return (&_ptr->data); }
		// Member functions
		node_type *				getPtr		(void) const								{ return (_ptr); }

	private:
		node_type *				_ptr;

		void nextNode (void)
		{
			if (_ptr->right != _ptr->right->left)
			{
				_ptr = _ptr->right;
				while (_ptr->left != _ptr->left->left)
					_ptr = _ptr->left;
			}
			else
			{
				while (_ptr == _ptr->parent->right && _ptr != _ptr->parent)
					_ptr = _ptr->parent;
				_ptr = _ptr->parent;
			}
		}

		void prevNode (void)
		{
			if (_ptr == _ptr->parent)
			{
				while (_ptr->right != _ptr->right->left)
					_ptr = _ptr->right;
			}
			else if (_ptr->left != _ptr->left->left)
			{
				_ptr = _ptr->left;
				while (_ptr->right != _ptr->right->left)
					_ptr = _ptr->right;
			}
			else
			{
				while (_ptr == _ptr->parent->left && _ptr != _ptr->parent)
					_ptr = _ptr->parent;
				_ptr = _ptr->parent;
			}
		}
	}; // Iterator

	//////////////////////////////
	// Member types
	//////////////////////////////

	typedef		T													key_type;
	typedef		T													value_type;
	typedef		Compare												key_compare;
	typedef		Compare												value_compare;
	typedef		typename Alloc::template rebind<node>::other		allocator_type;
	typedef		typename Alloc::reference							reference;
	typedef		typename Alloc::const_reference						const_reference;
	typedef		typename Alloc::pointer								pointer;
	typedef		typename Alloc::const_pointer						const_pointer;
	typedef		multisetIterator<false>								iterator;
	typedef		multisetIterator<true>								const_iterator;
	typedef		ft::reverse_iterator<iterator>						reverse_iterator;
	typedef		ft::reverse_iterator<const_iterator>				const_reverse_iterator;
	typedef		typename multisetIterator<false>::difference_type	difference_type;
	typedef		typename multisetIterator<false>::size_type			size_type;

	//////////////////////////////
	// Constructors
	//////////////////////////////

	explicit multiset (const key_compare & comp = key_compare(), const allocator_type & alloc = allocator_type())
	{
		_alloc = alloc;
		_comp = comp;
		this->_new_nil_node();
	}

	template <class InputIterator>
	multiset (InputIterator first, InputIterator last, const key_compare & comp = key_compare(), const allocator_type & alloc = allocator_type(),
	typename ft::enable_if<!ft::is_same<InputIterator, int>::value>::type* = 0)
	{
		_alloc = alloc;
		_comp = comp;
		this->_new_nil_node();

		while (first != last)
			this->insert(*first++);
	}

	multiset (const multiset & x)
	{
		this->_new_nil_node();
		*this = x;
	}

	//////////////////////////////
	// Destructors
	//////////////////////////////

	~multiset (void)
	{
		this->clear();
		_alloc.destroy(_nil);
		_alloc.deallocate(_nil, 1);
	}

	//////////////////////////////
	// Assignment operator
	//////////////////////////////

	multiset & operator= (const multiset & x)
	{
		if (this == &x)
			return (*this);

		this->clear();
		_alloc = x._alloc;
		_comp = x._comp;

		for (const_iterator it = x.begin() ; it != x.end() ; it++)
			this->insert(*it);
		return (*this);
	}

	//////////////////////////////
	// Iterators
	//////////////////////////////

	iterator begin (void)
	{
		return (iterator(this->_leftmost(_nil->right)));
	}

	const_iterator begin (void) const
	{
		return (const_iterator(this->_leftmost(_nil->right)));
	}

	iterator end (void)
	{
		return (iterator(_nil));
	}

	const_iterator end (void) const
	{
		return (const_iterator(_nil));
	}

	//////////////////////////////
	// Reverse iterators
	//////////////////////////////

	reverse_iterator rbegin (void)
	{
		return (reverse_iterator(_nil));
	}

	const_reverse_iterator rbegin (void) const
	{
		return (const_reverse_iterator(_nil));
	}

	reverse_iterator rend (void)
	{
		return (reverse_iterator(this->_leftmost(_nil->right)));
	}

	const_reverse_iterator rend (void) const
	{
		return (const_reverse_iterator(this->_leftmost(_nil->right)));
	}

	//////////////////////////////
	// Capacity
	//////////////////////////////

	bool empty (void) const
	{
		return (_nil == _nil->right);
	}

	size_type size (void) const
	{
		size_type n = 0;
		for (const_iterator it = this->begin() ; it != this->end() ; it++)
			n++;
		return (n);
	}

	size_type max_size (void) const
	{
		return (_alloc.max_size());
	}

	//////////////////////////////
	// Insertion modifiers
	//////////////////////////////

	iterator insert (const value_type & val)
	{
		return (iterator(this->_new_node(val)));
	}

	iterator insert (iterator position, const value_type & val)
	{
		(void)position;
		return (this->insert(val));
	}

	template <class InputIterator>
	void insert (InputIterator first, InputIterator last,
	typename ft::enable_if<!ft::is_same<InputIterator, int>::value>::type* = 0)
	{
		while (first != last)
			this->insert(*first++);
	}

	//////////////////////////////
	// Erasure modifiers
	//////////////////////////////

	void erase (iterator position)
	{
		node * ptr = position.getPtr();

		if (ptr->left != _nil && ptr->right != _nil)
		{
			position--;
			this->_swap_nodes(ptr, position.getPtr());
			this->erase(ptr);
		}
		else
		{
			node * child = (ptr->left != _nil) ? ptr->left : ptr->right;

			if (child != _nil)
				child->parent = ptr->parent;
			if (ptr->parent->left == ptr)
				ptr->parent->left = child;
			else
				ptr->parent->right = child;

			this->_removeNode(ptr, child);
		}
	}

	size_type erase (const value_type & val)
	{
		if (this->count(val))
		{
			this->erase(this->find(val));
			return (1);
		}
		return (0);
	}

	void erase (iterator first, iterator last)
	{
		for (iterator it = first++ ; it != last ; it = first++)
			this->erase(it);
	}

	//////////////////////////////
	// Common modifiers
	//////////////////////////////

	void swap (multiset & x)
	{
		ft::swap(_alloc, x._alloc);
		ft::swap(_comp, x._comp);
		ft::swap(_nil, x._nil);
	}

	void clear (void)
	{
		iterator first = this->begin();
		for (iterator it = first++ ; it != this->end() ; it = first++)
			this->erase(it);
	}

	//////////////////////////////
	// Observers
	//////////////////////////////

	key_compare key_comp (void) const
	{
		return (key_compare());
	}

	value_compare value_comp (void) const
	{
		return (key_compare());
	}

	//////////////////////////////
	// Search operations
	//////////////////////////////

	iterator find (const value_type & val)
	{
		if (this->count(val))
			return (iterator(this->_find_node(_nil->right, val)));
		else
			return (this->end());
	}

	const_iterator find (const value_type & val) const
	{
		if (this->count(val))
			return (iterator(this->_find_node(_nil->right, val)));
		else
			return (this->end());
	}

	size_type count (const value_type & val) const
	{
		size_type n = 0;
		for (const_iterator it = this->begin() ; it != this->end() ; it++)
		{
			if (this->_equal(val, *it))
				n++;
		}
		return (n);
	}

	//////////////////////////////
	// Range operations
	//////////////////////////////

	iterator lower_bound (const value_type & val)
	{
		iterator it = this->begin();
		while (this->_comp(*it, val) && it != this->end())
			it++;
		return (it);
	}

	const_iterator lower_bound (const value_type & val) const
	{
		const_iterator it = this->begin();
		while (this->_comp(*it, val) && it != this->end())
			it++;
		return (it);
	}

	iterator upper_bound (const value_type & val)
	{
		iterator it = this->begin();
		while (this->_comp(val, *it) == false && it != this->end())
			it++;
		return (it);
	}

	const_iterator upper_bound (const value_type & val) const
	{
		const_iterator it = this->begin();
		while (this->_comp(val, *it) == false && it != this->end())
			it++;
		return (it);
	}

	ft::pair<iterator,iterator> equal_range (const value_type & val)
	{
		return (ft::make_pair(this->lower_bound(val), this->upper_bound(val)));
	}

	ft::pair<const_iterator,const_iterator> equal_range (const value_type & val) const
	{
		return (ft::make_pair(this->lower_bound(val), this->upper_bound(val)));
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
	void _new_nil_node (void)
	{
		_nil = _alloc.allocate(1);
		this->_construct(_nil);
		_nil->color = BLACK_;
	}

	node * _new_node (const value_type & val = value_type())
	{
		node * new_node = _alloc.allocate(1);
		this->_construct(new_node, val);

		node * parent = this->_find_parent(_nil->right, val);
		if (parent == _nil || !this->_comp(val, parent->data))
			parent->right = new_node;
		else
			parent->left = new_node;
		new_node->parent = parent;

		this->_insertRB(new_node);

		return (new_node);
	}

	void _construct (node * ptr, const value_type & val = value_type())
	{
		node tmp(val);
		tmp.left = _nil;
		tmp.right = _nil;
		tmp.parent = _nil;
		tmp.color = RED_;
		_alloc.construct(ptr, tmp);
	}

	void _swap_nodes (node * a, node * b)
	{
		if (a->left != b && a->left != _nil)
			a->left->parent = b;
		if (a->right != b && a->right != _nil)
			a->right->parent = b;
		if (a->parent != b && a->parent != _nil)
		{
			if (a->parent->left == a)
				a->parent->left = b;
			else
				a->parent->right = b;
		}

		if (b->left != a && b->left != _nil)
			b->left->parent = a;
		if (b->right != a && b->right != _nil)
			b->right->parent = a;
		if (b->parent != a && b->parent != _nil)
		{
			if (b->parent->left == b)
				b->parent->left = a;
			else
				b->parent->right = a;
		}

		if (a->parent == b)
			a->parent = a;
		if (a->left == b)
			a->left = a;
		if (a->right == b)
			a->right = a;
		if (b->parent == a)
			b->parent = b;
		if (b->left == a)
			b->left = b;
		if (b->right == a)
			b->right = b;

		ft::swap(a->parent, b->parent);
		ft::swap(a->left, b->left);
		ft::swap(a->right, b->right);
		ft::swap(a->color, b->color);

		if (_nil->right == a)
			_nil->right = b;
		else if (_nil->right == b)
			_nil->right = a;
	}

	void _removeNode (node * ptr, node * child)
	{
		this->_deleteRB(ptr, child);

		_alloc.destroy(ptr);
		_alloc.deallocate(ptr, 1);
	}

	node * _find_node (node * current, const value_type & val) const
	{
		if (current == _nil || this->_equal(current->data, val))
			return (current);
		else if (this->_comp(val, current->data))
			return (this->_find_node(current->left, val));
		else
			return (this->_find_node(current->right, val));
	}

	node * _find_parent (node * current, const value_type & val) const
	{
		if (!this->_comp(val, current->data))
		{
			if (current->right == _nil)
				return (current);
			else
				return (this->_find_parent(current->right, val));
		}
		else
		{
			if (current->left == _nil)
				return (current);
			else
				return (this->_find_parent(current->left, val));
		}
	}

	node * _leftmost (node * root) const
	{
		while (root->left != root->left->left)
			root = root->left;
		return (root);
	}

	bool _equal (const value_type & lhs, const value_type & rhs) const
	{
		return (this->_comp(lhs, rhs) == false && this->_comp(rhs, lhs) == false);
	}

	//////////////////////////////
	// Red and Black Tree
	//////////////////////////////

	void _insertRB (node * x)
	{
		node * parent = x->parent;
		node * grandparent = parent->parent;
		node * uncle = (grandparent->right == parent) ? grandparent->left : grandparent->right;

		if (parent == _nil)
			x->color = BLACK_;
		else if (parent->color == BLACK_)
			return ;
		else if (uncle->color == RED_)
		{
			parent->color = BLACK_;
			uncle->color = BLACK_;
			grandparent->color = RED_;
			this->_insertRB(grandparent);
		}
		else if (uncle->color == BLACK_)
		{
			if (grandparent->left->left == x || grandparent->right->right == x)
			{
				if (grandparent->left->left == x)
					this->_LL(grandparent, parent);
				else if (grandparent->right->right == x)
					this->_RR(grandparent, parent);
				ft::swap(grandparent->color, parent->color);
			}
			else
			{
				if (grandparent->left->right == x)
					this->_LR(grandparent, parent, x);
				else if (grandparent->right->left == x)
					this->_RL(grandparent, parent, x);
				ft::swap(grandparent->color, x->color);
			}
		}
	}

	void _deleteRB (node * v, node * u)
	{
		if (v->color == RED_ || u->color == RED_)
			u->color = BLACK_;
		else
			this->_doubleBlack(u, v->parent);
	}

	void _doubleBlack (node * u, node * parent)
	{
		node * sibling = (parent->left != u) ? parent->left : parent->right;

		if (u == _nil->right)
			return ;
		else if (sibling->color == BLACK_ && (sibling->left->color == RED_ || sibling->right->color == RED_))
		{
			if (sibling == parent->left && sibling->left->color == RED_)
				this->_LL(parent, sibling);
			else if (sibling == parent->left && sibling->right->color == RED_)
				this->_LR(parent, sibling, sibling->right);
			else if (sibling == parent->right && sibling->right->color == RED_)
				this->_RR(parent, sibling);
			else if (sibling == parent->right && sibling->left->color == RED_)
				this->_RL(parent, sibling, sibling->left);

			if (sibling->left->color == RED_)
				sibling->left->color = BLACK_;
			else
				sibling->right->color = BLACK_;
		}
		else if (sibling->color == BLACK_)
		{
			sibling->color = RED_;
			if (parent->color == RED_)
				parent->color = BLACK_;
			else
				this->_doubleBlack(parent, parent->parent);
		}
		else if (sibling->color == RED_)
		{
			if (sibling == parent->left)
				this->_LL(parent, sibling);
			else
				this->_RR(parent, sibling);
			ft::swap(parent->color, sibling->color);
			this->_doubleBlack(u, parent);
		}
	}

	void _LL (node * grandparent, node * parent)
	{
		if (grandparent->parent->right == grandparent)
			grandparent->parent->right = parent;
		else
			grandparent->parent->left = parent;
		if (parent->right != _nil)
			parent->right->parent = grandparent;
		grandparent->left = parent->right;
		parent->parent = grandparent->parent;
		grandparent->parent = parent;
		parent->right = grandparent;
	}

	void _RR (node * grandparent, node * parent)
	{
		if (grandparent->parent->right == grandparent)
			grandparent->parent->right = parent;
		else
			grandparent->parent->left = parent;
		if (parent->left != _nil)
			parent->left->parent = grandparent;
		grandparent->right = parent->left;
		parent->parent = grandparent->parent;
		grandparent->parent = parent;
		parent->left = grandparent;
	}

	void _LR (node * grandparent, node * parent, node * x)
	{
		if (grandparent->parent->right == grandparent)
			grandparent->parent->right = x;
		else
			grandparent->parent->left = x;
		if (x->left != _nil)
			x->left->parent = parent;
		if (x->right != _nil)
			x->right->parent = grandparent;
		grandparent->left = x->right;
		parent->right = x->left;
		x->parent = grandparent->parent;
		grandparent->parent = x;
		parent->parent = x;
		x->left = parent;
		x->right = grandparent;
	}

	void _RL (node * grandparent, node * parent, node * x)
	{
		if (grandparent->parent->right == grandparent)
			grandparent->parent->right = x;
		else
			grandparent->parent->left = x;
		if (x->left != _nil)
			x->left->parent = grandparent;
		if (x->right != _nil)
			x->right->parent = parent;
		grandparent->right = x->left;
		parent->left = x->right;
		x->parent = grandparent->parent;
		grandparent->parent = x;
		parent->parent = x;
		x->left = grandparent;
		x->right = parent;
	}

	//////////////////////////////
	// Member variables
	//////////////////////////////

	allocator_type		_alloc;
	key_compare			_comp;
	node *				_nil;
}; // Multiset

	//////////////////////////////
	// Relational operators
	//////////////////////////////

	template <class T, class Compare, class Alloc>
	bool operator== (const multiset<T,Compare,Alloc> & lhs, const multiset<T,Compare,Alloc> & rhs)
	{
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class T, class Compare, class Alloc>
	bool operator<  (const multiset<T,Compare,Alloc> & lhs, const multiset<T,Compare,Alloc> & rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class T, class Compare, class Alloc>
	bool operator!= (const multiset<T,Compare,Alloc> & lhs, const multiset<T,Compare,Alloc> & rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T, class Compare, class Alloc>
	bool operator<= (const multiset<T,Compare,Alloc> & lhs, const multiset<T,Compare,Alloc> & rhs)
	{
		return (!(rhs < lhs));
	}

	template <class T, class Compare, class Alloc>
	bool operator>  (const multiset<T,Compare,Alloc> & lhs, const multiset<T,Compare,Alloc> & rhs)
	{
		return (rhs < lhs);
	}

	template <class T, class Compare, class Alloc>
	bool operator>= (const multiset<T,Compare,Alloc> & lhs, const multiset<T,Compare,Alloc> & rhs)
	{
		return (!(lhs < rhs));
	}

	template <class T, class Compare, class Alloc>
	void swap (multiset<T,Compare,Alloc> & x, multiset<T,Compare,Alloc> & y)
	{
		x.swap(y);
	}

} // Namespace ft

#endif
