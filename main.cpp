#include <iostream>
#include <vector>
#include "Vector.tpp"

// CHOOSE YOUR VECTOR :
// typedef		std::vector<int>		TheVector;
typedef		ft::Vector<int>			TheVector;

// CHOOSE YOUR ITERATOR :
// typedef		TheVector::iterator				TheIterator;
typedef		TheVector::const_iterator		TheIterator;


int		main(void)
{
	std::vector<int>			real(4, 100);
	const TheVector					vct(real.begin(), real.end());

	int	idx = 0;
	for ( TheIterator it = vct.begin() ; it != vct.end() ; it++ )
		std::cout << "Vector[" << idx++ << "] : " << *it << std::endl;

	for ( TheIterator it2 = vct.begin() ; it2 != vct.end() ; it2++ )
		*it2 = 45;

	for ( TheIterator it3 = vct.begin() ; it3 != vct.end() ; it3++ )
		std::cout << "Vector[" << idx++ << "] : " << *it3 << std::endl;

	std::cout << "Vector size : " << vct.end() - vct.begin() << std::endl;

	return (0);
}
