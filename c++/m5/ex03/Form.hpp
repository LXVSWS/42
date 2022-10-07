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
		Form(std::string param, int, int);
		Form(const Form& src);
		Form& operator=(const Form& right);
		virtual ~Form();

		std::string getName() const;
		bool getSignature() const;
		int getGradeSign() const;
		int getGradeExec() const;

		void beSigned(const Bureaucrat &bc);

		virtual void execute(Bureaucrat const & executor) const = 0;
};

std::ostream &operator<<(std::ostream &dst, const Form &src);

#endif
