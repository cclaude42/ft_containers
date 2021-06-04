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

	mp[5] = "";
	mp[3] = "";
	mp[7] = "";
	mp[2] = "";
	mp[1] = "";

	return (0);
}
