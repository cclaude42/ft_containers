#include "vector.hpp"
#include "list.hpp"
#include <vector>
#include <list>

#define TESTED ft

int	main(void)
{
	std::allocator<int>	al;
	TESTED::list<std::string> mylist(4, "sisi la mif", al);

	for (TESTED::list<std::string>::iterator it = mylist.begin() ; it != mylist.end() ; it++)
		std::cout << it->next << std::endl;

	std::cout << mylist.max_size() << std::endl;

	return 0;
}
