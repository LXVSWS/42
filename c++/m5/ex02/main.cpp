#include "Bureaucrat.hpp"
#include "Form.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

int	main()
{
	try
	{
		Bureaucrat bc(1);
		//ShrubberyCreationForm test("jardin");
		//RobotomyRequestForm test("cobaye");
		PresidentialPardonForm test("criminal");
		test.beSigned(bc);
		bc.executeForm(test);
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	return (0);
}
