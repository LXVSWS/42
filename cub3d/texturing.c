/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texturing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 15:42:36 by lwyss             #+#    #+#             */
/*   Updated: 2022/07/20 20:30:15 by lwyss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
		h_txtr (px)		= h_wall (px)
		y (txtr) (px)	= y (wall) (px)

		w_txtr (px)		= w_wall (1)
		x_txtr (px)		= x_wall (ray hit)
*/

unsigned int	north_side(t_data *data, t_ray *ray, int x, int y)
{
	int				x_tex;
	int				y_tex;
	unsigned int	color;

	x_tex = (x - ray->hit_x) * data->tex.no_w / FOV;
	y_tex = (y - ray->y_offset) * data->tex.no_h / ray->wall_h;
	data->tex.no_addr = mlx_get_data_addr(data->tex.no, \
	&data->tex.no_bpp, &data->tex.no_ll, &data->tex.no_endian);
	color = *(unsigned int *)(data->tex.no_addr + \
	y_tex * data->tex.no_ll + x_tex);
	return (color);
}

unsigned int	south_side(t_data *data, t_ray *ray, int x, int y)
{
	int				x_tex;
	int				y_tex;
	unsigned int	color;

	x_tex = (x - ray->hit_x) * data->tex.so_w / FOV;
	y_tex = (y - ray->y_offset) * data->tex.so_h / ray->wall_h;
	data->tex.so_addr = mlx_get_data_addr(data->tex.so, \
	&data->tex.so_bpp, &data->tex.so_ll, &data->tex.so_endian);
	color = *(unsigned int *)(data->tex.so_addr + \
	y_tex * data->tex.so_ll + x_tex);
	//printf("x_tex : %i / y_tex : %i / x : %i\n", x_tex, y_tex, x);
	return (color);
}

unsigned int	east_side(t_data *data, t_ray *ray, int x, int y)
{
	int				x_tex;
	int				y_tex;
	unsigned int	color;

	x_tex = (x - ray->hit_y) * data->tex.ea_w / FOV;
	y_tex = (y - ray->y_offset) * data->tex.ea_h / ray->wall_h;
	data->tex.ea_addr = mlx_get_data_addr(data->tex.ea, \
	&data->tex.ea_bpp, &data->tex.ea_ll, &data->tex.ea_endian);
	color = *(unsigned int *)(data->tex.ea_addr + \
	y_tex * data->tex.ea_ll + x_tex);
	return (color);
}

unsigned int	west_side(t_data *data, t_ray *ray, int x, int y)
{
	int				x_tex;
	int				y_tex;
	unsigned int	color;

	x_tex = (x - ray->hit_y) * data->tex.we_w / FOV;
	y_tex = (y - ray->y_offset) * data->tex.we_h / ray->wall_h;
	data->tex.we_addr = mlx_get_data_addr(data->tex.we, \
	&data->tex.we_bpp, &data->tex.we_ll, &data->tex.we_endian);
	color = *(unsigned int *)(data->tex.we_addr + \
	y_tex * data->tex.we_ll + x_tex);
	return (color);
}
