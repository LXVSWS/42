#include "includes.hpp"

int double_detected(char *param)
{
	double data = std::atof(param);
	if (static_cast<int>(data) == -2147483648)
		return (overflow());
	if ((data >= 0 && data < 32) || (data >= 127 && data <= 255))
		std::cout << "char: Non displayable" << std::endl;
	else if (data < 0 || data > 255)
		std::cout << "char: impossible" << std::endl;
	else
		std::cout << "char: '" << static_cast<char>(data) << "'" << std::endl;
	std::cout << "int: " << static_cast<int>(data) << std::endl;
	std::cout << "float: " << static_cast<float>(data) << std::endl;
	std::cout << "double: " << data << std::endl;
	return (0);
}

int int_detected(char *param)
{
	long test = std::atol(param);
	if (test < -2147483648 || test > 2147483647)
		return (overflow());
	int data = std::atoi(param);
	if ((data >= 0 && data < 32) || (data >= 127 && data <= 255))
		std::cout << "char: Non displayable" << std::endl;
	else if (data < 0 || data > 255)
		std::cout << "char: impossible" << std::endl;
	else
		std::cout << "char: '" << static_cast<char>(data) << "'" << std::endl;
	std::cout << "int: " << data << std::endl;
	std::cout << "float: " << static_cast<float>(data) << std::endl;
	std::cout << "double: " << static_cast<double>(data) << std::endl;
	return (0);
}

void print_values(char data)
{
	std::cout << "int: " << static_cast<int>(data) << std::endl;
	std::cout << "float: " << static_cast<float>(data) << ".0" << std::endl;
	std::cout << "double: " << static_cast<double>(data) << ".0" << std::endl;
}

int overflow(void)
{
	std::cout << "char: impossible" << std::endl;
	std::cout << "int: overflow" << std::endl;
	std::cout << "float: overflow" << std::endl;
	std::cout << "double: overflow" << std::endl;
	return (-1);
}
