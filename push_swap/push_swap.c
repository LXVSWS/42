#include "push_swap.h"

int main(int ac, char **av)
{
	char	**set;
	int		i;
	int		val;
	t_list	*list;

    if (ac == 2)
    {
		set = ft_split(av[1], ' ');
		i = -1;
		while (set[++i])
		{
			val = ft_atoi(set[i]);
			ft_lstadd_back(&list, ft_lstnew(&val));
		}
		while (list)
		{
			write(1, list->content, 1);
			write(1, "\n", 1);
			list = list->next;
		}
    }
    else
        write(2, "Error\n", 6);
}
