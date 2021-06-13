#include <vector>
#include "vector.hpp"

#ifndef STD
# define NAMESPACE ft
#else
# define NAMESPACE std
#endif

using namespace NAMESPACE;

template <class T>
void	print(vector<vector<T> >& lst)
{
	for (typename vector<vector<T> >::iterator it = lst.begin(); it != lst.end(); it++)
	{
		for (typename vector<T>::iterator it2 = it->begin(); it2 != it->end(); it2++)
			std::cout << *it2 << ' ';
		std::cout << '\n';
	}
}

template <class T>
void	print(vector<T>& lst)
{
	for (typename vector<T>::iterator it = lst.begin(); it != lst.end(); it++)
		std::cout << *it << ' ';
	std::cout << '\n';
}


int main ()
{
  vector<int> myvector (3,100);
  vector<int>::iterator it;
  vector<int>::iterator bit;

  it = myvector.begin();
  it = myvector.insert ( it , 200 );

  std::cout << "myvector contains:";
  for (bit=myvector.begin(); bit<myvector.end(); bit++)
	std::cout << ' ' << *bit;
  std::cout << '\n';

  myvector.insert (it,2,300);

  // "it" no longer valid, get a new one:
  it = myvector.begin();

  std::cout << "myvector contains:";
  for (bit=myvector.begin(); bit<myvector.end(); bit++)
    std::cout << ' ' << *bit;
  std::cout << '\n';

  vector<int> anothervector (2,400);
  myvector.insert (it+2,anothervector.begin(),anothervector.end());

  std::cout << "myvector contains:";
  for (bit=myvector.begin(); bit<myvector.end(); bit++)
	std::cout << ' ' << *bit;
  std::cout << '\n';

  int myarray [] = { 501,502,503 };
  myvector.insert (myvector.begin(), myarray, myarray+3);

  std::cout << "myvector contains:";
  for (it=myvector.begin(); it<myvector.end(); it++)
    std::cout << ' ' << *it;
  std::cout << '\n';

  return 0;
}
