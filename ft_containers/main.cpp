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
	if (ac < 2 || ac > 3)
	{
		std::cout << "Please select a valid test" << std::endl;
		return (1);
	}
	if (av[1][0] == '0' || av[1][0] == '1')
	{
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		vector<int> t1(10, 42);
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
		vector<int> t1(9, 66);
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		vector<int> t2(t1.begin(), t1.end());
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		if (av[1][0] == '2')
			for (vector<int>::iterator it = t2.begin() ; it != t2.end() ; ++it)
				std::cout << *it << std::endl;
		if (av[1][0] == '3')
			printTime(begin, end);
		return (0);
	}
	if (av[1][0] == '4' || av[1][0] == '5')
	{
		vector<int> t2(8, 6);
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		vector<int> t1(t2);
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		if (av[1][0] == '4')
			for (vector<int>::iterator it = t1.begin() ; it != t1.end() ; ++it)
				std::cout << *it << std::endl;
		if (av[1][0] == '5')
			printTime(begin, end);
		return (0);
	}
	if (av[1][0] == '6' || av[1][0] == '7')
	{
		vector<int> t1;
		vector<int> t2(7, 96);
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		t1 = t2;
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		if (av[1][0] == '6')
			for (vector<int>::iterator it = t1.begin() ; it != t1.end() ; ++it)
				std::cout << *it << std::endl;
		if (av[1][0] == '7')
			printTime(begin, end);
		return (0);
	}
	if (av[1][0] == '8' || av[1][0] == '9')
	{
		vector<int> t1(6, 22);
		t1.push_back(1);t1.push_back(2);t1.push_back(3);t1.push_back(4);t1.push_back(5);
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		size_t res = t1.size();
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		if (av[1][0] == '8')
			std::cout << res << std::endl;
		if (av[1][0] == '9')
			printTime(begin, end);
		return (0);
	}
	if (av[1][0] == 'a' || av[1][0] == 'b')
	{
		vector<int> t1;
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		size_t res = t1.max_size();
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		if (av[1][0] == 'a')
			std::cout << res << std::endl;
		if (av[1][0] == 'b')
			printTime(begin, end);
		return (0);
	}
	if (av[1][0] == 'c' || av[1][0] == 'd')
	{
		vector<int> t1(4, 42);
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		t1.resize(2);
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		if (av[1][0] == 'c')
			for (vector<int>::iterator it = t1.begin() ; it != t1.end() ; ++it)
				std::cout << *it << std::endl;
		if (av[1][0] == 'd')
			printTime(begin, end);
		return (0);
	}
	if (av[1][0] == 'e' || av[1][0] == 'f')
	{
		vector<int> t1(8, 44);
		t1.push_back(1);t1.push_back(2);t1.push_back(3);t1.push_back(4);t1.push_back(5);
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		size_t res = t1.capacity();
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		if (av[1][0] == 'e')
			std::cout << res << std::endl;
		if (av[1][0] == 'f')
			printTime(begin, end);
		return (0);
	}
	if (av[1][0] == 'g' || av[1][0] == 'h')
	{
		vector<int> t1;
		vector<int> t2(2, 24);
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		size_t res = t1.empty();
		size_t res2 = t2.empty();
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		if (av[1][0] == 'g')
			std::cout << res << " " << res2 << std::endl;
		if (av[1][0] == 'h')
			printTime(begin, end);
		return (0);
	}
	return (0);
}
