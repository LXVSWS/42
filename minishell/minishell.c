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

static void	play_with_tokens(t_list	*tokens, char **av, char **env)
{
	t_token *token;
	int		pid;

	token = tokens->content;
	if (token->type == 6)
	{
		pid = fork();
		if (!pid)
			exec(token->val, av, env);
		else
			waitpid(pid, NULL, 0);
	}
}

static int	routine(char **av, char **env)
{
	char	*line;
	t_list	*tokens;
	int		ret;

	ret = 0;
	line = readline("minishell-0.1$ ");
	if (!line)
	{
		write(1, " exit\n", 6);
		ret = -1;
	}
	else if (*line && line)
	{
		add_history(line);
		tokens = tokenize(line);
		while (tokens)
		{
			play_with_tokens(tokens, av, env);
			tokens = tokens->next;
		} // need add ft_lstclear(&tokens, &free_token);
	}
	free(line);
	return (ret);
}

int	main(int ac, char **av, char **env)
{
	while (ac)
		if (routine(av, env) == -1)
			break;
	clear_history();
	return (0);
}
