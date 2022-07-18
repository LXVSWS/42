/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 02:05:51 by lwyss             #+#    #+#             */
/*   Updated: 2022/07/18 18:40:02 by lwyss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_data	init(void)
{
	t_data	data;

	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, W, H, "cub3d");
	data.img = mlx_new_image(data.mlx, W, H);
	data.addr = mlx_get_data_addr(data.img, &data.bpp, &data.ll, &data.endian);
	data.no = NULL;
	data.so = NULL;
	data.we = NULL;
	data.ea = NULL;
	data.f = NULL;
	data.c = NULL;
	data.map = NULL;
	data.starting_pos = NULL;
	data = init2(data);
	return (data);
}

t_data	init2(t_data data)
{
	data.direction = 0;
	data.print_map = 0;
	data.max_map_x = 0;
	data.max_map_y = 0;
	data.player_map_x = 0;
	data.player_map_y = 0;
	data.block_size_x = 0;
	data.block_size_y = 0;
	data.player_x = 0;
	data.player_y = 0;
	data.player_delta_x = 0;
	data.player_delta_y = 0;
	data.player_angle = 0;
	return (data);
}

t_rgb	rgb(unsigned char r, unsigned char g, unsigned char b)
{
	t_rgb	rgb;

	rgb.r = r;
	rgb.g = g;
	rgb.b = b;
	return (rgb);
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i])
			i++;
	}
	return (i);
}

void	error(char *s)
{
	printf("Error\n%s\n", s);
	exit(-1);
}
