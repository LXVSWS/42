#include "minishell.h"

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
