/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 07:28:56 by lwyss             #+#    #+#             */
/*   Updated: 2022/08/04 21:27:32 by lwyss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*strdupmod(char *s)
{
	int		i;
	int		size;
	char	*str;

	i = 0;
	size = 0;
	while (s[i] && s[i] != '\n')
	{
		if (s[i] != ' ' && s[i] != '\t')
			size++;
		i++;
	}
	str = malloc(sizeof(char) * size + 1);
	str[size] = 0;
	i = 0;
	size = 0;
	while (s[i] && s[i] != '\n')
	{
		if (s[i] == ' ' || s[i] == '\t')
			i++;
		else
			str[size++] = s[i++];
	}
	return (str);
}

int	check_file(t_data *data, char *file)
{
	int	i;

	i = 0;
	while (file[i])
	{
		if (file[i] == 'N' && file[i + 1] == 'O' && (!file[i - 1] || \
		file[i - 1] == '\n' || file[i - 1] == '\t' || file[i - 1] == ' ') && \
		(file[i + 2] == ' ' || file[i + 2] == '\t'))
			no_detected(data, &file[i + 2]);
		else if (file[i] == 'S' && file[i + 1] == 'O' && (!file[i - 1] || \
		file[i - 1] == '\n' || file[i - 1] == '\t' || file[i - 1] == ' ') && \
		(file[i + 2] == ' ' || file[i + 2] == '\t'))
			so_detected(data, &file[i + 2]);
		else if (file[i] == 'W' && file[i + 1] == 'E' && (!file[i - 1] || \
		file[i - 1] == '\n' || file[i - 1] == '\t' || file[i - 1] == ' ') && \
		(file[i + 2] == ' ' || file[i + 2] == '\t'))
			we_detected(data, &file[i + 2]);
		else if (file[i] == 'E' && file[i + 1] == 'A' && (!file[i - 1] || \
		file[i - 1] == '\n' || file[i - 1] == '\t' || file[i - 1] == ' ') && \
		(file[i + 2] == ' ' || file[i + 2] == '\t'))
			ea_detected(data, &file[i + 2]);
		else if (file[i] == 'F' && (!file[i - 1] || file[i - 1] == '\n' || \
		file[i - 1] == '\t' || file[i - 1] == ' ') && \
		(file[i + 1] == ' ' || file[i + 1] == '\t'))
			f_detected(data, &file[i + 1]);
		else if (file[i] == 'C' && (!file[i - 1] || file[i - 1] == '\n' || \
		file[i - 1] == '\t' || file[i - 1] == ' ') && \
		(file[i + 1] == ' ' || file[i + 1] == '\t'))
			c_detected(data, &file[i + 1]);
		if (data->no && data->so && data->we && data->ea && data->f && data->c)
			break ;
		i++;
	}
	if (!data->no || !data->so || !data->we \
	|| !data->ea || !data->f || !data->c)
		error("Invalid/missing data");
	return (i);
}

int	detect_map(char *file, int i)
{
	while (file[i] && file[i] != '\n')
		i++;
	while (file[i] && file[i] == '\n')
		i++;
	if (!file[i])
		error("No map detected");
	return (i);
}

void	malloc_map(t_data *data)
{
	int		i;
	int		j;

	rgb_sky_check(data);
	rgb_floor_check(data);
	if (!data->starting_pos)
		error("Map has no player");
	data->map = malloc(sizeof(char *) * (data->max_map_y + 1));
	if (!data->map)
		error("Malloc failed");
	data->map[data->max_map_y] = NULL;
	i = 0;
	j = 0;
	while (i < data->max_map_y)
	{
		data->map[i] = malloc(sizeof(char) * data->max_map_x + 1);
		if (!data->map[i])
			error("Malloc failed");
		data->map[i][data->max_map_x] = 0;
		while (j < data->max_map_x)
			data->map[i][j++] = '0';
		j = 0;
		i++;
	}
}

void	full_free(t_data *data)
{
	int	i;

	if (data->no)
		free(data->no);
	if (data->so)
		free(data->so);
	if (data->we)
		free(data->we);
	if (data->ea)
		free(data->ea);
	i = 0;
	while (data->f[i])
		free(data->f[i++]);
	if (data->f)
		free(data->f);
	i = 0;
	while (data->c[i])
		free(data->c[i++]);
	if (data->c)
		free(data->c);
	i = 0;
	while (data->map[i])
		free(data->map[i++]);
	if (data->map)
		free(data->map);
}
