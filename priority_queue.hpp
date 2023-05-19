#ifndef PRIORITY_QUEUE_HPP
# define PRIORITY_QUEUE_HPP

# include "vector.hpp"

namespace ft
{

template <class T, class Container = ft::vector<T>, class Compare = ft::less<typename Container::value_type> >
class priority_queue {
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

	explicit priority_queue (const Compare & comp = Compare(), const Container& ctnr = Container())
	{
		this->comp = comp;
		this->c = ctnr;
	}

	template <class InputIterator>
	priority_queue (InputIterator first, InputIterator last, const Compare & comp = Compare(), const Container & ctnr = Container())
	{
		this->comp = comp;
		this->c = ctnr;
		this->c.assign(first, last);
	}

	size_type size (void) const
	{
		return (c.size());
	}

	bool empty (void) const
	{
		return (c.empty());
	}

	const value_type & top (void) const
	{
		return (c.front());
	}

	void push (const value_type & val)
	{
		c.push_back(val);
	}

	void pop (void)
	{
		c.erase(c.begin());
	}

	//////////////////////////////
	// Member variables
	//////////////////////////////

protected:
	container_type		c;
	Compare				comp;

	//////////////////////////////
	// Relational operators
	//////////////////////////////

	friend bool operator== (const priority_queue & lhs, const priority_queue & rhs)
	{
		return (lhs.c == rhs.c);
	}

	friend bool operator<  (const priority_queue & lhs, const priority_queue & rhs)
	{
		return (lhs.c < rhs.c);
	}
}; // Priority Queue

	template <class T, class Container, class Compare>
	bool operator!= (const priority_queue<T,Container,Compare> & lhs, const priority_queue<T,Container,Compare> & rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T, class Container, class Compare>
	bool operator<= (const priority_queue<T,Container,Compare> & lhs, const priority_queue<T,Container,Compare> & rhs)
	{
		return (!(rhs < lhs));
	}

	template <class T, class Container, class Compare>
	bool operator>  (const priority_queue<T,Container,Compare> & lhs, const priority_queue<T,Container,Compare> & rhs)
	{
		return (rhs < lhs);
	}

	template <class T, class Container, class Compare>
	bool operator>= (const priority_queue<T,Container,Compare> & lhs, const priority_queue<T,Container,Compare> & rhs)
	{
		return (!(lhs < rhs));
	}

} // Namespace ft

#endif
