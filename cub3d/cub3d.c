/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 02:54:44 by lwyss             #+#    #+#             */
/*   Updated: 2022/07/26 05:44:38 by lwyss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	movement(int keycode, t_data *data)
{
	float	previous_pos_x;
	float	previous_pos_y;

	previous_pos_x = data->player_x;
	previous_pos_y = data->player_y;
	if (keycode == 13)
	{
		data->player_x += data->player_delta_x * 5;
		data->player_y += data->player_delta_y * 5;
	}
	if (keycode == 1)
	{
		data->player_x -= data->player_delta_x * 5;
		data->player_y -= data->player_delta_y * 5;
	}
	if (keycode == 0 || keycode == 2)
		strafing(data, keycode);
	data->player_map_x = data->player_x / data->block_size_x;
	data->player_map_y = data->player_y / data->block_size_y;
	if (data->map[data->player_map_y][data->player_map_x] == '1')
	{
		data->player_x = previous_pos_x;
		data->player_y = previous_pos_y;
	}
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

static int	hook(int keycode, t_data *data)
{
	if (keycode == 13 || keycode == 0 || keycode == 1 || keycode == 2)
		movement(keycode, data);
	if (keycode == 123 || keycode == 124)
		rotation(keycode, data);
	draw(data);
	return (0);
}

static int	key_hook(int keycode, t_data *data)
{
	if (keycode == 41) // 46 for QWERTY
	{
		if (!data->print_map)
			data->print_map = 1;
		else
			data->print_map = 0;
		draw(data);
	}
	if (keycode == 53)
		clean_exit(data);
	return (0);
}

int	main(int ac, char **av)
{
	t_data		data;
	char		*file;
	int			i;

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
		init_textures(&data);
		draw(&data);
		mlx_hook(data.win, 2, 1L << 0, hook, &data);
		mlx_hook(data.win, 17, 0L, clean_exit, &data);
		mlx_key_hook(data.win, key_hook, &data);
		mlx_loop(data.mlx);
		full_free(&data);
	}
	else
		printf("Error\nArgument number invalid\n");
	return (0);
}
