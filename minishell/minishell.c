#include "minishell.h"

static int	routine(char **env)
{
	char	*line;
	t_list	*tokens;
	t_list	*cmds;
	int		ret;

	ret = 0;
	line = readline("minishell-0.4$ ");
	if (!line)
	{
		write(1, " exit\n", 6);
		ret = -1;
	}
	else if (*line && line)
	{
		add_history(line);
		tokens = tokenize(line);
		cmds = forge(tokens);
		exec_cmds(cmds, env);
		// need add ft_lstclear(&tokens, &free_token);
	}
	free(line);
	return (ret);
}

int	main(int ac, char **env)
{
	while (ac)
		if (routine(env) == -1)
			break;
	clear_history();
	return (0);
}

void	exec_cmds(t_list *cmds, char **env)
{
	t_cmd	*cmd;
	void	*save;
	int		pipe_needed;
	int		fd[2];
	int		pid;

	save = cmds;
	pipe_needed = -1;
	while (cmds)
	{
		pipe_needed++;
		cmds = cmds->next;
	}
	cmds = save;
	if (pipe_needed > 0)
	{
		printf("%i pipe(s) needed\n", pipe_needed);
		pipe(fd);
	}
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
