/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 03:58:51 by lwyss             #+#    #+#             */
/*   Updated: 2022/07/17 22:03:26 by lwyss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	raycasting(t_data *data, float angle)
{
	float	rx;
	float	ry;
	int		mx;
	int		my;
	float	hptn;

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
	hptn = sqrt((rx - data->player_x) * (rx - data->player_x) + \
	(ry - data->player_y) * (ry - data->player_y));
	hptn = fix_fish_eye(data, angle, hptn);
	rx = sqrt(data->block_size_y * data->block_size_y) * H / hptn;
	if (rx > H)
		rx = H;
	return (rx);
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

/*
		h_txtr (px)		= h_wall (px)
		y (txtr) (px)	= y (wall) (px)

		w_txtr (px)		= w_wall (1)
		x_txtr (px)		= x_wall (ray hit)
*/

void	texturing(t_data *data, float fov, int x, int y)
{
	char			*addr;
	int				bpp;
	int				ll;
	int				endian;
	unsigned int	color;
	int				x_texture;
	int				y_texture;

	addr = mlx_get_data_addr(data->no_img, &bpp, &ll, &endian);
	x_texture = x * data->block_size_x / fov;
	y_texture = y * data->block_size_y / fov;
	color = *(unsigned int *)(addr + y_texture * ll + x_texture);
	pixel_put(data, x, y, uinttorgb(color));
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
