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
		mapIterator				(value_type * const ptr)									{ _ptr = ptr; }
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
		mapIterator &			operator++	(void)											{ _ptr = _ptr->next; return (*this); }
		mapIterator &			operator--	(void)											{ _ptr = _ptr->prev; return (*this); }
		mapIterator				operator++	(int)											{ mapIterator<IsConst> x(*this); _ptr = _ptr->next; return (x); }
		mapIterator				operator--	(int)											{ mapIterator<IsConst> x(*this); _ptr = _ptr->prev; return (x); }
		// Dereference
		value_type &			operator*	(void)											{ return (_ptr->data); }
		value_type *			operator->	(void)											{ return (&_ptr->data); }
		// Member functions
		node_type *				getPtr		(void) const									{ return (_ptr); }

	private:
		void					successor	(void)											{ if (this->rrule() == false) { this->urule(); } }
		bool					rrule		(void)											{ if (_ptr->right != this->nil()) { _ptr = _ptr->right; this->leftmost(); } return (false); }
		void					urule		(void)											{ }
		void					leftmost	(void)											{  }
		node_type *				nil			(void)											{  }
		node_type *				_ptr;
	};

	//////////////////////////////
	// Member types
	//////////////////////////////

	typedef		Key												key_type;
	typedef		T												mapped_type;
	typedef		ft::pair<const key_type, mapped_type>			value_type;
	typedef		typename Alloc::template rebind<node>::other	allocator_type;
	typedef		Compare											key_compare;
	// typedef		???												value_compare;
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
	// Constructors
	//////////////////////////////

	explicit map (const key_compare & comp = key_compare(), const allocator_type & alloc = allocator_type())
	{
		_alloc = alloc;
		this->_new_nil_node();
	}

	template <class InputIterator>
	map (InputIterator first, InputIterator last, const key_compare & comp = key_compare(), const allocator_type & alloc = allocator_type())
	{
		_alloc = alloc;
		this->_new_nil_node();
	}

	map (const map & x)
	{
		_alloc = alloc;
		this->_new_nil_node();
	}

	//////////////////////////////
	// Destructors
	//////////////////////////////

	~map (void)
	{

	}

	//////////////////////////////
	// Assignment operator
	//////////////////////////////

	map & operator= (const map & x)
	{

	}

	//////////////////////////////
	// Iterators
	//////////////////////////////

	iterator begin (void)
	{
		return (iterator(this->_leftmost(_nil->right));
	}

	const_iterator begin (void) const
	{
		return (const_iterator(this->_leftmost(_nil->right));
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

	// //////////////////////////////
	// // Capacity
	// //////////////////////////////
	//
	// bool empty (void) const
	// {
	//
	// }
	//
	// size_type size (void) const
	// {
	//
	// }
	//
	// size_type max_size (void) const
	// {
	//
	// }

	//////////////////////////////
	// Member access
	//////////////////////////////

	mapped_type & operator[] (const key_type & k)
	{
		if (this->count(k))
			return (this->_find_node(_nil->right, k)->val());
		else
			return (this->_new_node(k)->val());
	}

	// //////////////////////////////
	// // Insertion modifiers
	// //////////////////////////////
	//
	// ft::pair<iterator,bool> insert (const value_type & val)
	// {
	//
	// }
	//
	// iterator insert (iterator position, const value_type & val)
	// {
	//
	// }
	//
	// template <class InputIterator>
	// void insert (InputIterator first, InputIterator last)
	// {
	//
	// }
	//
	// //////////////////////////////
	// // Erasure modifiers
	// //////////////////////////////
	//
	// void erase (iterator position)
	// {
	//
	// }
	//
	// size_type erase (const key_type & k)
	// {
	//
	// }
	//
	// void erase (iterator first, iterator last)
	// {
	//
	// }
	//
	// //////////////////////////////
	// // Common modifiers
	// //////////////////////////////
	//
	// void swap (map & x)
	// {
	//
	// }
	//
	// void clear (void)
	// {
	//
	// }
	//
	// //////////////////////////////
	// // Observers
	// //////////////////////////////
	//
	// key_compare key_comp (void) const
	// {
	//
	// }
	//
	// value_compare value_comp (void) const
	// {
	//
	// }

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

	node * _new_node (const key_type & key, const mapped_type & mapped = mapped_type())
	{
		node * new_node = _alloc.allocate(1);
		this->construct(new_node, key, mapped);

		node * parent = this->_find_parent(_nil, key);
		if (parent == _nil || parent->key() > key)
			parent->right = new_node;
		else
			parent->left = new_node;
		new_node->parent = parent;

		return (new_node);
	}

	void _construct (node * ptr, const key_type & key = key_type(), const mapped_type & mapped = mapped_type())
	{
		node	tmp;
		tmp.data = ft::make_pair(key, mapped);
		tmp.left = _nil;
		tmp.right = _nil;
		tmp.parent = _nil;
		_alloc.construct(ptr, tmp);
	}

	node * _find_node (node * current, const key_type & k)
	{
		if (current == _nil || current->key() == k)
			return (current);
		else if (current->key() < k)
			return (this->_find_node(current->left, k));
		else
			return (this->_find_node(current->right, k));
	}

	node * _find_parent (node * current, const key_type & k)
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

	//////////////////////////////
	// Member variables
	//////////////////////////////

	allocator_type		_alloc;
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
