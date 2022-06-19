/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 02:54:44 by lwyss             #+#    #+#             */
/*   Updated: 2022/06/19 17:33:58 by lwyss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_hook(int keycode, t_data *data)
{
	if (keycode == 13)
		data->player_y -= data->block_size_y;
	if (keycode == 0)
		data->player_x -= data->block_size_x;
	if (keycode == 1)
		data->player_y += data->block_size_y;
	if (keycode == 2)
		data->player_x += data->block_size_x;
	if (keycode == 53)
	{
		mlx_destroy_image(data->mlx, data->img);
		mlx_destroy_window(data->mlx, data->win);
		full_free(data);
		exit(0);
	}
	check_movement(data);
	draw_element(data, data->player_x, data->player_y, rgb(255, 255, 255));
	return (0);
}

void	mapdup(t_data *data, char c, int *j, int *k)
{
	if (c == ' ' || c == '1')
		data->map[*j][(*k)++] = '1';
	else if (c == '\n')
	{
		while (*k < data->max_map_x)
			data->map[*j][(*k)++] = '1';
		(*j)++;
		*k = 0;
	}
	else if (c == '\t')
	{
		data->map[*j][(*k)++] = '1';
		data->map[*j][(*k)++] = '1';
		data->map[*j][(*k)++] = '1';
		data->map[*j][(*k)++] = '1';
	}
	else if (c == 'N' || c == 'S' || \
	c == 'E' || c == 'W')
	{
		data->starting_pos = &data->map[*j][(*k)++];
		data->direction = c;
	}
	else
		(*k)++;
}

void	copy_map(t_data *data, char *file)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (file[i] && data->map[j])
		mapdup(data, file[i++], &j, &k);
	printf("%s\n%s\n%s\n%s\n%s\n%s\n", \
	data->no, data->so, data->we, data->ea, data->f, data->c);
	i = 0;
	while (data->map[i])
		printf("%s\n", data->map[i++]);
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
		data.block_size_x = W / data.max_map_x;
		data.block_size_y = H / data.max_map_y;
		draw_map(&data, rgb(0, 0, 0), rgb(114, 114, 127));
		draw_element(&data, data.player_x, data.player_y, rgb(255, 255, 255));
		mlx_key_hook(data.win, key_hook, &data);
		mlx_loop(data.mlx);
		full_free(&data);
	}
	else
		printf("Error\nArgument number invalid\n");
	return (0);
}
