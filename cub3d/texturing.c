/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texturing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 15:42:36 by lwyss             #+#    #+#             */
/*   Updated: 2022/07/23 17:33:46 by lwyss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_textures(t_data *data)
{
	t_tex	tex;

	tex.no = mlx_xpm_file_to_image(data->mlx, data->no, &tex.no_w, &tex.no_h);
	if (!tex.no)
		error("North texture invalid");
	tex.so = mlx_xpm_file_to_image(data->mlx, data->so, &tex.so_w, &tex.so_h);
	if (!tex.so)
		error("South tex invalid");
	tex.we = mlx_xpm_file_to_image(data->mlx, data->we, &tex.we_w, &tex.we_h);
	if (!tex.we)
		error("West tex invalid");
	tex.ea = mlx_xpm_file_to_image(data->mlx, data->ea, &tex.ea_w, &tex.ea_h);
	if (!tex.ea)
		error("East tex invalid");
	data->tex = tex;
}

unsigned int	north_side(t_data *data, t_ray *ray, int x, int y)
{
	int				x_tex;
	int				y_tex;
	unsigned int	color;

	x_tex = x - ray->hit_x * data->tex.so_w / W;
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

	x_tex = x - ray->hit_x * data->tex.so_w / W;
	y_tex = (y - ray->y_offset) * data->tex.so_h / ray->wall_h;
	data->tex.so_addr = mlx_get_data_addr(data->tex.so, \
	&data->tex.so_bpp, &data->tex.so_ll, &data->tex.so_endian);
	color = *(unsigned int *)(data->tex.so_addr + \
	y_tex * data->tex.so_ll + x_tex);
	return (color);
}

unsigned int	east_side(t_data *data, t_ray *ray, int x, int y)
{
	int				x_tex;
	int				y_tex;
	unsigned int	color;

	x_tex = x - ray->hit_y * data->tex.so_w / W;
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

	x_tex = x - ray->hit_y * data->tex.so_w / W;
	y_tex = (y - ray->y_offset) * data->tex.we_h / ray->wall_h;
	data->tex.we_addr = mlx_get_data_addr(data->tex.we, \
	&data->tex.we_bpp, &data->tex.we_ll, &data->tex.we_endian);
	color = *(unsigned int *)(data->tex.we_addr + \
	y_tex * data->tex.we_ll + x_tex);
	return (color);
}
