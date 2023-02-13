namespace ft {}
using namespace ft;

#include "vector.hpp"
#include "map.hpp"
#include <vector>
#include <map>

int main()
{
	vector<int> t1(1, 42);

	std::cout << t1.max_size() << std::endl;
	for (vector<int>::iterator it = t1.begin() ; it != t1.end() ; ++it)
		std::cout << *it << std::endl;

	return (0);
}
