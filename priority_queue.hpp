#ifndef PRIORITY_QUEUE_HPP
# define PRIORITY_QUEUE_HPP

# include "deque.hpp"

namespace ft
{

template <class T, class Container = vector<T>, class Compare = std::less<typename Container::value_type> >
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

	explicit priority_queue (const container_type & ctnr = container_type())
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

	// value_type & top (void)
	// {
	// 	return (_ctnr.back());
	// }

	// const value_type & top (void) const
	// {
	// 	return (_ctnr.back());
	// }

	// void push (const value_type & val)
	// {
	// 	_ctnr.push_back(val);
	// }

	// void pop (void)
	// {
	// 	_ctnr.pop_back();
	// }

	//////////////////////////////
	// Member variables
	//////////////////////////////

private:
	container_type		_ctnr;

	//////////////////////////////
	// Relational operators
	//////////////////////////////

	friend bool operator== (const priority_queue & lhs, const priority_queue & rhs)
	{
		return (lhs._ctnr == rhs._ctnr);
	}

	friend bool operator<  (const priority_queue & lhs, const priority_queue & rhs)
	{
		return (lhs._ctnr < rhs._ctnr);
	}
}; // Priority Queue

	template <class T, class Container>
	bool operator!= (const priority_queue<T,Container,Compare> & lhs, const priority_queue<T,Container,Compare> & rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T, class Container>
	bool operator<= (const priority_queue<T,Container,Compare> & lhs, const priority_queue<T,Container,Compare> & rhs)
	{
		return (!(rhs < lhs));
	}

	template <class T, class Container>
	bool operator>  (const priority_queue<T,Container,Compare> & lhs, const priority_queue<T,Container,Compare> & rhs)
	{
		return (rhs < lhs);
	}

	template <class T, class Container>
	bool operator>= (const priority_queue<T,Container,Compare> & lhs, const priority_queue<T,Container,Compare> & rhs)
	{
		return (!(lhs < rhs));
	}

} // Namespace ft

#endif
