#include "Bureaucrat.hpp"
#include "Error.hpp"

Bureaucrat::Bureaucrat() : name("Varg"), grade(150) {}

Bureaucrat::Bureaucrat(std::string p, int param) : name(p)
{
	if (param < 1)
		throw Error("Bureaucrat::GradeTooHighException");
	else if (param > 150)
		throw Error("Bureaucrat::GradeTooLowException");
	else
		this->grade = param;
}

Bureaucrat::Bureaucrat(const Bureaucrat& src) : name(src.name)
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

std::ostream &operator<<(std::ostream &dst, const Bureaucrat &src)
{
	dst << src.getName() << ", bureaucrat grade " << src.getGrade() << "." << std::endl;
	return (dst);
}
