#include "vector.hpp"
#include <vector>

#define TESTED ft

int	main(void)
{
	TESTED::vector<int>	vct(10, 100);
	TESTED::vector<int>	vct2;
	TESTED::vector<int>::iterator	it = vct.begin();
	TESTED::vector<int>::iterator	it2 = vct.end();


	vct2.assign(it2, it);

	for (TESTED::vector<int>::iterator it3 = vct2.begin() ; it3 != vct2.end() ; it3++)
	std::cout << *it3 << std::endl;

	return (0);
}
