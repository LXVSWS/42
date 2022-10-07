#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm() : Form("shrubbery creation", 145, 137), target("default") {}

ShrubberyCreationForm::ShrubberyCreationForm(std::string param) : Form("shrubbery creation", 145, 137), target(param) {}

ShrubberyCreationForm::~ShrubberyCreationForm() {}

void ShrubberyCreationForm::execute(Bureaucrat const & executor) const
{
	if (this->getSignature() && executor.getGrade() <= this->getGradeExec())
	{
		std::ofstream file(this->target + "_shrubbery");
		if (file.is_open())
		{
			file << "               ,@@@@@@@,\n";
			file << "       ,,,.   ,@@@@@@/@@,  .oo8888o.\n";
			file << "    ,&%%&%&&%,@@@@@/@@@@@@,8888\\88/8o\n";
			file << "   ,%&\\%&&%&&%,@@@\\@@@/@@@88\\88888/88'\n";
			file << "   %&&%&%&/%&&%@@\\@@/ /@@@88888\\88888'\n";
			file << "   %&&%/ %&%%&&@@\\ V /@@' `88\\8 `/88'\n";
			file << "   `&%\\ ` /%&'    |.|        \\ '|8'\n";
			file << "       |o|        | |         | |\n";
			file << "       |.|        | |         | |\n";
			file << "    \\\\/ ._\\//_/__/  ,\\_//__\\\\/.  \\_//__/_" << std::endl;
			file.close();
		}
	}
	else
		throw Error("ShrubberyCreationForm::NoSignatureOrInvalidGrade");
}
