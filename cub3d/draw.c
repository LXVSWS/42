/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 02:53:31 by lwyss             #+#    #+#             */
/*   Updated: 2022/07/13 18:42:49 by lwyss            ###   ########.fr       */
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

void	draw_player(t_data *data)
{
	int		x;
	int		y;
	float	ray_angle;
	int		i;

	ray_angle = data->player_angle - DR * 30;
	i = -1;
	while (++i < 60)
	{
		draw_rays(data, ray_angle);
		ray_angle += DR;
	}
	x = -1;
	while (++x < 3)
	{
		y = -1;
		while (++y < 3)
			pixel_put(data, x + data->player_x, y + \
			data->player_y, rgb(255, 0, 0));
	}
}

void	draw_rays(t_data *data, float angle)
{
	float	rx;
	float	ry;
	int		mx;
	int		my;

	rx = data->player_x;
	ry = data->player_y;
	mx = rx / data->block_size_x;
	my = ry / data->block_size_y;
	while (data->map[my][mx] == '0')
	{
		pixel_put(data, rx, ry, rgb(0, 0, 255));
		rx += cos(angle);
		ry += sin(angle);
		mx = rx / data->block_size_x;
		my = ry / data->block_size_y;
	}
}
