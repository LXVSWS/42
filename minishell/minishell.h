#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

char	**split(char const *s, char c);
int		ft_strlen(char *s);
char	*make_fullpath(char *path, char *line);
void	deep_free(char **path);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_back(t_list **alst, t_list *new);
void	ft_lstadd_front(t_list **alst, t_list *new);

#endif