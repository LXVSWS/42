/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 17:55:04 by lwyss             #+#    #+#             */
/*   Updated: 2022/07/11 18:22:06 by lwyss            ###   ########.fr       */
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
	while (data->map[i])
	{
		if (data->map[i][0] == '0' || \
		data->map[i][ft_strlen(data->map[i])] == '0')
			error("Map not closed");
		i++;
	}
	data->block_size_x = W / data->max_map_x;
	data->block_size_y = H / data->max_map_y;
}

void	init_player(t_data *data, int x, int y)
{
	data->player_x = x;
	data->player_y = y;
	data->player_delta_x = cos(data->player_angle);
	data->player_delta_y = sin(data->player_angle);
}

void	detect_player(t_data *data)
{
	int	i;
	int	j;
	int	x;
	int	y;

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

float	fix_fish_eye(t_data *data, float angle, float hptn)
{
	float	fish_eye;

	fish_eye = data->player_angle - angle;
	hptn *= cos(fish_eye);
	return (hptn);
}
