#include "vector.hpp"
#include "list.hpp"
#include <vector>
#include <list>

#define TESTED std

int	main(void)
{
	std::allocator<int>	al;
	TESTED::list<std::string, std::allocator<int> > mylist(4, "sisi la mif", al);

	for (TESTED::list<std::string, std::allocator<int> >::iterator it = mylist.begin() ; it != mylist.end() ; it++)
		std::cout << *it << std::endl;

	std::cout << mylist.max_size() << std::endl;

	return 0;
}
