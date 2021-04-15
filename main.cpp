#include "vector.hpp"
#include <vector>

int	main(void)
{
	ft::vector<int>	vct;

	std::cerr << vct.max_size() << std::endl;
	std::cerr << sizeof(int) << std::endl;

	return (0);
}
