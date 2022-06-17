#include "cub3d.h"

int	file_read(char **av)
{
	int size;
	int	fd;

	size = ft_strlen(av[1]);
	if (av[1][size - 1] != 'b' || av[1][size - 2] != 'u' \
	|| av[1][size - 3] != 'c' || av[1][size - 4] != '.')
	{
		printf("Error\nWrong file extension\n");
		exit(-1);
	}
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		printf("Error\nCannot open file\n");
		exit(-1);
	}
	return (fd);
}

int	file_size(int fd)
{
	int		i;
	int		bytes_read;
	char	buf;

	i = 0;
	bytes_read = 1;
	while (bytes_read)
	{
		bytes_read = read(fd, &buf, 1);
		if (bytes_read == -1)
		{
			printf("Error\nProblem while reading file\n");
			exit(-1);
		}
		i++;
	}
	close(fd);
	return (i);
}

char *file_copy(int fd, int size)
{
	char	*file;
	int		bytes_read;
	char	buf;

	file = malloc(sizeof(char) * size + 1);
	if (!file)
	{
		printf("Error\nMalloc problem\n");
		exit(-1);
	}
	file[size] = 0;
	size = 0;
	bytes_read = 1;
	while (bytes_read)
	{
		bytes_read = read(fd, &buf, 1);
		if (bytes_read == -1)
		{
			printf("Error\nProblem while reading file\n");
			exit(-1);
		}
		file[size] = buf;
		size++;
	}
	close(fd);
	return (file);
}

void	check_file(t_data *data, char *file)
{
	int i = 0;
	int x = 0;
	int x_max = 0;
	int y = 0;

	while (file[i])
	{
		if (file[i] != '\t' && file[i] != '\n' && file[i] != ' ' \
		&& file[i] != '0' && file[i] != '1' && file[i] != 'N')
		{
			printf("Error\nIncorrect character in map\n");
			exit(-1);
		}
		if (file[i] == '\n')
		{
			if (file[i + 1] && file[i + 1] == '\n' && file[i + 2])
			{
				printf("Error\nMultiple empty lines in map\n");
				exit(-1);
			}
			if (x > x_max)
				x_max = x;
			x = 0;
			if (!file[i + 1])
				break;
			y++;
		}
		else if (file[i] == '\t')
			x += 4;
		else if (file[i] == ' ' || file[i] == '0' || \
		file[i] == '1' || file[i] == 'N')
			x++;
		i++;
	}
	data->max_map_x = x_max;
	data->max_map_y = y;
	data->block_size_x = W / data->max_map_x;
	data->block_size_y = H / data->max_map_y;
}
