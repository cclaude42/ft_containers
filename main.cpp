#include <utility>
#include <iostream>
#include "includes/utility.hpp"

int main(void)
{
	ft::pair<int, int>	pra(2, 3);
	ft::pair<int, int>	prb(2, 4);

	std::cout << std::boolalpha << (pra < prb) << std::endl;
}
