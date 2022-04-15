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

void	exec_cmds(t_list *cmds, char **env)
{
	t_cmd	*cmd;
	int		pid;

	while (cmds)
	{
		cmd = cmds->content;
		pid = fork();
		if (!pid)
			exec(cmd->cmd_with_args, env);
		else
			waitpid(pid, NULL, 0);
		cmds = cmds->next;
	}
}

int	exec(char **cmd_with_args, char **env)
{
	char	**path;
	char	*absolute;
	int		i;

	path = split(getenv("PATH"), ':');
	if (execve(cmd_with_args[0], cmd_with_args, env) == -1)
	{
		i = -1;
		while (path[++i])
		{
			absolute = make_fullpath(path[i], cmd_with_args[0]);
			execve(absolute, cmd_with_args, env);
			free(absolute);
		}
	}
	printf("minishell: %s: command not found\n", cmd_with_args[0]);
	deep_free(path);
	exit(0);
}

char	*make_fullpath(char *path, char *line)
{
	char 	*cmd;
	int		i;
	int		j;

	i = 0;
	j = 0;
	cmd = malloc(sizeof(char) * ft_strlen(path) + ft_strlen(line) + 2);
	while (path[i])
	{
		cmd[j] = path[i];
		j++;
		i++;
	}
	cmd[j++] = '/';
	i = 0;
	while (line[i])
		cmd[j++] = line[i++];
	cmd[j] = 0;
	return (cmd);
}
