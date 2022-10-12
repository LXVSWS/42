#include "includes.hpp"

int main(int ac, char **av)
{
	if (ac == 2)
	{
		if ((*av[1] >= 48 && *av[1] <= 57) || (*av[1] == 45 && *av[1]))
		{
			for (int i = 0 ; av[1][i] ; i++)
				if (av[1][i] == 46)
					return (float_detected(av[1]));
			return (int_detected(av[1]));
		}
		else if (av[1][1])
		{
			std::cout << "Too much characters" << std::endl;
			return (-1);
		}
		else if ((*av[1] >= 32 && *av[1] <= 47) || (*av[1] > 57 && *av[1] < 127))
			std::cout << "char: '" << *av[1] << "'" << std::endl;
		else
			std::cout << "char: impossible" << std::endl;
		print_values(*av[1]);
	}
	else
		std::cout << "Incorrect parameters" << std::endl;
	return (0);
}
