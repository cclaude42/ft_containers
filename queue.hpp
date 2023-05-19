#ifndef QUEUE_HPP
# define QUEUE_HPP

# include "deque.hpp"
# include "priority_queue.hpp"

namespace ft
{

template <class T, class Container = deque<T> >
class queue {
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

	explicit queue (const container_type & ctnr = container_type())
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

	value_type & front (void)
	{
		return (c.front());
	}

	const value_type & front (void) const
	{
		return (c.front());
	}

	value_type & back (void)
	{
		return (c.back());
	}

	const value_type & back (void) const
	{
		return (c.back());
	}

	void push (const value_type & val)
	{
		c.push_back(val);
	}

	void pop (void)
	{
		c.pop_front();
	}

	//////////////////////////////
	// Member variables
	//////////////////////////////

protected:
	container_type		c;

	//////////////////////////////
	// Relational operators
	//////////////////////////////

	friend bool operator== (const queue & lhs, const queue & rhs)
	{
		return (lhs.c == rhs.c);
	}

	friend bool operator<  (const queue & lhs, const queue & rhs)
	{
		return (lhs.c < rhs.c);
	}
}; // Queue

	template <class T, class Container>
	bool operator!= (const queue<T,Container> & lhs, const queue<T,Container> & rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T, class Container>
	bool operator<= (const queue<T,Container> & lhs, const queue<T,Container> & rhs)
	{
		return (!(rhs < lhs));
	}

	template <class T, class Container>
	bool operator>  (const queue<T,Container> & lhs, const queue<T,Container> & rhs)
	{
		return (rhs < lhs);
	}

	template <class T, class Container>
	bool operator>= (const queue<T,Container> & lhs, const queue<T,Container> & rhs)
	{
		return (!(lhs < rhs));
	}

} // Namespace ft

#endif
