/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 17:55:04 by lwyss             #+#    #+#             */
/*   Updated: 2022/08/04 21:30:14 by lwyss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	mapdup(t_data *data, char c, int *j, int *k)
{
	if (c == ' ' || c == '1')
		data->map[*j][(*k)++] = '1';
	else if (c == '\n')
	{
		while (*k < data->max_map_x)
			data->map[*j][(*k)++] = '1';
		(*j)++;
		*k = 0;
	}
	else if (c == '\t')
	{
		data->map[*j][(*k)++] = '1';
		data->map[*j][(*k)++] = '1';
		data->map[*j][(*k)++] = '1';
		data->map[*j][(*k)++] = '1';
	}
	else if (c == 'N' || c == 'S' || \
	c == 'E' || c == 'W')
	{
		data->starting_pos = &data->map[*j][(*k)++];
		data->direction = c;
	}
	else
		(*k)++;
}

void	copy_map(t_data *data, char *file)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (file[i] && data->map[j])
		mapdup(data, file[i++], &j, &k);
	i = 0;
	j = 0;
	while (data->map[i])
	{
		while (data->map[0][j])
			if (data->map[0][j++] != '1')
				error("Map not closed");
		if (data->map[i][0] == '0' || data->map[i][strln(data->map[i])] == '0')
			error("Map not closed");
		i++;
	}
}

void	init_player(t_data *data, int x, int y)
{
	data->player_x = x;
	data->player_y = y;
	if (data->direction == 'N')
		data->player_angle = PI * 1.5;
	if (data->direction == 'S')
		data->player_angle = PI * 0.5;
	if (data->direction == 'E')
		data->player_angle = PI;
	data->player_delta_x = cos(data->player_angle);
	data->player_delta_y = sin(data->player_angle);
}

void	detect_player(t_data *data)
{
	int	i;
	int	j;
	int	x;
	int	y;

	data->block_size_x = W / data->max_map_x;
	data->block_size_y = H / data->max_map_y;
	i = -1;
	j = -1;
	x = 0;
	y = 0;
	while (data->map[++i])
	{
		while (data->map[i][++j])
		{
			if (!data->player_x && &data->map[i][j] == data->starting_pos)
				init_player(data, x, y);
			x += data->block_size_x;
		}
		j = -1;
		x = 0;
		y += data->block_size_y;
	}
}

float	pythagore(t_data *data, float rx, float ry, float angle)
{
	float	hptn;
	float	fix_fish_eye;

	hptn = sqrt((rx - data->player_x) * (rx - data->player_x) + \
	(ry - data->player_y) * (ry - data->player_y));
	fix_fish_eye = data->player_angle - angle;
	hptn *= cos(fix_fish_eye);
	rx = sqrt(data->block_size_y * data->block_size_y) * H / hptn;
	if (rx > H)
		rx = H;
	return (rx);
}
