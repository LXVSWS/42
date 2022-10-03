#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat() : name("Varg"), grade(150) {}

Bureaucrat::Bureaucrat(int param) : name("Varg")
{
	if (param < 1)
		throw Error("Bureaucrat::GradeTooHighException");
	else if (param > 150)
		throw Error("Bureaucrat::GradeTooLowException");
	else
		this->grade = param;
}

Bureaucrat::Bureaucrat(const Bureaucrat& src)
{
	*this = src;
}

Bureaucrat& Bureaucrat::operator=(const Bureaucrat& right)
{
	if (this != &right)
		this->grade = right.grade;
	return (*this);
}

Bureaucrat::~Bureaucrat() {}

std::string Bureaucrat::getName() const
{
	return (this->name);
}

int Bureaucrat::getGrade() const
{
	return (this->grade);
}

void Bureaucrat::increment()
{
	if (this->grade > 1)
		--this->grade;
	else
		throw Error("Bureaucrat::GradeTooHighException");
}

void Bureaucrat::decrement()
{
	if (this->grade < 150)
		++this->grade;
	else
		throw Error("Bureaucrat::GradeTooLowException");
}

void Bureaucrat::signForm(const Form &form)
{
	if (form.getSignature())
		std::cout << this->getName() << " signed " << form.getName() << std::endl;
	else
	{
		if (this->grade > form.getGradeSign())
			std::cout << this->getName() << " couldn’t sign " << form.getName() << " because grade is too low" << std::endl;
		else if (this->grade < 1)
			std::cout << this->getName() << " couldn’t sign " << form.getName() << " because grade is too high" << std::endl;
	}
}

Error::Error(std::string param) : message(param) {}

Error::~Error() throw() {}

const char *Error::what() const throw()
{
	return (this->message.c_str());
}

std::ostream &operator<<(std::ostream &dst, const Bureaucrat &src)
{
	dst << src.getName() << ", bureaucrat grade " << src.getGrade() << "." << std::endl;
	return (dst);
}
