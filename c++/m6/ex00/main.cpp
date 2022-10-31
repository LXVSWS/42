#include "includes.hpp"

int main(int ac, char **av)
{
	if (ac == 2)
	{
		if ((*av[1] >= 48 && *av[1] <= 57) || \
		(*av[1] == 45 && (av[1][1] >= 48 && av[1][1] <= 57)))
		{
			char flag = 0;
			for (int i = 1 ; av[1][i] ; i++)
			{
				if (av[1][i] == 46 && !flag)
					flag = 1;
				else if ((av[1][i] < 48 || av[1][i] > 57) || (av[1][i] == 46 && flag))
				{
					if ((av[1][i] == 'f' || av[1][i] == 'F') && !av[1][i + 1] && flag)
					{
						flag = 2;
						continue;
					}
					std::cerr << "Error" << std::endl;
					return (-1);
				}
			}
			if (flag == 1)
				return (double_detected(av[1]));
			else if (flag == 2)
				return (float_detected(av[1]));
			return (int_detected(av[1]));
		}
		else if (av[1][1])
		{
			std::string input = static_cast<std::string>(av[1]);
			if (input == "-inff" || input == "+inff" || input == "nanf" || \
			input == "-inf" || input == "+inf" || input == "nan")
				return (special_values(input));
			std::cerr << "Error" << std::endl;
			return (-1);
		}
		else if ((*av[1] >= 32 && *av[1] <= 47) || (*av[1] > 57 && *av[1] < 127))
			std::cout << "char: '" << *av[1] << "'" << std::endl;
		else
			std::cerr << "char: impossible" << std::endl;
		print_values(*av[1]);
	}
	else
		std::cerr << "Incorrect parameters" << std::endl;
	return (0);
}
