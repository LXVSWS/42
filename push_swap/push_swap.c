#include "push_swap.h"
#include <stdio.h>

int main(int ac, char **av)
{
	char	**set;
	int		i;
	t_list	*list;

    if (ac == 2)
    {
		set = ft_split(av[1], ' ');
		i = -1;
		while (set[++i])
			ft_lstadd_back(&list, ft_lstnew(set[i]));
		while (list)
		{
			printf("%i\n", ft_atoi(list->content));
			list = list->next;
		}
    }
    else
        write(2, "Error\n", 6);
}
