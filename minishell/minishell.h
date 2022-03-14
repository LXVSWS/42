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

typedef struct s_token
{
	int		type;
	char	*val;
}	t_token;

char	**split(char const *s, char c);
int		get_word_size(char *line);
int		extract_word(char **line, t_token *token);
int		extract_symbol(char **line, t_token *token);
t_token	*get_token(char **line);
t_list	*tokenize(char *line);
void	skip_blank(char **line);
int		check_symbol(char c);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_back(t_list **alst, t_list *new);
void	ft_strncpy(char *dst, const char *src, int n);
int		ft_strlen(char *s);
char	*make_fullpath(char *path, char *line);
void	deep_free(char **path);

#endif
