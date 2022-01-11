#include "push_swap.h"

int main(int ac, char **av)
{
	t_list	*list;
	char	**set;
	int		i;

    if (ac == 2)
    {
		set = ft_split(av[1], ' ');
		i = 0;
		list = ft_lstnew(set[i]);
		while (set[++i])
			ft_lstadd_back(&list, ft_lstnew(set[i]));
    }
    else
        write(2, "Error\n", 6);
}
