#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char	buffer[1000000];
	int		bytes;
	int		pid;

	while (ac)
	{
		write(1, "minishell-0.1$ ", 15);
		bytes = read(0, buffer, 1000000);
		buffer[bytes - 1] = 0;
		if (buffer[0] && buffer[0] != ' ')
		{
			pid = fork();
			if (!pid)
			{
				if (execve(buffer, av, env) == -1)
					printf("minishell: %s: command not found\n", buffer);
			}
			else
				waitpid(pid, NULL, 0);
		}
	}
}
