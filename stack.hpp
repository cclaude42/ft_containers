#ifndef STACK_HPP
# define STACK_HPP

# include "deque.hpp"

namespace ft
{

template <class T, class Container = deque<T> >
class stack {
public:

	//////////////////////////////
	// Member types
	//////////////////////////////

	typedef		T				value_type;
	typedef		Container		container_type;
	typedef		size_t			size_type;

	//////////////////////////////
	// Member functions
	//////////////////////////////

	explicit stack (const container_type & ctnr = container_type())
	{
		c = ctnr;
	}

	size_type size (void) const
	{
		return (c.size());
	}

	bool empty (void) const
	{
		return (c.empty());
	}

	value_type & top (void)
	{
		return (c.back());
	}

	const value_type & top (void) const
	{
		return (c.back());
	}

	void push (const value_type & val)
	{
		c.push_back(val);
	}

	void pop (void)
	{
		c.pop_back();
	}

	//////////////////////////////
	// Member variables
	//////////////////////////////

protected:
	container_type		c;

	//////////////////////////////
	// Relational operators
	//////////////////////////////

	friend bool operator== (const stack & lhs, const stack & rhs)
	{
		return (lhs.c == rhs.c);
	}

	friend bool operator<  (const stack & lhs, const stack & rhs)
	{
		return (lhs.c < rhs.c);
	}
}; // Stack

	template <class T, class Container>
	bool operator!= (const stack<T,Container> & lhs, const stack<T,Container> & rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T, class Container>
	bool operator<= (const stack<T,Container> & lhs, const stack<T,Container> & rhs)
	{
		return (!(rhs < lhs));
	}

	template <class T, class Container>
	bool operator>  (const stack<T,Container> & lhs, const stack<T,Container> & rhs)
	{
		return (rhs < lhs);
	}

	template <class T, class Container>
	bool operator>= (const stack<T,Container> & lhs, const stack<T,Container> & rhs)
	{
		return (!(lhs < rhs));
	}

} // Namespace ft

#endif
