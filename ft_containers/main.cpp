#include "map.hpp"
#include "vector.hpp"

int main()
{
    ft::map<int, int> m1;
    m1.insert(ft::pair<int, int>(1, 1));
	m1.erase(1);
	m1.insert(ft::pair<int, int>(2, 2));
	for (ft::map<int, int>::iterator it = m1.begin() ; it != m1.end() ; ++it)
		std::cout << it->first << std::endl;
	return (0);
}
