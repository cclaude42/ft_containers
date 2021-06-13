#ifndef QUEUE_HPP
# define QUEUE_HPP

# include "deque.hpp"

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
		_ctnr = ctnr;
	}

	size_type size (void) const
	{
		return (_ctnr.size());
	}

	bool empty (void) const
	{
		return (_ctnr.empty());
	}

	value_type & front (void)
	{
		return (_ctnr.front());
	}

	const value_type & front (void) const
	{
		return (_ctnr.front());
	}

	value_type & back (void)
	{
		return (_ctnr.back());
	}

	const value_type & back (void) const
	{
		return (_ctnr.back());
	}

	void push (const value_type & val)
	{
		_ctnr.push_back(val);
	}

	void pop (void)
	{
		_ctnr.pop_front();
	}

	//////////////////////////////
	// Member variables
	//////////////////////////////

private:
	container_type		_ctnr;

	//////////////////////////////
	// Relational operators
	//////////////////////////////

	friend bool operator== (const queue & lhs, const queue & rhs)
	{
		return (lhs._ctnr == rhs._ctnr);
	}

	friend bool operator<  (const queue & lhs, const queue & rhs)
	{
		return (lhs._ctnr < rhs._ctnr);
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
