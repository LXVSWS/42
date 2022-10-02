#include "Bureaucrat.hpp"
#include "Form.hpp"

int	main()
{
	try
	{
		Form();
	}
	catch(const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	return (0);
}
