#include "push_swap.h"

int main(int ac, char **av)
{
	char **set;

    if (ac == 2)
    {
		set = split(av[1], ' ');
		write(1, *set, 2);
    }
    else
        write(2, "Error\n", 6);
}
