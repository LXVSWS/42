#include "Bureaucrat.hpp"

int	main()
{
	try
	{
		Bureaucrat bc(10);
		std::cout << bc;
	}
	catch(const std::string& e)
	{
		std::cerr << e << std::endl;
	}
	return (0);
}
