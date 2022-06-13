#include "cub3d.h"

int	ft_strlen(char *s)
{
	int i = 0;

	if (s)
	{
		while (s[i])
			i++;
	}
	return (i);
}

void	check_map_name(char **av)
{
	int size;

	size = ft_strlen(av[1]);
	if (av[1][size - 1] != 'b' || av[1][size - 2] != 'u' \
	|| av[1][size - 3] != 'c' || av[1][size - 4] != '.')
	{
		printf("Error\nWrong extension\n");
		exit(-1);
	}
}

int	map_read(char **av)
{
	int	map_fd;

	map_fd = open(av[1], O_RDONLY);
	if (map_fd == -1)
	{
		printf("Error\nCannot open map\n");
		exit(-1);
	}
	return (map_fd);
}

int	map_size(int map_fd)
{
	int		i;
	int		bytes_read;
	char	buf;

	i = 0;
	bytes_read = 1;
	while (bytes_read)
	{
		bytes_read = read(map_fd, &buf, 1);
		if (bytes_read == -1)
		{
			write(2, "Error\nProblem while reading\n", 28);
			exit(-1);
		};
		if (buf != '\t' && buf != '\n' && buf != ' ' \
		&& buf != '0' && buf != '1' && buf != 'N')
		{
			printf("Error\nIncorrect character in map\n");
			exit(-1);
		}
		i++;
	}
	close(map_fd);
	return (i);
}

char *map_copy(int map_fd, int size)
{
	char	*map;
	int		bytes_read;
	char	buf;

	map = malloc(sizeof(char) * size + 1);
	if (!map)
		return (NULL);
	map[size] = 0;
	size = 0;
	bytes_read = 1;
	while (bytes_read)
	{
		bytes_read = read(map_fd, &buf, 1);
		if (bytes_read == -1)
		{
			write(2, "Error\nProblem while reading\n", 28);
			exit(-1);
		}
		map[size] = buf;
		size++;
	}
	close(map_fd);
	return (map);
}
