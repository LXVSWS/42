#include "minishell.h"

int	main()
{
	char	buffer[1000000];
	int		bytes;

	while (1)
	{
		write(1, "minishell-0.1$ ", 15);
		bytes = read(0, buffer, 1000000);
		if (bytes > 1)
			write(1, buffer, bytes);
	}
}
