#include "minishell.h"

static int	routine(char **av, char **env)
{
	char	*line;
	t_list	*tokens;
	t_list	*cmds;
	int		ret;

	ret = 0;
	line = readline("minishell-0.2$ ");
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
		exec_cmds(cmds, av, env);
		// need add ft_lstclear(&tokens, &free_token);
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
