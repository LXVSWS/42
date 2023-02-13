namespace ft {}
using namespace ft;

#include "vector.hpp"
#include "map.hpp"
#include <vector>
#include <map>

int main()
{
	vector<int> t1(1, 42);

	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

	std::cout << t1.max_size() << std::endl;
	for (vector<int>::iterator it = t1.begin() ; it != t1.end() ; ++it)
		std::cout << *it << std::endl;

	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	std::chrono::steady_clock::duration time = end - begin;
	double ns = static_cast<double>(time.count()) * std::chrono::steady_clock::period::num / std::chrono::steady_clock::period::den;
	std::cout.precision(9);
	std::cout << std::fixed << ns << "s" << std::endl;

	return (0);
}
