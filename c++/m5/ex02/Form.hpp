#ifndef FORM_HPP
#define FORM_HPP

#include "Bureaucrat.hpp"

class Bureaucrat;

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
		virtual ~Form();

		virtual std::string getName() const = 0;
		bool getSignature() const;
		int getGradeSign() const;
		int getGradeExec() const;

		void beSigned(const Bureaucrat &bc);
};

std::ostream &operator<<(std::ostream &dst, const Form &src);

#endif
