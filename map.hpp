#ifndef MAP_HPP
# define MAP_HPP

# include "includes/containers.hpp"

namespace ft
{

template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator< ft::pair<const Key, T> > >
class map {
public:

	//////////////////////////////
	// Node
	//////////////////////////////

	typedef struct				s_node
	{
		ft::pair<const Key, T>	data;
		struct s_node *			left;
		struct s_node *			right;
		struct s_node *			parent;
		// bool					color;

		s_node (ft::pair<const Key, T> data) : data(data) {}
		const Key &	key (void)	{ return (data.first); }
		T &			val (void)	{ return (data.second); }
	}							node;

	//////////////////////////////
	// Iterator subclass
	//////////////////////////////

	template <bool IsConst>
	class mapIterator {
	public:
		// Member types
		typedef					ft::pair<const Key, T>										pair_type;
		typedef typename		ft::conditional<IsConst, const pair_type, pair_type>::type	value_type;
		typedef typename		ft::conditional<IsConst, const node, node>::type			node_type;
		typedef					std::ptrdiff_t												difference_type;
		typedef					std::size_t													size_type;
		// -structors
		mapIterator				(void)														{ _ptr = NULL; }
		mapIterator				(node_type * const ptr)										{ _ptr = ptr; }
		~mapIterator			(void)														{}
		// Const stuff
		template <bool B>		mapIterator
			(const mapIterator<B> & x, typename ft::enable_if<!B>::type* = 0)				{ _ptr = x.getPtr(); }

		// Assignment
		mapIterator &			operator=	(const mapIterator & x)							{ _ptr = x.getPtr(); return (*this); }
		// Comparison
		template <bool B> bool	operator==	(const mapIterator<B> & x) const				{ return (_ptr == x.getPtr()); }
		template <bool B> bool	operator!=	(const mapIterator<B> & x) const				{ return (_ptr != x.getPtr()); }
		// -crementation
		mapIterator &			operator++	(void)											{ this->nextNode(); return (*this); }
		mapIterator &			operator--	(void)											{ this->prevNode(); return (*this); }
		mapIterator				operator++	(int)											{ mapIterator<IsConst> x(*this); this->nextNode(); return (x); }
		mapIterator				operator--	(int)											{ mapIterator<IsConst> x(*this); this->prevNode(); return (x); }
		// Dereference
		value_type &			operator*	(void)											{ return (_ptr->data); }
		value_type *			operator->	(void)											{ return (&_ptr->data); }
		// Member functions
		node_type *				getPtr		(void) const									{ return (_ptr); }

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
			if (_ptr->left != _ptr->left->left)
			{
				_ptr = _ptr->left;
				while (_ptr->right == _ptr->right->left)
					_ptr = _ptr->right;
			}
			else
			{
				while (_ptr == _ptr->parent->left && _ptr != _ptr->parent)
					_ptr = _ptr->parent;
				_ptr = _ptr->parent;
			}
		}
	};

	//////////////////////////////
	// Member types
	//////////////////////////////

	class		ValueCompare;

	typedef		Key												key_type;
	typedef		T												mapped_type;
	typedef		ft::pair<const key_type, mapped_type>			value_type;
	typedef		typename Alloc::template rebind<node>::other	allocator_type;
	typedef		Compare											key_compare;
	typedef		ValueCompare									value_compare;
	typedef		typename allocator_type::reference				reference;
	typedef		typename allocator_type::const_reference		const_reference;
	typedef		typename allocator_type::pointer				pointer;
	typedef		typename allocator_type::const_pointer			const_pointer;
	typedef		mapIterator<false>								iterator;
	typedef		mapIterator<true>								const_iterator;
	typedef		ft::reverse_iterator<iterator>					reverse_iterator;
	typedef		ft::reverse_iterator<const_iterator>			const_reverse_iterator;
	typedef		typename mapIterator<false>::difference_type	difference_type;
	typedef		typename mapIterator<false>::size_type			size_type;

	//////////////////////////////
	// Value compare
	//////////////////////////////

	class ValueCompare {
	public:
		friend			class			map;
		typedef			bool			result_type;
		typedef			value_type		first_argument_type;
		typedef			value_type		second_argument_type;
		bool			operator()		(const value_type & x, const value_type & y) const
			{ return (comp(x.first, y.first)); }
	protected:
		ValueCompare	(Compare c)		: comp(c) {}
		Compare			comp;
	};

	//////////////////////////////
	// Constructors
	//////////////////////////////

	explicit map (const key_compare & comp = key_compare(), const allocator_type & alloc = allocator_type())
	{
		_alloc = alloc;
		_comp = comp;
		this->_new_nil_node();
	}

	template <class InputIterator>
	map (InputIterator first, InputIterator last, const key_compare & comp = key_compare(), const allocator_type & alloc = allocator_type())
	{
		_alloc = alloc;
		_comp = comp;
		this->_new_nil_node();

		while (first != last)
			this->insert(*first++);
	}

	map (const map & x)
	{
		this->_new_nil_node();
		*this = x;
	}

	//////////////////////////////
	// Destructors
	//////////////////////////////

	~map (void)
	{
		this->clear();
		_alloc.destroy(_nil);
		_alloc.deallocate(_nil, 1);
	}

	//////////////////////////////
	// Assignment operator
	//////////////////////////////

	map & operator= (const map & x)
	{
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
	// Member access
	//////////////////////////////

	mapped_type & operator[] (const key_type & k)
	{
		this->insert(ft::make_pair(k, mapped_type()));
		return (this->find(k)->second);
	}

	//////////////////////////////
	// Insertion modifiers
	//////////////////////////////

	ft::pair<iterator,bool> insert (const value_type & val)
	{
		iterator it;
		if (this->count(val.first))
		{
			it = this->find(val.first);
			return (ft::make_pair(it, false));
		}
		else
		{
			it = iterator(this->_new_node(val));
			return (ft::make_pair(it, true));
		}
	}

	iterator insert (iterator position, const value_type & val)
	{
		return (this->insert(val));
	}

	template <class InputIterator>
	void insert (InputIterator first, InputIterator last)
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
		}
		else if (ptr->left != _nil || ptr->right != _nil)
		{
			if (ptr->left != _nil)
				ptr->left->parent = ptr->parent;
			else
				ptr->right->parent = ptr->parent;
			if (ptr->parent->left == ptr)
				ptr->parent->left = (ptr->left == _nil) ? ptr->right : ptr->left;
			else
				ptr->parent->right = (ptr->left == _nil) ? ptr->right : ptr->left;
		}
		else
		{
			if (ptr->parent->left == ptr)
				ptr->parent->left = _nil;
			else
				ptr->parent->right = _nil;
		}

		_alloc.destroy(ptr);
		_alloc.deallocate(ptr, 1);
	}

	size_type erase (const key_type & k)
	{
		if (this->count(k))
		{
			this->erase(this->find(k));
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

	void swap (map & x)
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
		return (value_compare(_comp));
	}

	//////////////////////////////
	// Search operations
	//////////////////////////////

	iterator find (const key_type & k)
	{
		return (iterator(this->_find_node(_nil->right, k)));
	}

	const_iterator find (const key_type & k) const
	{
		return (const_iterator(this->_find_node(_nil->right, k)));
	}

	size_type count (const key_type & k) const
	{
		if (this->_find_node(_nil->right, k) != _nil)
			return (1);
		else
			return (0);
	}

	// //////////////////////////////
	// // Bound operations
	// //////////////////////////////
	//
	// iterator lower_bound (const key_type & k)
	// {
	//
	// }
	//
	// const_iterator lower_bound (const key_type & k) const
	// {
	//
	// }
	//
	// iterator upper_bound (const key_type & k)
	// {
	//
	// }
	//
	// const_iterator upper_bound (const key_type & k) const
	// {
	//
	// }
	//
	// //////////////////////////////
	// // Range operations
	// //////////////////////////////
	//
	// ft::pair<iterator,iterator> equal_range (const key_type & k)
	// {
	//
	// }
	//
	// ft::pair<const_iterator,const_iterator> equal_range (const key_type & k) const
	// {
	//
	// }

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
	}

	node * _new_node (const value_type & val = value_type())
	{
		node * new_node = _alloc.allocate(1);
		this->_construct(new_node, val);

		node * parent = this->_find_parent(_nil->right, val.first);
		if (parent == _nil || parent->key() < val.first)
			parent->right = new_node;
		else
			parent->left = new_node;
		new_node->parent = parent;

		return (new_node);
	}

	void _construct (node * ptr, const value_type & val = value_type())
	{
		node tmp(val);
		tmp.left = _nil;
		tmp.right = _nil;
		tmp.parent = _nil;
		_alloc.construct(ptr, tmp);
	}

	void _swap_nodes (node * a, node * b)
	{
		node * a_parent = a->parent;
		node * a_left = a->left;
		node * a_right = a->right;
		node * b_parent = b->parent;
		node * b_left = b->left;
		node * b_right = b->right;

		a_parent->left == a ? a_parent->left = b : a_parent->right = b;
		b_parent->left == b ? b_parent->left = a : b_parent->right = a;
		ft::swap(a_left->parent, b_left->parent);
		ft::swap(a_right->parent, b_right->parent);
		ft::swap(a->parent, b->parent);
		ft::swap(a->left, b->left);
		ft::swap(a->right, b->right);
	}

	node * _find_node (node * current, const key_type & k) const
	{
		if (current == _nil || current->key() == k)
			return (current);
		else if (k < current->key())
			return (this->_find_node(current->left, k));
		else
			return (this->_find_node(current->right, k));
	}

	node * _find_parent (node * current, const key_type & k) const
	{
		if (current->key() < k)
		{
			if (current->right == _nil || current->right->key() == k)
				return (current);
			else
				return (this->_find_parent(current->right, k));
		}
		else
		{
			if (current->left == _nil || current->left->key() == k)
				return (current);
			else
				return (this->_find_parent(current->left, k));
		}
	}

	node * _leftmost (node * root)
	{
		node * leftmost = root;
		while (leftmost->left != leftmost->left->left)
			leftmost = leftmost->left;
		return (leftmost);
	}

	void _treecheck (void)
	{
		std::cout << "The tree is as follows :" << std::endl;
		for (iterator it = this->begin() ; it != this->end() ; it++)
		{
			std::cout << it->first << " is the child of " << it.getPtr()->parent->key() << ", points left to " << it.getPtr()->left->key() << " and right to " << it.getPtr()->right->key() << std::endl;
		}
		std::cout << "End of tree check" << std::endl;
	}

	//////////////////////////////
	// Member variables
	//////////////////////////////

	allocator_type		_alloc;
	key_compare			_comp;
	node *				_nil;
};

	//////////////////////////////
	// Relational operators
	//////////////////////////////

	template <class Key, class T, class Compare, class Alloc>
	bool operator== (const map<Key,T,Compare,Alloc> & lhs, const map<Key,T,Compare,Alloc> & rhs)
	{
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<  (const map<Key,T,Compare,Alloc> & lhs, const map<Key,T,Compare,Alloc> & rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator!= (const map<Key,T,Compare,Alloc> & lhs, const map<Key,T,Compare,Alloc> & rhs)
	{
		return (!(lhs == rhs));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<= (const map<Key,T,Compare,Alloc> & lhs, const map<Key,T,Compare,Alloc> & rhs)
	{
		return (!(rhs < lhs));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>  (const map<Key,T,Compare,Alloc> & lhs, const map<Key,T,Compare,Alloc> & rhs)
	{
		return (rhs < lhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>= (const map<Key,T,Compare,Alloc> & lhs, const map<Key,T,Compare,Alloc> & rhs)
	{
		return (!(lhs < rhs));
	}

	template <class Key, class T, class Compare, class Alloc>
	void swap (map<Key,T,Compare,Alloc> & x, map<Key,T,Compare,Alloc> & y)
	{
		x.swap(y);
	}

} // Namespace ft

#endif
