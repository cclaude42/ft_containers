#ifndef DUMMY_ITERATOR_HPP
# define DUMMY_ITERATOR_HPP
#include <iterator>
template <typename T>
class dummy_input_iterator
{
private:
	T value;
public:
	typedef int difference_type;
	typedef T value_type;
	typedef T* pointer;
	typedef T& reference;
	typedef std::input_iterator_tag iterator_category;

	dummy_input_iterator(T val) : value(val) {}
	dummy_input_iterator(const dummy_input_iterator &other) : value(other.value) {};


	dummy_input_iterator &operator=(const dummy_input_iterator &) {return *this;}

	T operator*() {return value;};

	T *operator->() {return &value;};

	dummy_input_iterator &operator++() {return *this;};

	dummy_input_iterator operator++(int) {return *this;};
};


template <typename T>
bool operator==(const dummy_input_iterator<T> &, const dummy_input_iterator<T> &) {return false;}

template <typename T>
bool operator!=(const dummy_input_iterator<T> &, const dummy_input_iterator<T> &) {return false;}


#endif