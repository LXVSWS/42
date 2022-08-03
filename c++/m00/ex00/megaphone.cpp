#include <iostream>

int	main(int ac, char **av)
{
	int i = -1;

	if (ac == 1)
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
	else
	{
		while (av[1][++i])
			std::cout << av[1][i];
		std::cout << std::endl;
	}
	return (0);
}
