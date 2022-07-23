/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 03:19:17 by lwyss             #+#    #+#             */
/*   Updated: 2022/07/23 17:34:38 by lwyss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_rgb	uinttorgb(unsigned int i)
{
	t_rgb	rgb;

	rgb.r = (i >> 16) & 0xFF;
	rgb.g = (i >> 8) & 0xFF;
	rgb.b = i & 0xFF;
	return (rgb);
}

void	draw_floor(t_data *data, int x, int y)
{
	while (y < H)
		pixel_put(data, x, y++, rgb(ft_atoi(data->f[0]), \
		ft_atoi(data->f[1]), ft_atoi(data->f[2])));
}

void	rgb_sky_check(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->c[i])
	{
		j = 0;
		while (data->c[i][j])
		{
			if (data->c[i][j] < 48 || data->c[i][j] > 57)
				error("RGB Sky value is not a number");
			j++;
		}
		if (ft_atoi(data->c[i]) >= 0 && ft_atoi(data->c[i]) <= 255)
			i++;
		else
			error("RGB Sky value incorrect");
	}
	if (i != 3)
		error("RGB Sky data incorrect");
}

void	rgb_floor_check(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->f[i])
	{
		j = 0;
		while (data->f[i][j])
		{
			if (data->f[i][j] < 48 || data->f[i][j] > 57)
				error("RGB Floor value is not a number");
			j++;
		}
		if (ft_atoi(data->f[i]) >= 0 && ft_atoi(data->f[i]) <= 255)
			i++;
		else
			error("RGB Floor value incorrect");
	}
	if (i != 3)
		error("RGB Floor data incorrect");
}

int	clean_exit(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_window(data->mlx, data->win);
	full_free(data);
	exit(0);
	return (0);
}
