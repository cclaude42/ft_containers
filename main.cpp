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

int		main(void)
{
	std::vector<int>			real(7, 1);

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

	ft::Vector<int>::const_iterator	it2 = it;

	idx = 0;
	it = BEGIN;
	while (it < END)
	{
		std::cout << "Vector[" << idx << "] : " << *it << std::endl;
		idx++;
		it++;
	}

	return (0);
}
