#ifndef ITER_HPP
#define ITER_HPP

#include <iostream>

template<typename T>
void iter(T *ptr, int size, void (*fct)(T))
{
	for (int i = 0 ; i < size ; i++)
		fct(ptr[i]);
}

template<typename T>
void fct(T param)
{
	std::cout << param << std::endl;
}

#endif
