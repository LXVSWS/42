/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 02:54:44 by lwyss             #+#    #+#             */
/*   Updated: 2022/07/12 03:55:55 by lwyss            ###   ########.fr       */
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

static void	movement(int keycode, t_data *data)
{
	if (keycode == 13)
		if (data->player_map_y > 0 && \
		data->map[data->player_map_y - 1][data->player_map_x] == '0')
			data->player_y -= data->block_size_y;
	if (keycode == 0)
		if (data->player_map_x > 0 && \
		data->map[data->player_map_y][data->player_map_x - 1] == '0')
			data->player_x -= data->block_size_x;
	if (keycode == 1)
		if (data->player_map_y < data->max_map_y - 1 && \
		data->map[data->player_map_y + 1][data->player_map_x] == '0')
			data->player_y += data->block_size_y;
	if (keycode == 2)
		if (data->player_map_x < data->max_map_x && \
		data->map[data->player_map_y][data->player_map_x + 1] == '0')
			data->player_x += data->block_size_x;
}

static void	rotation(int keycode, t_data *data)
{
	if (keycode == 123)
	{
		data->player_angle -= 0.1;
		if (data->player_angle < 0)
			data->player_angle += 2 * PI;
		data->player_delta_x = cos(data->player_angle);
		data->player_delta_y = sin(data->player_angle);
	}
	if (keycode == 124)
	{
		data->player_angle += 0.1;
		if (data->player_angle > 2 * PI)
			data->player_angle -= 2 * PI;
		data->player_delta_x = cos(data->player_angle);
		data->player_delta_y = sin(data->player_angle);
	}
}

static int	key_hook(int keycode, t_data *data)
{
	data->player_map_x = data->player_x / data->block_size_x;
	data->player_map_y = data->player_y / data->block_size_y;
	if (keycode == 13 || keycode == 0 || keycode == 1 || keycode == 2)
		movement(keycode, data);
	if (keycode == 123 || keycode == 124)
		rotation(keycode, data);
	if (keycode == 41)
	{
		if (!data->print_map)
			data->print_map = 1;
		else
			data->print_map = 0;
	}
	if (keycode == 53)
	{
		mlx_destroy_image(data->mlx, data->img);
		mlx_destroy_window(data->mlx, data->win);
		full_free(data);
		exit(0);
	}
	draw(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;
	char	*file;
	int		i;

	if (ac == 2)
	{
		data = init();
		file = file_copy(file_read(av), file_size(file_read(av)));
		i = detect_map(file, check_file(&data, file));
		check_map(&data, &file[i]);
		malloc_map(&data);
		copy_map(&data, &file[i]);
		free(file);
		detect_player(&data);
		draw(&data);
		mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
		mlx_key_hook(data.win, key_hook, &data);
		mlx_loop(data.mlx);
	}
	else
		printf("Error\nArgument number invalid\n");
	full_free(&data);
	return (0);
}
