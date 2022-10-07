#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <iostream>
#include "Form.hpp"

class Form;

class Bureaucrat
{
	const std::string name;
	int grade;

	public:
		Bureaucrat();
		Bureaucrat(int);
		Bureaucrat(const Bureaucrat& src);
		Bureaucrat& operator=(const Bureaucrat& right);
		~Bureaucrat();

		std::string getName() const;
		int getGrade() const;
		void increment();
		void decrement();
		void signForm(const Form &form) const;
};

class Error : public std::exception
{
	std::string message;

	public:
		Error(std::string);
		~Error() throw();
		const char *what() const throw();
};

std::ostream &operator<<(std::ostream &dst, const Bureaucrat &src);

#endif
