#include "common.hpp"

#define T1 int

int		main(void)
{
	TESTED_NAMESPACE::set<T1> const st;
	TESTED_NAMESPACE::set<T1>::iterator it = st.begin(); // <-- error expected

	(void)it;
	return (0);
}
