#include <iostream>
#include <string>
#include <deque>
#if 1
	#include "map.hpp"
	#include "vector.hpp"
	#include <stack>
#else
	#include <stack>
	#include <map>
	#include <vector>
	namespace ft = std;
#endif

int main ()
{
  ft::map<char,int> mymap;
  ft::map<char,int>::iterator it;

  // insert some values:
  mymap['a']=10;
  mymap['b']=20;
  mymap['c']=30;
  mymap['d']=40;
  mymap['e']=50;
  mymap['f']=60;

  it=mymap.find('b');
  std::cout << "found b\n";
  mymap.erase (it);                   // erasing by iterator
  std::cout << "erase iterator to b\n";
  mymap.erase ('c');                  // erasing by key
  std::cout << "erase by key 'c'\n";
  it=mymap.find ('e');
  std::cout << "erase by range 'e' to end\n";
  mymap.erase ( it, mymap.end() );    // erasing by range

  std::cout << " display :\n";
  // show content:
  for (it=mymap.begin(); it!=mymap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

  return 0;
}
/*
#include <stdlib.h>

#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096
struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};

#define COUNT (MAX_RAM / (int)sizeof(Buffer))

template<typename T>
class MutantStack : public std::stack<T>
{
public:
	MutantStack() {}
	MutantStack(const MutantStack<T>& src) { *this = src; }
	MutantStack<T>& operator=(const MutantStack<T>& rhs)
	{
		this->c = rhs.c;
		return *this;
	}
	~MutantStack() {}

	typedef typename std::stack<T>::container_type::iterator iterator;

	iterator begin() { return this->c.begin(); }
	iterator end() { return this->c.end(); }
};

int main(int argc, char** argv) {
	if (argc != 2)
	{
		std::cerr << "Usage: ./test seed" << std::endl;
		std::cerr << "Provide a seed please" << std::endl;
		std::cerr << "Count value:" << COUNT << std::endl;
		return 1;
	}
	const int seed = atoi(argv[1]);
	srand(seed);
	ft::map<int, int> map_int;

	for (int i = 0; i < COUNT; ++i)
	{
		map_int.insert(ft::make_pair(rand(), rand()));
		std::cout << "map insert = " << i << std::endl;
	}

	int sum = 0;
	for (int i = 0; i < 10000; i++)
	{
		int access = rand();
		sum += map_int[access];
		std::cout << "map access = " << i << std::endl;
	}
	std::cout << "should be constant with the same seed: " << sum << std::endl;

	{
		std::cout << "map copy" << std::endl;
		ft::map<int, int> copy = map_int;
	}

	MutantStack<char> iterable_stack;
	for (char letter = 'a'; letter <= 'z'; letter++)
	{
		std::cout << "stack push" << std::endl;
		iterable_stack.push(letter);
	}
	for (MutantStack<char>::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++)
	{
		std::cout << *it;
	}
	std::cout << std::endl;
	return (0);
}
*/
