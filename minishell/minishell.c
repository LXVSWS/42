#include "minishell.h"

t_list	*parsing(char *line)
{
	char	**path;
	t_list	*cmds;
	int		i;

	path = split(getenv("PATH"), ':');
	i = -1;
	while (path[++i])
		ft_lstadd_front(&cmds, ft_lstnew(make_fullpath(path[i], line)));
	deep_free(path);
	return (cmds);
}

int	forked(char *line, char **av, char **env)
{
	t_list	*cmds;

	while (*line == ' ' || *line == '\t')
		line++;
	cmds = NULL;
	if (execve(line, av, env) == -1)
		cmds = parsing(line);
	while (execve(cmds->content, av, env) == -1 && cmds->next)
		cmds = cmds->next;
	printf("minishell: %s: command not found\n", line);
	exit(0);
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	int		pid;

	while (ac)
	{
		line = readline("minishell-0.1$ ");
		if (*line && line)
		{
			add_history(line);
			pid = fork();
			if (!pid)
				forked(line, av, env);
			else
				waitpid(pid, NULL, 0);
		}
		free(line);
	}
	clear_history();
}
