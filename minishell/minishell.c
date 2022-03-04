#include "minishell.h"

void	skip_empty(char **line)
{
	while (**line == ' ' || **line == '\t')
		(*line)++;
}

int	main()
{
	char *line;

	while (1)
	{
		line = readline("minishell-0.1$ ");
		if (line[0] == 'e' && line[1] == 'x' && line[2] == 'i' && line[3] == 't')
			break;
		skip_empty(&line);
		printf("%s", line);
	}
	free(line);
}
