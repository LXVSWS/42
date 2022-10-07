#include "RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm() : Form("robotomy request", 72, 45), target("default") {}

RobotomyRequestForm::RobotomyRequestForm(std::string param) : Form("robotomy request", 72, 45), target(param) {}

RobotomyRequestForm::~RobotomyRequestForm() {}

void RobotomyRequestForm::execute(Bureaucrat const & executor) const
{
	if (this->getSignature() && executor.getGrade() <= this->getGradeExec())
	{
		if (this->target.length() % 2 == 0)
			std::cout << "Brrrrr ! Brrrrr ! " << this->target << " robotomization success" << std::endl;
		else
			std::cout << this->target << " robotomization failed" << std::endl;
	}
	else
		throw Error("RobotomyRequestForm::NoSignatureOrInvalidGrade");
}
