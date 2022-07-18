/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 03:58:51 by lwyss             #+#    #+#             */
/*   Updated: 2022/07/18 19:22:18 by lwyss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_ray	raycasting(t_data *data, float angle)
{
	float	rx;
	float	ry;
	int		mx;
	int		my;
	float	hptn;
	t_ray	ray;

	rx = data->player_x;
	ry = data->player_y;
	mx = rx / data->block_size_x;
	my = ry / data->block_size_y;
	while (data->map[my][mx] == '0')
	{
		rx += cos(angle);
		ry += sin(angle);
		mx = rx / data->block_size_x;
		my = ry / data->block_size_y;
	}
	ray.angle = angle;
	ray.hit_x = rx / data->block_size_x - mx;
	ray.hit_y = ry / data->block_size_y - my;
	hptn = sqrt((rx - data->player_x) * (rx - data->player_x) + \
	(ry - data->player_y) * (ry - data->player_y));
	hptn = fix_fish_eye(data, angle, hptn);
	rx = sqrt(data->block_size_y * data->block_size_y) * H / hptn;
	if (rx > H)
		rx = H;
	ray.wall_h = rx;
	return (ray);
}

/*
		h_txtr (px)		= h_wall (px)
		y (txtr) (px)	= y (wall) (px)

		w_txtr (px)		= w_wall (1)
		x_txtr (px)		= x_wall (ray hit)
*/

void	texturing(t_data *data, t_ray ray, int x, int y)
{
	int				x_tex;
	int				y_tex;
	unsigned int	color;

	data->tex.no_addr = mlx_get_data_addr(data->tex.no, &data->tex.no_bpp, &data->tex.no_ll, &data->tex.no_endian);
	x_tex = ray.hit_x * data->tex.no_w / 1;
	y_tex = ray.hit_y * data->tex.no_h / ray.wall_h;
	if (x_tex >= data->tex.no_w || y_tex >= data->tex.no_h)
		error("Texture overflow");
	color = *(unsigned int *)(data->tex.no_addr + x_tex * data->tex.no_ll + y_tex);
	pixel_put(data, x, y, uinttorgb(color));
	//pixel_put(data, x, y, rgb(255, 0, 0));
}

void	strafing(t_data *data, int keycode)
{
	if (keycode == 0)
	{
		if (data->player_angle >= 4 && data->player_angle <= 6)
			data->player_x -= 5;
		else if (data->player_angle >= 2 && data->player_angle < 4)
			data->player_y += 5;
		else if (data->player_angle > 6 || data->player_angle < 1)
			data->player_y -= 5;
		else
			data->player_x += 5;
	}
	if (keycode == 2)
	{
		if (data->player_angle >= 4 && data->player_angle <= 6)
			data->player_x += 5;
		else if (data->player_angle >= 2 && data->player_angle < 4)
			data->player_y -= 5;
		else if (data->player_angle > 6 || data->player_angle < 1)
			data->player_y += 5;
		else
			data->player_x -= 5;
	}
}

void	rgb_check(t_data *data)
{
	int	i;

	i = 0;
	while (data->c[i])
		i++;
	if (i != 3)
		error("RGB Sky data incorrect");
	i = 0;
	while (data->f[i])
		i++;
	if (i != 3)
		error("RGB Floor data incorrect");
}

int	ft_atoi(const char *s)
{
	int	i;
	int	neg;
	int	res;

	i = 0;
	neg = 0;
	res = 0;
	while (s[i] == '\v' || s[i] == '\n' || s[i] == '\t' \
	|| s[i] == '\r' || s[i] == '\f' || s[i] == ' ')
		i++;
	if (s[i] == '-' && (s[i + 1] >= '0' && s[i] <= '9'))
	{
		neg++;
		i++;
	}
	if (s[i] == '+' && (s[i + 1] >= '0' && s[i] <= '9'))
		i++;
	while (s[i] >= '0' && s[i] <= '9')
	{
		res *= 10;
		res += (s[i++] - 48);
	}
	if (neg == 1)
		return (-res);
	return (res);
}
