#include "common.hpp"

#define TESTED_TYPE int

int		main(void)
{
	TESTED_NAMESPACE::vector<TESTED_TYPE> vct(7);

	for (unsigned long int i = 0; i < vct.size(); ++i)
	{
		vct[i] = (vct.size() - i) * 3;
		std::cout << "vct.at(): " << vct.at(i) << std::endl;
	}
	printSize(vct, true);

	TESTED_NAMESPACE::vector<TESTED_TYPE> const vct_c(vct);

	std::cout << "front(): " << vct.front() << " " << vct_c.front() << std::endl;
	std::cout << "back(): " << vct.back() << " " <<  vct_c.back() << std::endl;


	try
	{
		vct.at(10) = 42;
	}
	catch (std::out_of_range e)
	{
		std::cout << "Caught exception :" << std::endl;
		std::cout << "  what():  " << e.what() << std::endl;
	}
	catch (ft::out_of_range e)
	{
		std::cout << "Caught exception :" << std::endl;
		std::cout << "  what():  " << e.what() << std::endl;
	}

	return (0);
}
