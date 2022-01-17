#include "push_swap.h"
#include <stdio.h>

void	clean_exit(void **set)
{
	int	i;

	write(2, "Error\n", 6);
	i = -1;
	while (set[++i])
		free(set[i]);
	free(set);
	exit(1);
}

void	free_set(void **set)
{
	int	i;

	i = -1;
	while (set[++i])
		free(set[i]);
	free(set);
}

int main(int ac, char **av)
{
	char	**set;
	int		**a;
	int		*d;
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
				if ((set[i][y] < 48 || set[i][y] > 57) && set[i][y] != 45)
					clean_exit((void **)set);
			y = -1;
			if (ft_atol(set[i]) < -2147483648 || ft_atol(set[i]) > 2147483647)
				clean_exit((void **)set);
		}
		a = malloc(sizeof(int *) * i + 1);
		a[i] = NULL;
		i = -1;
		while (set[++i])
		{
			d = malloc(sizeof(int));
			*d = (int)ft_atol(set[i]);
			a[i] = d;
		}
		free_set((void **)set);
		i = -1;
		while (a[++i])
		{
			y = i;
			while (a[++y])
				if (*a[y] == *a[i])
					clean_exit((void **)a);
			ft_lstadd_back(&list, ft_lstnew(a[i]));
		}
		while (list)
		{
			printf("%i\n", *(int *)(list->content));
			list = list->next;
		}
    }
    else
        write(2, "Error\n", 6);
}
