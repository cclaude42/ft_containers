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
	ft::map<int, std::string>	mp;

	mp[15] = "";
	mp[20] = "";
	mp[10] = "";
	mp[25] = "";
	mp[22] = "";
	mp[17] = "";
	mp[7] = "";

	mp.erase(22);
	mp.erase(20);

	return (0);
}
