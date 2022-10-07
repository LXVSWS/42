#include "Form.hpp"

Form::Form() : name("Formulaire"), signature(false), grade_sign(150), grade_exec(150) {}

Form::Form(std::string param, int param1, int param2) : name(param), signature(false), grade_sign(param1), grade_exec(param2)
{
	if (param1 < 1 || param2 < 1)
		throw Error("Form::GradeTooHighException");
	else if (param1 > 150 || param2 > 150)
		throw Error("Form::GradeTooLowException");
}

Form::Form(const Form& src) : grade_sign(src.grade_sign), grade_exec(src.grade_sign)
{
	*this = src;
}

Form& Form::operator=(const Form& right)
{
	if (this != &right)
		this->signature = right.signature;
	return (*this);
}

Form::~Form() {}

std::string Form::getName() const
{
	return (this->name);
}

bool Form::getSignature() const
{
	return (this->signature);
}

int Form::getGradeSign() const
{
	return (this->grade_sign);
}

int Form::getGradeExec() const
{
	return (this->grade_exec);
}

void Form::beSigned(const Bureaucrat &bc)
{
	if (bc.getGrade() <= this->getGradeSign())
	{
		this->signature = true;
		bc.signForm(*this);
	}
	else
		throw Error("Form::GradeTooLowException");
}

std::ostream &operator<<(std::ostream &dst, const Form &src)
{
	dst << src.getName() << ", signature : " << src.getSignature() << "\nGrade needed to sign : " << src.getGradeSign() \
	<< "\nGrade needed to execute : " << src.getGradeExec() << std::endl;
	return (dst);
}
