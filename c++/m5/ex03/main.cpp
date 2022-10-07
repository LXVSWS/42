#include "Intern.hpp"

int	main()
{
    Intern  someRandomIntern;
    Form*   rrf;

	try
	{
		rrf = someRandomIntern.makeForm("robotomy request", "Bender");
		std::cout << rrf->getName() << " successfully created" << std::endl;
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	return (0);
}
