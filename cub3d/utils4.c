/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 03:58:51 by lwyss             #+#    #+#             */
/*   Updated: 2022/07/20 23:17:36 by lwyss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_ray	raycasting(t_data *data, float angle)
{
	t_ray	ray;

	ray.rx = data->player_x;
	ray.ry = data->player_y;
	ray.mx = ray.rx / data->block_size_x;
	ray.my = ray.ry / data->block_size_y;
	while (data->map[ray.my][ray.mx] == '0')
	{
		ray.rx += cos(angle);
		ray.ry += sin(angle);
		ray.mx = ray.rx / data->block_size_x;
		ray.my = ray.ry / data->block_size_y;
	}
	init_textures_sides(data, &ray, angle);
	ray.hit_x = ray.rx / data->block_size_x - ray.mx;
	ray.hit_y = ray.ry / data->block_size_y - ray.my;
	ray.y_offset = 0;
	ray.wall_h = pythagore(data, ray.rx, ray.ry, angle);
	return (ray);
}

void	texturing(t_data *data, t_ray ray, int x, int y)
{
	unsigned int	color;

	color = 0;
	if (ray.side == 'N')
		color = north_side(data, &ray, x, y);
	else if (ray.side == 'S')
		color = south_side(data, &ray, x, y);
	else if (ray.side == 'E')
		color = east_side(data, &ray, x, y);
	else if (ray.side == 'W')
		color = west_side(data, &ray, x, y);
	pixel_put(data, x, y, uinttorgb(color));
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
