#ifndef FORM_HPP
#define FORM_HPP

#include "Bureaucrat.hpp"

class Form
{
	const std::string name;
	bool signature;
	const int grade_sign;
	const int grade_exec;

	public:
		Form();
		Form(int, int);
		Form(const Form& src);
		Form& operator=(const Form& right);
		~Form();

		std::string getName() const;
		bool getSignature() const;
		int getGradeSign() const;
		int getGradeExec() const;
};

std::ostream &operator<<(std::ostream &dst, const Form &src);

#endif
