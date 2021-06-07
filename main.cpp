#include <iostream>
#include "map.hpp"
#include <map>
#include <deque>
#include "includes/utility.hpp"

#ifndef TESTED
# define TESTED ft
#endif

int main(void)
{
	std::deque<int>	dq;

	std::cout << dq.capacity() << std::endl;

	return (0);
}
