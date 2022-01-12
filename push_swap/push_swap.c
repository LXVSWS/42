#include "push_swap.h"
#include <stdio.h>

int main(int ac, char **av)
{
	char	**set;
	int		**a;
	int		*data;
	int		i;
	int		y;
	t_list	*list;

    if (ac == 2)
    {
		set = ft_split(av[1], ' ');
		i = -1;
		y = -1;
		while (set[++i])
		{
			while (set[i][++y])
			{
				if (set[i][y] < 48 || set[i][y] > 57)
				{
					write(2, "Error\n", 6);
					free(set);
					exit(1);
				}
			}
			y = -1;
		}
		a = malloc(sizeof(int *) * i + 1);
		a[i] = NULL;
		i = -1;
		y = -1;
		while (set[++i])
		{
			data = malloc(sizeof(int));
			*data = ft_atoi(set[i]);
			/*
			while (a[++y])
			{
				if (*(a[y]) == *data)
				{
					write(2, "Error\n", 6);
					free(set);
					free(a);
					exit(1);
				}
			}
			*/
			a[i] = data;
			ft_lstadd_back(&list, ft_lstnew(a[i]));
		}
		free(set);
		while (list)
		{
			printf("%i\n", *(int *)(list->content));
			list = list->next;
		}
    }
    else
        write(2, "Error\n", 6);
}
