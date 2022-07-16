/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 03:19:17 by lwyss             #+#    #+#             */
/*   Updated: 2022/07/16 03:54:37 by lwyss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_textures(t_data *data)
{
	int		width;
	int		height;

	data->no_img = mlx_xpm_file_to_image(data->mlx, data->no, &width, &height);
	data->so_img = mlx_xpm_file_to_image(data->mlx, data->no, &width, &height);
	data->we_img = mlx_xpm_file_to_image(data->mlx, data->no, &width, &height);
	data->ea_img = mlx_xpm_file_to_image(data->mlx, data->no, &width, &height);
}

int	clean_exit(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_window(data->mlx, data->win);
	full_free(data);
	exit(0);
	return (0);
}
