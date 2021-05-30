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

	mp[13] = "thirteen ";
	mp[5] = "five ";
	mp[7] = "seven ";
	mp[15] = "fifteen ";
	mp[2] = "two ";
	mp[10] = "ten ";

	for (TESTED::map<int, std::string>::iterator it = mp.begin() ; it != mp.end() ; it++)
		std::cout << it->second << std::endl;

	return (0);
}
