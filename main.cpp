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

	mp[10] = "";
	mp[5] = "";
	mp[15] = "";
	mp[20] = "";
	mp[18] = "";

	return (0);
}
