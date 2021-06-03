#include <iostream>
#include "map.hpp"
#include <map>
#include "includes/utility.hpp"

#ifndef TESTED
# define TESTED ft
#endif

int main(void)
{
	TESTED::map<int, std::string>	mp;

	mp.get_allocator();

	return (0);
}
