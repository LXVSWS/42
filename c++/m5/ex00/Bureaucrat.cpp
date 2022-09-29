#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat()
{
	this->grade = 150;
}

Bureaucrat::Bureaucrat(int param)
{
	if (param < 1)
		throw std::string("Bureaucrat::GradeTooLowException");
	else if (param > 150)
		throw std::string("Bureaucrat::GradeTooHighException");
	else
		this->grade = param;
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

std::ostream &operator<<(std::ostream &dst, const Bureaucrat &src)
{
	dst << src.getName() << ", bureaucrat grade " << src.getGrade() << "." << std::endl;
	return (dst);
}
