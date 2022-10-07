#ifndef ROBOTOMYREQUESTFORM_HPP
#define ROBOTOMYREQUESTFORM_HPP

#include "Form.hpp"

class RobotomyRequestForm : public Form
{
	std::string target;

	public:
		RobotomyRequestForm();
		RobotomyRequestForm(std::string);
		~RobotomyRequestForm();

		void execute(Bureaucrat const & executor) const;
};

#endif
