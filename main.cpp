#include "vector.hpp"
#include <vector>
#include <list>

#define TESTED std

int	main(void)
{
	TESTED::list<int>	lst;

	lst.push_back(6);

	auto it = lst.begin();

	std::cout << it->_prev << std::endl;

	return (0);
}
