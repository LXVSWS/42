#include "includes.hpp"

void check_char(int data)
{
	if ((data >= 0 && data < 32) || (data >= 127 && data <= 255))
		std::cout << "char: Non displayable" << std::endl;
	else if (data < 0 || data > 255)
		std::cout << "char: impossible" << std::endl;
	else
		std::cout << "char: '" << static_cast<char>(data) << "'" << std::endl;
}

int double_detected(char *param) // implement overflow & check precision
{
	double data = std::atof(param);
	check_char(static_cast<int>(data));
	std::cout << "int: " << static_cast<int>(data) << std::endl;
	std::cout << std::fixed << "float: " << static_cast<float>(data) << "f" << std::endl;
	std::cout << std::fixed << "double: " << data << std::endl;
	return (0);
}

int float_detected(char *param) // implement overflow & check precision
{
	float data = std::atof(param);
	check_char(static_cast<int>(data));
	std::cout << "int: " << static_cast<int>(data) << std::endl;
	std::cout << std::fixed << "float: " << data << "f" << std::endl;
	std::cout << std::fixed << "double: " << static_cast<double>(data) << std::endl;
	return (0);
}

int int_detected(char *param)
{
	long test = std::atol(param);
	if (test < -2147483648 || test > 2147483647)
		return (overflow());
	int data = std::atoi(param);
	check_char(data);
	std::cout << "int: " << data << std::endl;
	std::cout << std::fixed << "float: " << static_cast<float>(data) << "f" << std::endl;
	std::cout << std::fixed << "double: " << static_cast<double>(data) << std::endl;
	return (0);
}

void print_values(char data)
{
	std::cout << "int: " << static_cast<int>(data) << std::endl;
	std::cout << std::fixed << "float: " << static_cast<float>(data) << "f" << std::endl;
	std::cout << std::fixed << "double: " << static_cast<double>(data) << std::endl;
}

int special_values(std::string val)
{
	std::cerr << "char: impossible" << std::endl;
	std::cout << "int: impossible" << std::endl;
	if (val == "nan" || val == "nanf")
	{
		std::cout << "float: nanf" << std::endl;
		std::cout << "double: nan" << std::endl;
	}
	else if (val == "-inf" || val == "-inff")
	{
		std::cout << "float: -inff" << std::endl;
		std::cout << "double: -inf" << std::endl;
	}
	else
	{
		std::cout << "float: +inff" << std::endl;
		std::cout << "double: +inf" << std::endl;
	}
	return (0);
}

int overflow(void)
{
	std::cout << "char: impossible" << std::endl;
	std::cout << "int: impossible" << std::endl;
	std::cout << "float: impossible" << std::endl;
	std::cout << "double: impossible" << std::endl;
	return (-1);
}
