#include "queue.hpp"
#include <deque>
#include <queue>

int main()
{
	ft::queue<int> qu_;

	std::cout << "empty: " << qu_.empty() << std::endl;
	std::cout << "size: " << qu_.size() << std::endl;

	qu_.push(41);
	qu_.push(29);
	qu_.push(10);
	qu_.push(42);
	std::cout << "Added some elements" << std::endl;

	qu_.back() = 404;

	std::cout << "empty: " << qu_.empty() << std::endl;

	return (0);
}
