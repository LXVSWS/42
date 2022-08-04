#include <iostream>

int	main(int ac, char **av)
{
	int i = 0;
	int j = -1;

	if (ac <= 1)
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
	else
	{
		while (av[++i])
		{
			while (av[i][++j])
				if (av[i][j] >= 97 && av[i][j] <= 122)
					std::cout << static_cast<char>(av[i][j] - 32);
				else
					std::cout << (av[i][j]);
			j = -1;
		}
		std::cout << std::endl;
	}
	return (0);
}
