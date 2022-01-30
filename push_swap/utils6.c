#include "push_swap.h"

int **parsing_multiple_args(char **av)
{
    char    str[1000000];
	int		i;
	int		y;
	int		j;

    i = 0;
    y = -1;
    j = -1;
    while (av[++i])
    {
        while (av[i][++y])
            str[++j] = av[i][y];
        str[++j] = ' '; 
        y = -1;
    }
    return (parsing(ft_split(str, ' ')));
}

void    check_double(int **a, int i)
{
    int y;

    y = i;
    while (a[++y])
        if (*a[y] == *a[i])
            clean_exit((void **)a, 1);
}
