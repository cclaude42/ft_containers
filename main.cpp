#include <iostream>
#include <deque>
#include "deque.hpp"

int main ()
{
  ft::deque<int> mydeque;
  int sum (0);

  for (int i=1;i<=10;i++) mydeque.push_back(i);

  while (!mydeque.empty())
  {
     sum += mydeque.front();
     mydeque.pop_front();
  }

  std::cout << "total: " << sum << '\n';

  return 0;
}
