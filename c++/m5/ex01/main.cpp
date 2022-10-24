#include "Bureaucrat.hpp"
#include "Form.hpp"

int	main()
{
	try
	{
		Bureaucrat bc("Varg", 10);
		Form form(50, 150);
		form.beSigned(bc);
		std::cout << form;
	}
	catch(const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	return (0);
}
