#ifndef SHRUBBERYCREATIONFORM_HPP
#define SHRUBBERYCREATIONFORM_HPP

#include "Form.hpp"
#include <fstream>

class ShrubberyCreationForm : public Form
{
	std::string target;

	public:
		ShrubberyCreationForm();
		ShrubberyCreationForm(std::string);
		~ShrubberyCreationForm();

		void execute(Bureaucrat const & executor) const;
};

#endif
