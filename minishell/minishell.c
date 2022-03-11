#include "minishell.h"

void	skip_spaces(char **line)
{
	while (**line == ' ' || **line == '\t')
		(*line)++;
}

int	main()
{
	char	*line;
	char	*original_line;

	while (1)
	{
		line = readline("minishell-0.1$ ");
		if (*line && line)
		{
			add_history(line);
			original_line = line;
			skip_spaces(&line);
			printf("%s", line);
		}
		free(original_line);
	}
	clear_history();
}
