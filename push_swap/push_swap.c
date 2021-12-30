#include "push_swap.h"

int main(int ac, char **av)
{
    int i;
    int j;

    if (ac > 1)
    {
        i = 0;
        while (av[++i])
        {
            j = -1;
            while (av[i][++j])
                if (av[i][j] >= '0' && av[i][j] <= '9')
                    write(1, &av[i][j], 1);
        }
    }
    else
        write(2, "Error\n", 6);
}
