#include <iostream>
#include <vector>
#include "Vector.tpp"

// CHOOSE YOUR VECTOR :
// typedef		std::vector<int>		TheVector;
// typedef		const std::vector<int>	TheVector;
typedef		ft::Vector<int>			TheVector;
// typedef		const ft::Vector<int>	TheVector;

// CHOOSE YOUR METHOD :
#define BEGIN vct.begin()
#define END vct.end()
// #define BEGIN vct.rbegin()
// #define END vct.rend()

// CHOOSE YOUR ITERATOR :
typedef		TheVector::iterator					TheIterator;
// typedef		TheVector::const_iterator			TheIterator;
// typedef		TheVector::reverse_iterator			TheIterator;
// typedef		TheVector::const_reverse_iterator	TheIterator;

void	resize_print(TheVector & vct, unsigned int n)
{
	(void)n;
	vct.resize(427387902);

	std::cout << vct.size() << " " << vct.capacity() << " " << vct.max_size() << "\n";
}

int		main(void)
{
	std::vector<int>			real(1, 1);

	int							idx = 1;
	for (std::vector<int>::iterator it = real.begin() ; it != real.end() ; it++ )
		*it = idx++;

	TheVector					vct(real.begin(), real.end());
	TheIterator					it = BEGIN;

	idx = 0;
	while (it != END)
		std::cout << "Vector[" << idx++ << "] : " << *(it++) << std::endl;
	std::cout << std::endl;

	it--;
	idx = 0;
	while (it != BEGIN)
		std::cout << "Vector[" << idx++ << "] : " << *(it--) << std::endl;
	std::cout << std::endl;

	resize_print(vct, 0);

	return (0);
}
