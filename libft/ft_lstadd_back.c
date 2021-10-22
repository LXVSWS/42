#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	while (*alst)
		*alst = (*alst)->next;
	*alst = new;
	(*alst)->next = NULL;
}
