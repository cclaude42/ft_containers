#include "common.hpp"

typedef int UNDER_TYPE;
typedef foo<UNDER_TYPE> TESTED_TYPE;

int		main(void)
{
	// 700 unordered ints
	TESTED_TYPE shuffled[] = {
		276, 591,   9, 405, 548, 375, 346
	};
	int n = sizeof(shuffled) / sizeof(TESTED_TYPE);
	TESTED_NAMESPACE::list<TESTED_TYPE> lst(shuffled, shuffled + n);
	TESTED_NAMESPACE::list<TESTED_TYPE>::iterator it;
	for (it = lst.begin(); it != lst.end(); ++it)
		it->switchVerbose();
	std::cout << "\t-- LIST CREATED --" << std::endl;
	printSize(lst);

	std::cout << "\t-- SORT --" << std::endl;
	lst.sort();
	printSize(lst);
	return (0);
}
