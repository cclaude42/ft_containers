#include <iostream>
#include <vector>
#include "Vector.tpp"

// CHOOSE YOUR VECTOR :
// typedef		std::vector<int>		TheVector;
typedef		const std::vector<int>	TheVector;
// typedef		ft::Vector<int>			TheVector;
// typedef		const ft::Vector<int>	TheVector;

// CHOOSE YOUR ITERATOR :
typedef		TheVector::iterator					TheIterator;
// typedef		TheVector::const_iterator			TheIterator;
// typedef		TheVector::reverse_iterator			TheIterator;
// typedef		TheVector::const_reverse_iterator	TheIterator;

// CHOOSE YOUR METHOD :
#define BEGIN vct.begin()
#define END vct.end()
// #define BEGIN vct.rbegin()
// #define END vct.rend()

int		main(void)
{
	std::vector<int>			real(4, 100);
	TheVector					vct(real.begin(), real.end());

	int	idx = 0;
	for ( TheIterator it = BEGIN ; it != END ; it++ )
		std::cout << "Vector[" << idx++ << "] : " << *it << std::endl;

	for ( TheIterator it2 = BEGIN ; it2 != END ; it2++ )
		*it2 = idx++;

	idx = 0;
	for ( TheIterator it3 = BEGIN ; it3 != END ; it3++ )
		std::cout << "Vector[" << idx++ << "] : " << *it3 << std::endl;

	std::cout << "Vector size : " << END - BEGIN << std::endl;

	return (0);
}
