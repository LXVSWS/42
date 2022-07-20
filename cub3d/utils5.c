/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 03:19:17 by lwyss             #+#    #+#             */
/*   Updated: 2022/07/20 16:07:54 by lwyss            ###   ########.fr       */
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

void	init_textures_sides(t_data *data, t_ray *ray, float angle)
{
	if ((int)((ray->ry - sin(angle)) / data->block_size_y) > ray->my)
		ray->side = 'S';
	else if ((int)((ray->ry - sin(angle)) / data->block_size_y) < ray->my)
		ray->side = 'N';
	else if ((int)((ray->rx - cos(angle)) / data->block_size_x) > ray->mx)
		ray->side = 'E';
	else if ((int)((ray->rx - cos(angle)) / data->block_size_x) < ray->mx)
		ray->side = 'W';
}

int	clean_exit(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_window(data->mlx, data->win);
	full_free(data);
	exit(0);
	return (0);
}
