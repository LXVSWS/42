#include "Span.hpp"

Span::Span() : N(0) {}

Span::Span(unsigned int num) : N(num) {}

Span::Span(const Span & src)
{
	*this = src;
}

Span & Span::operator=(const Span & src)
{
	if (this != &src)
	{
		this->N = src.N;
		this->vector = src.vector;
	}
	return (*this);
}

Span::~Span() {}

void Span::addNumber(int num)
{
	if (this->vector.size() < this->N)
		this->vector.push_back(num);
	else
		throw std::string("Span::MaximumNumbersReachedException");
}

unsigned int Span::shortestSpan(void)
{
	if (this->vector.size() > 1)
	{
		std::sort(this->vector.begin(), this->vector.end());
		return (this->vector[1] - this->vector.front() - 1);
	}
	else
		throw std::string("Span::NotEnoughNumbersException");
}

unsigned int Span::longestSpan(void)
{
	if (this->vector.size() > 1)
	{
		std::sort(this->vector.begin(), this->vector.end());
		return (this->vector.back() - this->vector.front());
	}
	else
		throw std::string("Span::NotEnoughNumbersException");
}

void Span::addMultipleNumbers(int *nums, unsigned int size)
{
	if (this->vector.size() + size <= this->N)
		this->vector.insert(this->vector.end(), nums, nums + size);
	else
		throw std::string("Span::OverrideMaximumNumbersException");
}

void Span::getNumbers()
{
	for (std::vector<int>::iterator it = this->vector.begin() ; it != this->vector.end() ; ++it)
		std::cout << *it << " - ";
	std::cout << std::endl;
}
