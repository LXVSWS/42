#include "Intern.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "Error.hpp"

Intern::Intern() {}

Intern::Intern(const Intern& src)
{
	*this = src;
}

Intern& Intern::operator=(const Intern& right)
{
	if (this != &right)
		(void)right;
	return (*this);
}

Intern::~Intern() {}

Form *Intern::makeForm(std::string name, std::string target)
{
	std::string names[3];
	Form *forms[3];

	names[0] = "presidential pardon";
	names[1] = "robotomy request";
	names[2] = "shrubbery creation";
	forms[0] = new PresidentialPardonForm(target);
	forms[1] = new RobotomyRequestForm(target);
	forms[2] = new ShrubberyCreationForm(target);
	for (int i = 0 ; i < 3 ; i++)
		if (names[i] == name)
		{
			std::cout << "Intern creates " << name << " form with "<< target << " target" << std::endl;
			for (int j = 0 ; j < 3 ; j++)
				if (j != i)
					delete forms[j];
			return (forms[i]);
		}
	for (int k = 0 ; k < 3 ; k++)
		delete forms[k];
	throw Error("Intern::IncorrectFormName");
	return (NULL);
}
