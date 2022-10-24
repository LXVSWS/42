#include "Bureaucrat.hpp"

int	main()
{
	try
	{
		Bureaucrat bc("Varg", 10);
		std::cout << bc;
		bc.increment();
		std::cout << bc;
		bc.decrement();
		std::cout << bc;
	}
	catch(const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	return (0);
}
