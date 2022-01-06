#include "push_swap.h"

int main(int ac, char **av)
{
	char	**set;
	int		i;

    if (ac == 2)
    {
		set = split(av[1], ' ');
		i = -1;
		while (set[++i])
		{
			write(1, set[i], strlen(set[i]));
			write(1, "\n", 1);
		}
    }
    else
        write(2, "Error\n", 6);
}
