#ifndef BASE_HPP
#define BASE_HPP

#include <iostream>

class Base
{
	public:
		virtual ~Base() = 0;
};

class A : public Base {};

class B : public Base {};

class C : public Base {};

#endif
