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
	if (ac != 2)
	{
		std::cout << "Select a valid test" << std::endl;
		return (1);
	}
	if (av[1][0] == '!' || av[1][0] == '$')
	{
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		vector<int> t1;
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		if (av[1][0] == '!')
			for (vector<int>::iterator it = t1.begin() ; it != t1.end() ; ++it)
				std::cout << *it << std::endl;
		if (av[1][0] == '$')
			printTime(begin, end);
		return (0);
	}
	if ((av[1][0] == '0' || av[1][0] == '1') && !av[1][1])
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
	if ((av[1][0] == '2' || av[1][0] == '3') && !av[1][1])
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
	if ((av[1][0] == '4' || av[1][0] == '5') && !av[1][1])
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
	if ((av[1][0] == '6' || av[1][0] == '7') && !av[1][1])
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
	if ((av[1][0] == '8' || av[1][0] == '9') && !av[1][1])
	{
		vector<int> t1(6, 22);
		t1.push_back(1);t1.push_back(2);t1.push_back(3);t1.push_back(4);t1.push_back(5);
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		int res = t1.size();
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
		int res = t1.max_size();
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
		int res = t1.capacity();
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
		int res = t1.empty();
		int res2 = t2.empty();
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		if (av[1][0] == 'g')
			std::cout << res << " " << res2 << std::endl;
		if (av[1][0] == 'h')
			printTime(begin, end);
		return (0);
	}
	if (av[1][0] == 'i' || av[1][0] == 'j')
	{
		vector<int> t1;
		int res = t1.capacity();
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		t1.reserve(10);
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		int res2 = t1.capacity();
		if (av[1][0] == 'i')
			std::cout << res << " " << res2 << std::endl;
		if (av[1][0] == 'j')
			printTime(begin, end);
		return (0);
	}
	if (av[1][0] == 'k' || av[1][0] == 'l')
	{
		vector<int> t1;
		t1.push_back(1);t1.push_back(2);t1.push_back(3);t1.push_back(4);t1.push_back(5);
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		int res = t1[3];
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		if (av[1][0] == 'k')
			std::cout << res << std::endl;
		if (av[1][0] == 'l')
			printTime(begin, end);
		return (0);
	}
	if (av[1][0] == 'm' || av[1][0] == 'n')
	{
		vector<int> t1;
		t1.push_back(1);t1.push_back(2);t1.push_back(3);t1.push_back(4);t1.push_back(5);
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		int res = t1.at(2);
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		if (av[1][0] == 'm')
			std::cout << res << std::endl;
		if (av[1][0] == 'n')
			printTime(begin, end);
		return (0);
	}
	if (av[1][0] == 'o' || av[1][0] == 'p')
	{
		vector<int> t1;
		t1.push_back(1);t1.push_back(2);t1.push_back(3);t1.push_back(4);t1.push_back(5);
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		int res = t1.front();
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		if (av[1][0] == 'o')
			std::cout << res << std::endl;
		if (av[1][0] == 'p')
			printTime(begin, end);
		return (0);
	}
	if (av[1][0] == 'q' || av[1][0] == 'r')
	{
		vector<int> t1;
		t1.push_back(1);t1.push_back(2);t1.push_back(3);t1.push_back(4);t1.push_back(5);
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		int res = t1.back();
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		if (av[1][0] == 'q')
			std::cout << res << std::endl;
		if (av[1][0] == 'r')
			printTime(begin, end);
		return (0);
	}
	if (av[1][0] == 's' || av[1][0] == 't')
	{
		vector<int> t1(1, 1);
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		int *res = t1.data();
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		if (av[1][0] == 's')
			std::cout << *res << std::endl;
		if (av[1][0] == 't')
			printTime(begin, end);
		return (0);
	}
	if (av[1][0] == 'u' || av[1][0] == 'v')
	{
		vector<int> t1;
		vector<int> t2(7, 77);
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		t1.assign(t2.begin(), t2.end());
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		if (av[1][0] == 'u')
			for (vector<int>::iterator it = t1.begin() ; it != t1.end() ; ++it)
				std::cout << *it << std::endl;
		if (av[1][0] == 'v')
			printTime(begin, end);
		return (0);
	}
	if (av[1][0] == 'w' || av[1][0] == 'x')
	{
		vector<int> t1(2, 88);
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		t1.assign(2, 44);
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		if (av[1][0] == 'w')
			for (vector<int>::iterator it = t1.begin() ; it != t1.end() ; ++it)
				std::cout << *it << std::endl;
		if (av[1][0] == 'x')
			printTime(begin, end);
		return (0);
	}
	if (av[1][0] == 'y' || av[1][0] == 'z')
	{
		vector<int> t1(3, 33);
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		t1.push_back(10);
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		if (av[1][0] == 'y')
			for (vector<int>::iterator it = t1.begin() ; it != t1.end() ; ++it)
				std::cout << *it << std::endl;
		if (av[1][0] == 'z')
			printTime(begin, end);
		return (0);
	}
	if ((av[1][0] == '0' && av[1][1] == '0') || (av[1][0] == '0' && av[1][1] == '1'))
	{
		vector<int> t1(4, 12);
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		t1.pop_back();
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		if (av[1][0] == '0' && av[1][1] == '0')
			for (vector<int>::iterator it = t1.begin() ; it != t1.end() ; ++it)
				std::cout << *it << std::endl;
		if (av[1][0] == '0' && av[1][1] == '1')
			printTime(begin, end);
		return (0);
	}
	if ((av[1][0] == '0' && av[1][1] == '2') || (av[1][0] == '0' && av[1][1] == '3'))
	{
		vector<int> t1(1, 89);
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		t1.insert(t1.begin(), 90);
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		if (av[1][0] == '0' && av[1][1] == '2')
			for (vector<int>::iterator it = t1.begin() ; it != t1.end() ; ++it)
				std::cout << *it << std::endl;
		if (av[1][0] == '0' && av[1][1] == '3')
			printTime(begin, end);
		return (0);
	}
	if ((av[1][0] == '0' && av[1][1] == '4') || (av[1][0] == '0' && av[1][1] == '5'))
	{
		vector<int> t1(2, 77);
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		t1.insert(t1.begin(), 4, 80);
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		if (av[1][0] == '0' && av[1][1] == '4')
			for (vector<int>::iterator it = t1.begin() ; it != t1.end() ; ++it)
				std::cout << *it << std::endl;
		if (av[1][0] == '0' && av[1][1] == '5')
			printTime(begin, end);
		return (0);
	}
	if ((av[1][0] == '0' && av[1][1] == '6') || (av[1][0] == '0' && av[1][1] == '7'))
	{
		vector<int> t1(3, 33);
		vector<int> t2(2, 22);
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		t1.insert(t1.begin(), t2.begin(), t2.end());
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		if (av[1][0] == '0' && av[1][1] == '6')
			for (vector<int>::iterator it = t1.begin() ; it != t1.end() ; ++it)
				std::cout << *it << std::endl;
		if (av[1][0] == '0' && av[1][1] == '7')
			printTime(begin, end);
		return (0);
	}
	if ((av[1][0] == '0' && av[1][1] == '8') || (av[1][0] == '0' && av[1][1] == '9'))
	{
		vector<int> t1(6, 66);
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		t1.erase(t1.begin());
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		if (av[1][0] == '0' && av[1][1] == '8')
			for (vector<int>::iterator it = t1.begin() ; it != t1.end() ; ++it)
				std::cout << *it << std::endl;
		if (av[1][0] == '0' && av[1][1] == '9')
			printTime(begin, end);
		return (0);
	}
	if ((av[1][0] == '1' && av[1][1] == '0') || (av[1][0] == '1' && av[1][1] == '1'))
	{
		vector<int> t1(5, 55);
		vector<int>::iterator itr = t1.begin();
		++itr;
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		t1.erase(itr, t1.end());
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		if (av[1][0] == '1' && av[1][1] == '0')
			for (vector<int>::iterator it = t1.begin() ; it != t1.end() ; ++it)
				std::cout << *it << std::endl;
		if (av[1][0] == '1' && av[1][1] == '1')
			printTime(begin, end);
		return (0);
	}
	if ((av[1][0] == '1' && av[1][1] == '2') || (av[1][0] == '1' && av[1][1] == '3'))
	{
		vector<int> t1(6, 12);
		vector<int> t2(5, 19);
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		t1.swap(t2);
		swap< vector<int> >(t1, t2);
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		if (av[1][0] == '1' && av[1][1] == '2')
		{
			for (vector<int>::iterator it = t1.begin() ; it != t1.end() ; ++it)
				std::cout << *it << std::endl;
			for (vector<int>::iterator it = t2.begin() ; it != t2.end() ; ++it)
				std::cout << *it << std::endl;
		}
		if (av[1][0] == '1' && av[1][1] == '3')
			printTime(begin, end);
		return (0);
	}
	if ((av[1][0] == '1' && av[1][1] == '4') || (av[1][0] == '1' && av[1][1] == '5'))
	{
		vector<int> t1(7, 77);
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		t1.clear();
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		if (av[1][0] == '1' && av[1][1] == '4')
			for (vector<int>::iterator it = t1.begin() ; it != t1.end() ; ++it)
				std::cout << *it << std::endl;
		if (av[1][0] == '1' && av[1][1] == '5')
			printTime(begin, end);
		return (0);
	}
	if ((av[1][0] == '1' && av[1][1] == '6') || (av[1][0] == '1' && av[1][1] == '7'))
	{
		vector<int> t1(2, 10);
		vector<int> t2(2, 20);
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		if (av[1][0] == '1' && av[1][1] == '6')
		{
			std::cout << (t1 == t2) << std::endl;
			std::cout << (t1 != t2) << std::endl;
			std::cout << (t1 < t2) << std::endl;
			std::cout << (t1 <= t2) << std::endl;
			std::cout << (t1 > t2) << std::endl;
			std::cout << (t1 >= t2) << std::endl;
		}
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		if (av[1][0] == '1' && av[1][1] == '7')
			printTime(begin, end);
		return (0);
	}
	if ((av[1][0] == '1' && av[1][1] == '8') || (av[1][0] == '1' && av[1][1] == '9'))
	{
		vector<int> t1(5, 50);
		t1.push_back(100);
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		if (av[1][0] == '1' && av[1][1] == '8')
		{
			std::cout << *t1.begin() << std::endl;
			std::cout << *t1.rbegin() << std::endl;
		}
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		if (av[1][0] == '1' && av[1][1] == '9')
			printTime(begin, end);
		return (0);
	}
	if ((av[1][0] == '2' && av[1][1] == '0') || (av[1][0] == '2' && av[1][1] == '1'))
	{
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		map<int, int> t1;
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		if (av[1][0] == '2' && av[1][1] == '0')
			for (map<int, int>::iterator it = t1.begin() ; it != t1.end() ; ++it)
				std::cout << it->first << ":" << it->second << std::endl;
		if (av[1][0] == '2' && av[1][1] == '1')
			printTime(begin, end);
		return (0);
	}
	if ((av[1][0] == '2' && av[1][1] == '2') || (av[1][0] == '2' && av[1][1] == '3'))
	{
		map<int, int> t2;
		t2.insert(pair<int, int>(1, 1));t2.insert(pair<int, int>(2, 2));t2.insert(pair<int, int>(0, 0));
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		map<int, int> t1(t2.begin(), t2.end());
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		if (av[1][0] == '2' && av[1][1] == '2')
			for (map<int, int>::iterator it = t1.begin() ; it != t1.end() ; ++it)
				std::cout << it->first << ":" << it->second << std::endl;
		if (av[1][0] == '2' && av[1][1] == '3')
			printTime(begin, end);
		return (0);
	}
	if ((av[1][0] == '2' && av[1][1] == '4') || (av[1][0] == '2' && av[1][1] == '5'))
	{
		map<int, int> t2;
		t2.insert(pair<int, int>(1, 1));t2.insert(pair<int, int>(2, 2));t2.insert(pair<int, int>(0, 0));
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		map<int, int> t1(t2);
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		if (av[1][0] == '2' && av[1][1] == '4')
			for (map<int, int>::iterator it = t1.begin() ; it != t1.end() ; ++it)
				std::cout << it->first << ":" << it->second << std::endl;
		if (av[1][0] == '2' && av[1][1] == '5')
			printTime(begin, end);
		return (0);
	}
	if ((av[1][0] == '2' && av[1][1] == '6') || (av[1][0] == '2' && av[1][1] == '7'))
	{
		map<int, int> t2;
		t2.insert(pair<int, int>(1, 1));t2.insert(pair<int, int>(2, 2));t2.insert(pair<int, int>(0, 0));
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		map<int, int> t1 = t2;
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		if (av[1][0] == '2' && av[1][1] == '6')
			for (map<int, int>::iterator it = t1.begin() ; it != t1.end() ; ++it)
				std::cout << it->first << ":" << it->second << std::endl;
		if (av[1][0] == '2' && av[1][1] == '7')
			printTime(begin, end);
		return (0);
	}
	if ((av[1][0] == '2' && av[1][1] == '8') || (av[1][0] == '2' && av[1][1] == '9'))
	{
		map<int, int> t1;
		map<int, int> t2;
		t2.insert(pair<int, int>(1, 1));t2.insert(pair<int, int>(2, 2));
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		int res = t1.empty();
		int res2 = t2.empty();
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		if (av[1][0] == '2' && av[1][1] == '8')
			std::cout << res << " " << res2 << std::endl;
		if (av[1][0] == '2' && av[1][1] == '9')
			printTime(begin, end);
		return (0);
	}
	if ((av[1][0] == '3' && av[1][1] == '0') || (av[1][0] == '3' && av[1][1] == '1'))
	{
		map<int, int> t1;
		t1.insert(pair<int, int>(1, 1));t1.insert(pair<int, int>(2, 2));t1.insert(pair<int, int>(0, 0));
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		int res = t1.size();
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		if (av[1][0] == '3' && av[1][1] == '0')
			std::cout << res << std::endl;
		if (av[1][0] == '3' && av[1][1] == '1')
			printTime(begin, end);
		return (0);
	}
	if ((av[1][0] == '3' && av[1][1] == '2') || (av[1][0] == '3' && av[1][1] == '3'))
	{
		map<int, int> t1;
		t1.insert(pair<int, int>(1, 1));
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		t1[2];
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		if (av[1][0] == '3' && av[1][1] == '2')
			for (map<int, int>::iterator it = t1.begin() ; it != t1.end() ; ++it)
				std::cout << it->first << ":" << it->second << std::endl;
		if (av[1][0] == '3' && av[1][1] == '3')
			printTime(begin, end);
		return (0);
	}
	if ((av[1][0] == '3' && av[1][1] == '4') || (av[1][0] == '3' && av[1][1] == '5'))
	{
		map<int, int> t1;
		t1.insert(pair<int, int>(1, 1));t1.insert(pair<int, int>(2, 2));
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		int res = t1.at(2);
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		if (av[1][0] == '3' && av[1][1] == '4')
			std::cout << res << std::endl;
		if (av[1][0] == '3' && av[1][1] == '5')
			printTime(begin, end);
		return (0);
	}
	if ((av[1][0] == '3' && av[1][1] == '6') || (av[1][0] == '3' && av[1][1] == '7'))
	{
		map<int, int> t1;
		t1.insert(pair<int, int>(1, 1));t1.insert(pair<int, int>(2, 2));
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		t1.insert(pair<int, int>(0, 0));
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		if (av[1][0] == '3' && av[1][1] == '6')
			for (map<int, int>::iterator it = t1.begin() ; it != t1.end() ; ++it)
				std::cout << it->first << ":" << it->second << std::endl;
		if (av[1][0] == '3' && av[1][1] == '7')
			printTime(begin, end);
		return (0);
	}
	if ((av[1][0] == '3' && av[1][1] == '8') || (av[1][0] == '3' && av[1][1] == '9'))
	{
		map<int, int> t1;
		map<int, int> t2;
		t2.insert(pair<int, int>(1, 1));t2.insert(pair<int, int>(2, 2));t2.insert(pair<int, int>(0, 0));
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		t1.insert(t2.begin(), t2.end());
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		if (av[1][0] == '3' && av[1][1] == '8')
			for (map<int, int>::iterator it = t1.begin() ; it != t1.end() ; ++it)
				std::cout << it->first << ":" << it->second << std::endl;
		if (av[1][0] == '3' && av[1][1] == '9')
			printTime(begin, end);
		return (0);
	}
	if ((av[1][0] == '4' && av[1][1] == '0') || (av[1][0] == '4' && av[1][1] == '1'))
	{
		map<int, int> t1;
		t1.insert(pair<int, int>(1, 1));t1.insert(pair<int, int>(2, 2));t1.insert(pair<int, int>(0, 0));
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		t1.erase(t1.begin());
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		if (av[1][0] == '4' && av[1][1] == '0')
			for (map<int, int>::iterator it = t1.begin() ; it != t1.end() ; ++it)
				std::cout << it->first << ":" << it->second << std::endl;
		if (av[1][0] == '4' && av[1][1] == '1')
			printTime(begin, end);
		return (0);
	}
	if ((av[1][0] == '4' && av[1][1] == '2') || (av[1][0] == '4' && av[1][1] == '3'))
	{
		map<int, int> t1;
		t1.insert(pair<int, int>(1, 1));t1.insert(pair<int, int>(2, 2));t1.insert(pair<int, int>(0, 0));
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		t1.erase(2);
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		if (av[1][0] == '4' && av[1][1] == '2')
			for (map<int, int>::iterator it = t1.begin() ; it != t1.end() ; ++it)
				std::cout << it->first << ":" << it->second << std::endl;
		if (av[1][0] == '4' && av[1][1] == '3')
			printTime(begin, end);
		return (0);
	}
	if ((av[1][0] == '4' && av[1][1] == '4') || (av[1][0] == '4' && av[1][1] == '5'))
	{
		map<int, int> t1;
		t1.insert(pair<int, int>(1, 1));t1.insert(pair<int, int>(2, 2));
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		t1.erase(t1.begin(), t1.end());
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		if (av[1][0] == '4' && av[1][1] == '4')
			for (map<int, int>::iterator it = t1.begin() ; it != t1.end() ; ++it)
				std::cout << it->first << ":" << it->second << std::endl;
		if (av[1][0] == '4' && av[1][1] == '5')
			printTime(begin, end);
		return (0);
	}
	if ((av[1][0] == '4' && av[1][1] == '6') || (av[1][0] == '4' && av[1][1] == '7'))
	{
		map<int, int> t1;
		map<int, int> t2;
		t1.insert(pair<int, int>(5, 5));t1.insert(pair<int, int>(10, 10));
		t2.insert(pair<int, int>(6, 6));t2.insert(pair<int, int>(20, 20));
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		t1.swap(t2);
		swap< map<int, int> >(t1, t2);
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		if (av[1][0] == '4' && av[1][1] == '6')
		{
			for (map<int, int>::iterator it = t1.begin() ; it != t1.end() ; ++it)
				std::cout << it->first << ":" << it->second << std::endl;
			for (map<int, int>::iterator it = t2.begin() ; it != t2.end() ; ++it)
				std::cout << it->first << ":" << it->second << std::endl;
		}
		if (av[1][0] == '4' && av[1][1] == '7')
			printTime(begin, end);
		return (0);
	}
	if ((av[1][0] == '4' && av[1][1] == '8') || (av[1][0] == '4' && av[1][1] == '9'))
	{
		map<int, int> t1;
		t1.insert(pair<int, int>(100, 100));t1.insert(pair<int, int>(200, 200));
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		t1.clear();
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		if (av[1][0] == '4' && av[1][1] == '8')
			for (map<int, int>::iterator it = t1.begin() ; it != t1.end() ; ++it)
				std::cout << it->first << ":" << it->second << std::endl;
		if (av[1][0] == '4' && av[1][1] == '9')
			printTime(begin, end);
		return (0);
	}
	if ((av[1][0] == '5' && av[1][1] == '0') || (av[1][0] == '5' && av[1][1] == '1'))
	{
		map<int, int> t1;
		t1.insert(pair<int, int>(55, 55));t1.insert(pair<int, int>(22, 22));
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		map<int, int>::iterator it = t1.find(22);
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		if (av[1][0] == '5' && av[1][1] == '0')
			std::cout << it->first << ":" << it->second << std::endl;
		if (av[1][0] == '5' && av[1][1] == '1')
			printTime(begin, end);
		return (0);
	}
	if ((av[1][0] == '5' && av[1][1] == '2') || (av[1][0] == '5' && av[1][1] == '3'))
	{
		map<int, int> t1;
		t1.insert(pair<int, int>(44, 44));t1.insert(pair<int, int>(22, 22));
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		int res = t1.count(44);
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		if (av[1][0] == '5' && av[1][1] == '2')
			std::cout << res << std::endl;
		if (av[1][0] == '5' && av[1][1] == '3')
			printTime(begin, end);
		return (0);
	}
	if ((av[1][0] == '5' && av[1][1] == '4') || (av[1][0] == '5' && av[1][1] == '5'))
	{
		map<int, int> t1;
		t1.insert(pair<int, int>(10, 10));t1.insert(pair<int, int>(20, 20));
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		map<int, int>::iterator it = t1.lower_bound(20);
		map<int, int>::iterator itr = t1.upper_bound(10);
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		if (av[1][0] == '5' && av[1][1] == '4')
			std::cout << it->first << ":" << it->second << itr->first << ":" << itr->second << std::endl;
		if (av[1][0] == '5' && av[1][1] == '5')
			printTime(begin, end);
		return (0);
	}
	if ((av[1][0] == '5' && av[1][1] == '6') || (av[1][0] == '5' && av[1][1] == '7'))
	{
		map<int, int> t1;
		t1.insert(pair<int, int>(10, 10));t1.insert(pair<int, int>(20, 20));
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		pair< map<int, int>::iterator, map<int, int>::iterator > res = t1.equal_range(10);
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		if (av[1][0] == '5' && av[1][1] == '6')
			std::cout << res.first->first << res.second->first << std::endl;
		if (av[1][0] == '5' && av[1][1] == '7')
			printTime(begin, end);
		return (0);
	}
	if ((av[1][0] == '5' && av[1][1] == '8') || (av[1][0] == '5' && av[1][1] == '9'))
	{
		map<int, int> t1;
		map<int, int> t2;
		t1.insert(pair<int, int>(555, 555));t1.insert(pair<int, int>(777, 777));
		t2.insert(pair<int, int>(777, 777));t2.insert(pair<int, int>(555, 555));
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		if (av[1][0] == '5' && av[1][1] == '8')
		{
			std::cout << (t1 == t2) << std::endl;
			std::cout << (t1 != t2) << std::endl;
			std::cout << (t1 < t2) << std::endl;
			std::cout << (t1 <= t2) << std::endl;
			std::cout << (t1 > t2) << std::endl;
			std::cout << (t1 >= t2) << std::endl;
		}
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		if (av[1][0] == '5' && av[1][1] == '9')
			printTime(begin, end);
		return (0);
	}
	if ((av[1][0] == '6' && av[1][1] == '0') || (av[1][0] == '6' && av[1][1] == '1'))
	{
		map<int, int> t1;
		t1.insert(pair<int, int>(666, 666));t1.insert(pair<int, int>(999, 999));
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		if (av[1][0] == '6' && av[1][1] == '0')
		{
			std::cout << t1.begin()->first << std::endl;
			std::cout << t1.rbegin()->first << std::endl;
		}
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		if (av[1][0] == '6' && av[1][1] == '1')
			printTime(begin, end);
		return (0);
	}
	std::cout << "Select a valid test" << std::endl;
	return (1);
}
