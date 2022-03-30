#include "minishell.h"

int	exec(char *cmd, char **av, char **env)
{
	char	**path;
	char	*absolute;
	int		i;

	path = split(getenv("PATH"), ':');
	if (execve(cmd, av, env) == -1)
	{
		i = -1;
		while (path[++i])
		{
			absolute = make_fullpath(path[i], cmd);
			execve(absolute, av, env);
			free(absolute);
		}
	}
	printf("minishell: %s: command not found\n", cmd);
	deep_free(path);
	exit(0);
}

void	exec_cmds(t_list *cmds, char **av, char **env)
{
	t_cmd	*cmd;
	int		pid;

	while (cmds)
	{
		cmd = cmds->content;
		pid = fork();
		if (!pid)
			exec(cmd->cmd_with_args, av, env);
		else
			waitpid(pid, NULL, 0);
		cmds = cmds->next;
	}
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
