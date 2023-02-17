namespace ft {}
using namespace ft;

#include "vector.hpp"
#include "map.hpp"
#include <vector>
#include <map>

void printTime(std::chrono::steady_clock::time_point begin, std::chrono::steady_clock::time_point end)
{
	std::chrono::steady_clock::duration time = end - begin;
	double ns = static_cast<double>(time.count()) * std::chrono::steady_clock::period::num / std::chrono::steady_clock::period::den;
	std::cout.precision(9);
	std::cout << std::fixed << ns << "s" << std::endl;
}

int main(int ac, char **av)
{
	if (ac == 1)
	{
		std::cout << "Please select a test" << std::endl;
		return (1);
	}
	if (av[1][0] == '0' || av[1][0] == '1')
	{
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		vector<int> t1(2, 42);
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		if (av[1][0] == '0')
			for (vector<int>::iterator it = t1.begin() ; it != t1.end() ; ++it)
				std::cout << *it << std::endl;
		if (av[1][0] == '1')
			printTime(begin, end);
		return (0);
	}
	if (av[1][0] == '2' || av[1][0] == '3')
	{
		vector<int> t1;
		vector<int> t2(2, 42);
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		t1 = t2;
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		if (av[1][0] == '2')
			for (vector<int>::iterator it = t1.begin() ; it != t1.end() ; ++it)
				std::cout << *it << std::endl;
		if (av[1][0] == '3')
			printTime(begin, end);
		return (0);
	}
	return (0);
}
