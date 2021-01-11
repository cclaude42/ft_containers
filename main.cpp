#include <iostream>
#include <vector>
#include "Vector.tpp"

int		main(void)
{
	std::vector<int>			real(4, 100);
	// std::vector<int>			broken(real.begin(), real.begin() - 1);
	Vector<int>					mine(real.begin(), real.end());

	int	idx = 0;
	for ( Vector<int>::iterator it = mine.begin() ; it != mine.end() ; it++ )
		std::cout << "Vector[" << idx++ << "] : " << *it << std::endl;

	std::cout << "Vector size : " << mine.end() - mine.begin() << std::endl;

	return (0);
}
