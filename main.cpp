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
	mp[-2] = "-two ";
	mp[-6] = "-six ";
	mp[-4] = "-four ";
	mp[-3] = "-three ";

	TESTED::map<int, std::string>::iterator it = mp.begin();
	while (it != mp.end())
		std::cout << (it++)->second << std::endl;
	std::cout << "now in reverse!" << std::endl;
	while (it != mp.begin())
		std::cout << (--it)->second << std::endl;

	return (0);
}
