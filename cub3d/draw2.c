/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 17:25:15 by lwyss             #+#    #+#             */
/*   Updated: 2022/07/16 03:53:41 by lwyss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw(t_data *data)
{
	int		i;
	float	ray_angle;
	float	fov[61];

	ray_angle = data->player_angle - DR * 30;
	i = -1;
	while (++i < 60)
	{
		fov[i] = raycasting(data, ray_angle);
		ray_angle += DR;
	}
	fov[i] = '\0';
	if (data->print_map)
		draw_map(data);
	else
		draw_3d(data, fov);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
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
			normal_view(data, fov[i], offset, &x);
		else
			close_view(data, offset, &x);
		if (x % (W / 60) == 0)
			i++;
	}
}

void	normal_view(t_data *data, float fov, float offset, int *x)
{
	int	y;
	int	j;

	y = 0;
	j = -1;
	while (++j < H)
	{
		if (j < fov)
		{
			pixel_put(data, *x, y++, rgb(ft_atoi(data->c[0]), \
			ft_atoi(data->c[1]), ft_atoi(data->c[2])));
			j++;
		}
		else if (j > fov && j < offset)
		{
			pixel_put(data, *x, y++, rgb(ft_atoi(data->c[0]), \
			ft_atoi(data->c[1]), ft_atoi(data->c[2])));
			j++;
		}
		else
			texturing(data, *x, y++);
	}
	while (y < H)
		pixel_put(data, *x, y++, rgb(ft_atoi(data->f[0]), \
		ft_atoi(data->f[1]), ft_atoi(data->f[2])));
}

void	close_view(t_data *data, float offset, int *x)
{
	int	y;
	int	j;

	y = 0;
	j = -1;
	while (++j < H)
	{
		if (j < offset)
		{
			pixel_put(data, *x, y++, rgb(ft_atoi(data->c[0]), \
			ft_atoi(data->c[1]), ft_atoi(data->c[2])));
			j++;
		}
		else
			texturing(data, *x, y++);
	}
	while (y < H)
		pixel_put(data, *x, y++, rgb(ft_atoi(data->f[0]), \
		ft_atoi(data->f[1]), ft_atoi(data->f[2])));
}

void	draw_map(t_data *data)
{
	int		i;
	int		j;
	int		x;
	int		y;

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
	draw_player(data);
}
