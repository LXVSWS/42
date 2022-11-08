#include "Span.hpp"

int main()
{
	Span span(10);
	Span span2(100000);
	try
	{
		span.addNumber(6);
		span.addNumber(3);
		span.addNumber(17);
		span.addNumber(9);
		span.addNumber(11);
		std::cout << "Test with 5 numbers and printing span:" << std::endl;
		std::cout << "shortestSpan: " << span.shortestSpan() << std::endl;
		std::cout << "longestSpan: " << span.longestSpan() << std::endl;
	}
	catch(std::string & e)
	{
		std::cout << e << std::endl;
	}
	try
	{
		std::cout << "\nTest with 100000 numbers:" << std::endl;
		for (unsigned int i = 0 ; i < 100000 ; i++)
			span2.addNumber(i);
		std::cout << "Test successful" << std::endl;
	}
	catch(std::string & e)
	{
		std::cout << e << std::endl;
	}
	try
	{
		unsigned int size = 5;
		int numbers[size];
		for (unsigned int i = 0 ; i < size ; i++)
			numbers[i] = i;
		std::cout << "\nTest adding multiple numbers into one call:\nNumbers before calling function:" << std::endl;
		span.getNumbers();
		span.addMultipleNumbers(numbers, size);
		std::cout << "Numbers after calling function:" << std::endl;
		span.getNumbers();
	}
	catch(std::string & e)
	{
		std::cout << e << std::endl;
	}
	return (0);
}
