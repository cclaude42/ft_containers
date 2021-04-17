#include "vector.hpp"
#include <vector>

#define TESTED std

int	main(void)
{
	std::vector<int>	vct(5, 100);
	std::vector<int>	vct2(8, 100);

	std::cout << (vct < vct2) << std::endl;

	return (0);
}
