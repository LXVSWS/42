/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 02:43:20 by lwyss             #+#    #+#             */
/*   Updated: 2022/06/19 06:15:45 by lwyss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	file_read(char **av)
{
	int	size;
	int	fd;

	size = ft_strlen(av[1]);
	if (av[1][size - 1] != 'b' || av[1][size - 2] != 'u' \
	|| av[1][size - 3] != 'c' || av[1][size - 4] != '.')
		error("Wrong file extension");
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

char	*file_copy(int fd, int size)
{
	char	*file;
	int		bytes_read;
	char	buf;

	file = malloc(sizeof(char) * size + 1);
	if (!file)
		error("Malloc file copy failed");
	file[size] = 0;
	size = 0;
	bytes_read = 1;
	while (bytes_read)
	{
		bytes_read = read(fd, &buf, 1);
		if (bytes_read == -1)
			error("Problem while reading file");
		file[size] = buf;
		size++;
	}
	close(fd);
	return (file);
}

void	check_incorrect_input(t_data *data, char c)
{
	if (c != '\t' && c != '\n' && c != ' ' \
	&& c != '0' && c != '1' && c != 'N' \
	&& c != 'S' && c != 'E' && c != 'W')
		error("Incorrect character");
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (!data->starting_pos)
			data->starting_pos = c;
		else
			error("Multiple players detected");
	}
}

void	check_map(t_data *data, char *file)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while (file[i])
	{
		check_incorrect_input(data, file[i]);
		if (file[i] == '\n')
		{
			if (file[i + 1] && file[i + 1] == '\n' && file[i + 2])
				error("Multiple empty lines in map");
			if (x > data->max_map_x)
				data->max_map_x = x;
			x = 0;
			if (!file[i + 1])
				break ;
			data->max_map_y++;
		}
		else if (file[i] == '\t')
			x += 4;
		else
			x++;
		i++;
	}
}
