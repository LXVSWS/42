/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 02:53:31 by lwyss             #+#    #+#             */
/*   Updated: 2022/07/10 18:17:29 by lwyss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	rgb2int(t_rgb rgb)
{
	return (rgb.r << 16 | rgb.g << 8 | rgb.b);
}

void	pixel_put(t_data *data, int x, int y, t_rgb rgb)
{
	char	*dst;

	if (x < 0 || x >= W || y < 0 || y >= H)
		return ;
	dst = data->addr + (y * data->ll + x * (data->bpp / 8));
	*(unsigned int *)dst = rgb2int(rgb);
}

void	draw_element(t_data *data, int pos_x, int pos_y, t_rgb color)
{
	int	x;
	int	y;

	x = -1;
	while (++x < data->block_size_x)
	{
		y = -1;
		while (++y < data->block_size_y)
			pixel_put(data, x + pos_x, y + pos_y, color);
	}
}

void	init_player(t_data *data, int x, int y)
{
	data->player_x = x;
	data->player_y = y;
}

void	draw_map(t_data *data, t_rgb color_wall, t_rgb color_void)
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
			else if (data->map[i][j] == '1')
				draw_element(data, x, y, color_wall);
			else
				draw_element(data, x, y, color_void);
			x += data->block_size_x;
		}
		j = -1;
		x = 0;
		y += data->block_size_y;
	}
}
