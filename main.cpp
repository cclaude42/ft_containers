#include <iostream>
#include <vector>
#include "Vector.tpp"

int		main(void)
{
	std::vector<int>			real(4, 100);
	std::vector<int>			broken(real.end(), real.begin());
	// Vector<int>					mine(real.end(), real.begin());

	return (0);
}
