#include "Span.hpp"

int main()
{
	Span span(5);
	Span span2(100000);
	try
	{
		span.addNumber(6);
		span.addNumber(3);
		span.addNumber(17);
		span.addNumber(9);
		span.addNumber(11);
		std::cout << "Test with 5 numbers:" << std::endl;
		std::cout << span.shortestSpan() << std::endl;
		std::cout << span.longestSpan() << std::endl;
	}
	catch(std::string & e)
	{
		std::cout << e << std::endl;
	}
	try
	{
		for (unsigned int i = 0 ; i < 100000 ; i++)
			span2.addNumber(i);
		std::cout << "Test with 100000 numbers:" << std::endl;
		std::cout << span2.shortestSpan() << std::endl;
		std::cout << span2.longestSpan() << std::endl;
	}
	catch(std::string & e)
	{
		std::cout << e << std::endl;
	}
	return (0);
}
