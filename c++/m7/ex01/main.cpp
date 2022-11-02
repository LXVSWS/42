#include "iter.hpp"

int main()
{
	int i = 1;
	int (*pf)() = NULL;
	iter(&i, 2, pf);
	return (0);
}
