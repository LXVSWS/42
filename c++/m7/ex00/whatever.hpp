#ifndef WHATEVER_HPP
#define WHATEVER_HPP

#include <iostream>

template<typename T>
void swap(T &p1, T &p2)
{
	T tmp = p1;
	p1 = p2;
	p2 = tmp;
}

template<typename T>
T min(T p1, T p2)
{
	if (p1 < p2)
		return (p1);
	return (p2);
}

template<typename T>
T max(T p1, T p2)
{
	if (p1 > p2)
		return (p1);
	return (p2);
}

#endif
