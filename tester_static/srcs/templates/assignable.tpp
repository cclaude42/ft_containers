#ifndef ASSIGNABLE_TPP
# define ASSIGNABLE_TPP
# include <type_traits>
template <typename T>
void assignable(T &t)
{
	t = t;
	static_assert(std::is_same<decltype(t = t), T&>::value, "wrong return type for assignation");
}

#endif