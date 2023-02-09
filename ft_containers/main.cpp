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

#include <stdlib.h>

/*
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

template <class K, class V>
void	printMap(ft::map<K, V> m){
	std::string r = "";
	for (typename ft::map<K,V>::iterator it = m.begin(); it != m.end(); it++){
		r += std::to_string((*it).first);
		r += ":";
		r += std::to_string((*it).second);
		r += " ";
	}
	std::cout << r << std::endl;
}

int main()
{
	#define K int
	#define M int
//CONSTRUCTORS
	ft::map<K,M> m;
	m[-34] = 1;
	m[0345] = 12;
	m[654] = -24;
	m[234] = 53;
	ft::map<K,M> n(m);
	ft::map<K,M> o = n;
//ITERATORS
	for (ft::map<K,M>::iterator it = m.begin(); it != m.end(); it++)
		it->second = 0;
	for (ft::map<K,M>::const_iterator it = m.begin(); it != m.end(); it++)
		std::cout << it->first << ":" << it->second << " ";
	std::cout << std::endl;
	int i = 9;
	for (ft::map<K,M>::reverse_iterator it = m.rbegin(); it != m.rend(); it++)
		it->second = i++;
	for (ft::map<K,M>::const_reverse_iterator it = m.rbegin(); it != m.rend(); it++)
		std::cout << it->first << ":" << it->second << " ";
	std::cout << std::endl;
//CAPACITY
	std::cout << m.empty() << m.size() << m.max_size() << std::endl;
//ELEMENT_ACCESS
	printMap(m);
	std::cout << m[14];
	printMap(m);
	std::cout << m[229] << std::endl;
//MODIFIERS
	m.insert(ft::make_pair(35,54));
	printMap(m);
	ft::map<K,M>::iterator hh = m.begin();
	hh++;
	m.insert(hh, ft::make_pair(-200,-200));
	m.insert(n.begin(), n.end());
	for (int i = 0; i < 4; i++)
		n.insert(ft::make_pair(i, i));
	m.insert(n.begin(), n.end());
	printMap(m);
	m.erase(m.begin());
	m.erase(1);
	printMap(m);
	m.clear();
	for (int i = 0; i < 12; i++){
		m.insert(ft::make_pair(i*5,i*5));
		n.insert(ft::make_pair(i,i));
	}
	m.swap(n);
	printMap(m);
	printMap(n);
//OPERATIONS
	//std::cout << m.find(5)->second << m.count(5) << m.count(43) << std::endl;
	//std::cout << m.lower_bound(30)->second << m.upper_bound(30)->second << std::endl;
	return 0;
}
