#include "PresidentialPardonForm.hpp"
#include "Error.hpp"

PresidentialPardonForm::PresidentialPardonForm() : Form("presidential pardon", 25, 5), target("default") {}

PresidentialPardonForm::PresidentialPardonForm(std::string param) : Form("presidential pardon", 25, 5), target(param) {}

PresidentialPardonForm::~PresidentialPardonForm() {}

void PresidentialPardonForm::execute(Bureaucrat const & executor) const
{
	if (this->getSignature() && executor.getGrade() <= this->getGradeExec())
		std::cout << this->target << " forgived by Zaphod Beeblebrox" << std::endl;
	else
		throw Error("PresidentialPardonForm::NoSignatureOrInvalidGrade");
}
