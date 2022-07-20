/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 17:25:15 by lwyss             #+#    #+#             */
/*   Updated: 2022/07/20 16:30:54 by lwyss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	draw(t_data *data)
{
	int		i;
	float	ray_angle;
	t_ray	ray[FOV];

	ray_angle = data->player_angle - DR * 30;
	i = -1;
	while (++i < FOV)
	{
		ray[i] = raycasting(data, ray_angle);
		ray_angle += DR;
	}
	if (data->print_map)
		draw_map(data);
	else
		draw_3d(data, ray);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}

void	draw_3d(t_data *data, t_ray *ray)
{
	int		x;
	int		y;
	int		i;
	int		j;
	float	offset;

	x = -1;
	i = 0;
	while (++x < W && i < FOV)
	{
		offset = H - ray[i].wall_h;
		y = 0;
		j = -1;
		if (ray[i].wall_h < offset)
			normal_view(data, ray[i], offset, &x);
		else
			close_view(data, ray[i], offset, &x);
		ray[i].x_offset++;
		if (x % (W / FOV) == 0)
			i++;
	}
}

void	normal_view(t_data *data, t_ray ray, float offset, int *x)
{
	int	y;
	int	j;

	y = 0;
	j = -1;
	while (++j < H)
	{
		if (j < ray.wall_h)
		{
			pixel_put(data, *x, y++, rgb(ft_atoi(data->c[0]), \
			ft_atoi(data->c[1]), ft_atoi(data->c[2])));
			ray.y_offset++;
			j++;
		}
		else if (j > ray.wall_h && j < offset)
		{
			pixel_put(data, *x, y++, rgb(ft_atoi(data->c[0]), \
			ft_atoi(data->c[1]), ft_atoi(data->c[2])));
			ray.y_offset++;
			j++;
		}
		else
			texturing(data, ray, *x, y++);
	}
	draw_floor(data, *x, y);
}

void	close_view(t_data *data, t_ray ray, float offset, int *x)
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
			ray.y_offset++;
		}
		else
			texturing(data, ray, *x, y++);
	}
	draw_floor(data, *x, y);
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
