#include "common.hpp"

#define TESTED_TYPE int

int		main(void)
{
	const int size = 5;
	TESTED_NAMESPACE::deque<TESTED_TYPE> const vct(size);
	TESTED_NAMESPACE::deque<TESTED_TYPE>::iterator it = vct.begin(); // <-- error expected

	for (int i = 0; i < size; ++i)
		it[i] = i;

	return (0);
}
