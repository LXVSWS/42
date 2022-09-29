#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <iostream>

class Bureaucrat
{
	const std::string name;
	int grade;

	public:
		Bureaucrat();
		Bureaucrat(int);
		~Bureaucrat();

		std::string getName() const;
		int getGrade() const;
};

std::ostream &operator<<(std::ostream &dst, const Bureaucrat &src);

#endif
