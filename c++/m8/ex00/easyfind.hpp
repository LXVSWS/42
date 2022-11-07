#ifndef EASYFIND_HPP
#define EASYFIND_HPP

#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <deque>

template<typename T>
int easyfind(T container, int integer)
{
	if (find(container.begin(), container.end(), integer) != container.end())
		return (integer);
	throw (integer);
}

#endif
