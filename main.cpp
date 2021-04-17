#include "vector.hpp"
#include <vector>

#define TESTED std

int	main(void)
{
	TESTED::vector<int>	vct;
	TESTED::vector<int>::iterator			it;
	it = vct.begin();
	TESTED::vector<int>::const_iterator	cit;
	cit = vct.begin();

	it = it;
	cit = cit;
	it = cit;
	cit = it;

	return (0);
}
