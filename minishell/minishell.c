#include "minishell.h"

static int	exec(char *cmd, char **av, char **env)
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

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_list	*tokens;
	t_token *token;
	int		pid;

	while (ac)
	{
		line = readline("minishell-0.1$ ");
		if (*line && line)
		{
			add_history(line);
			tokens = tokenize(line);
			while (tokens)
			{
				token = tokens->content;
				if (token->type == 6)
				{
					pid = fork();
					if (!pid)
						exec(token->val, av, env);
					else
						waitpid(pid, NULL, 0);
				}
				tokens = tokens->next;
			}
		}
		free(line);
	}
	clear_history();
}
