#ifndef PRESIDENTIALPARDONFORM_HPP
#define PRESIDENTIALPARDONFORM_HPP

#include "Form.hpp"

class PresidentialPardonForm : public Form
{
	std::string target;

	public:
		PresidentialPardonForm();
		PresidentialPardonForm(std::string);
		~PresidentialPardonForm();

		void execute(Bureaucrat const & executor) const;
};

#endif
