#include "minishell.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*l;

	l = malloc(sizeof(t_list));
	if (!l)
		return (NULL);
	l->content = content;
	l->next = NULL;
	return (l);
}

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*tmp;

	tmp = *alst;
	if (*alst)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		*alst = new;
}

void	ft_strncpy(char *dst, const char *src, int n)
{
	int	i;

	if (!dst || !src || n < 0)
		return ;
	i = 0;
	while (src[i] && i < n)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
}

int		ft_strlen(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (i);
	while (s[i])
		i++;
	return (i);
}

void	deep_free(char **path)
{
	int	i;

	i = -1;
	while (path[++i])
		free(path[i]);
	free(path);
}
