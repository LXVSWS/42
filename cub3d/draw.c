/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 02:53:31 by lwyss             #+#    #+#             */
/*   Updated: 2022/07/11 15:19:45 by lwyss            ###   ########.fr       */
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
		mx = (rx += cos(angle)) / data->block_size_x;
		my = (ry += sin(angle)) / data->block_size_y;
	}
}

void	draw_map(t_data *data)
{
	int	i;
	int	j;
	int	x;
	int	y;
	float	ray_angle;

	i = -1;
	j = -1;
	x = 0;
	y = 0;
	while (data->map[++i])
	{
		while (data->map[i][++j])
		{
			if (data->map[i][j] == '1')
				draw_element(data, x, y, rgb(0, 0, 0));
			else
				draw_element(data, x, y, rgb(114, 114, 127));
			x += data->block_size_x;
		}
		j = -1;
		x = 0;
		y += data->block_size_y;
	}
	draw_element(data, data->player_x, data->player_y, rgb(255, 255, 255));
	ray_angle = data->player_angle - DR * 30;
	i = -1;
	while (++i < 60)
	{
		draw_rays(data, ray_angle);
		ray_angle += DR;
	}
}

void	draw_3d(t_data *data, float *fov)
{
	int		x;
	int		y;
	int		i;
	int		j;
	float	offset;

	x = -1;
	i = 0;
	while (++x < W && fov[i])
	{
		offset = H - fov[i];
		y = 0;
		j = -1;
		if (fov[i] < offset)
		{
			while (++j < H)
			{
				if (j < fov[i])
				{
					pixel_put(data, x, y, rgb(0, 0, 255));
					j++;
				}
				else if (j > fov[i] && j < offset)
				{
					pixel_put(data, x, y, rgb(0, 0, 255));
					j++;
				}
				else
					pixel_put(data, x, y, rgb(255, 0, 0));
				y++;
			}
			while (y < H)
				pixel_put(data, x, y++, rgb(0, 255, 0));
		}
		else
		{
			while (++j < H)
			{
				if (j < offset)
				{
					pixel_put(data, x, y, rgb(0, 0, 255));
					j++;
				}
				else
					pixel_put(data, x, y, rgb(255, 0, 0));
				y++;
			}
			while (y < H)
				pixel_put(data, x, y++, rgb(0, 255, 0));
		}
		if (x % (W / 60) == 0)
			i++;
	}
}
