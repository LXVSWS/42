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

typedef struct s_cmd
{
	char	**cmd_with_args;
}	t_cmd;

void	skip_blank(char **line);
t_list	*tokenize(char *line);
t_token	*get_token(char **line);
int		check_symbol(char c);
int		extract_symbol(char **line, t_token *token);
int		get_word_size(char *line);
int		extract_word(char **line, t_token *token);
t_list	*forge(t_list *tokens);
t_cmd	*get_cmd(t_list **tokens);
char	**split(char const *s, char c);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_back(t_list **alst, t_list *new);
void	ft_strncpy(char *dst, const char *src, int n);
int		ft_strlen(char *s);
void	deep_free(char **path);
int		exec(char *cmd, char **av, char **env);
void	exec_cmds(t_list *cmds, char **av, char **env);
char	*make_fullpath(char *path, char *line);

#endif
