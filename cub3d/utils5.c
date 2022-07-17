/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 03:19:17 by lwyss             #+#    #+#             */
/*   Updated: 2022/07/17 21:38:34 by lwyss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_textures(t_data *data)
{
	int		width;
	int		height;

	data->no_img = mlx_xpm_file_to_image(data->mlx, data->no, &width, &height);
	if (!data->no_img)
		error("North path invalid");
	data->so_img = mlx_xpm_file_to_image(data->mlx, data->no, &width, &height);
	if (!data->no_img)
		error("South path invalid");
	data->we_img = mlx_xpm_file_to_image(data->mlx, data->no, &width, &height);
	if (!data->no_img)
		error("West path invalid");
	data->ea_img = mlx_xpm_file_to_image(data->mlx, data->no, &width, &height);
	if (!data->no_img)
		error("East path invalid");
}

t_rgb	uinttorgb(unsigned int i)
{
	t_rgb	rgb;

	rgb.r = (i >> 16) & 0xFF;
	rgb.g = (i >> 8) & 0xFF;
	rgb.b = i & 0xFF;
	return (rgb);
}

int	clean_exit(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_window(data->mlx, data->win);
	full_free(data);
	exit(0);
	return (0);
}
