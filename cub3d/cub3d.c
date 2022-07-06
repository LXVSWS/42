/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 02:54:44 by lwyss             #+#    #+#             */
/*   Updated: 2022/07/06 02:45:53 by lwyss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_3d(t_data *data, float *fov)
{
	int	x;
	int	y;
	int i = 0;

	x = -1;
	while (++x < W)
	{
		y = -1;
		while (++y < fov[i])
			pixel_put(data, x, y, rgb(255, 0, 0));
		if (x % 8 == 0)
			i++;
	}
}

float	draw_ray(t_data *data, float angle)
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
		pixel_put(data, rx, ry, rgb(0, 0, 255));
		mx = (rx += cos(angle)) / data->block_size_x;
		my = (ry += sin(angle)) / data->block_size_y;
	}
	hptn = sqrt((rx - data->player_x) * (rx - data->player_x) + (ry - data->player_y) * (ry - data->player_y));
	rx = sqrt(data->block_size_y * data->block_size_y) * H / hptn;
	if (rx > H)
		rx = H;
	return (rx);
}

void	draw_player(t_data *data, int pos_x, int pos_y, t_rgb color)
{
	int		x;
	int		y;
	float	i;
	int		j;
	float	fov[101];

	draw_element(data, pos_x, pos_y, rgb(255, 255, 255));
	x = -1;
	while (++x < 5)
	{
		y = -1;
		while (++y < 5)
			pixel_put(data, pos_x + x, pos_y + y, color);
	}
	i = data->player_angle - 0.5;
	j = 0;
	while (i < data->player_angle + 0.5)
	{
		fov[j] = (draw_ray(data, i));
		i += 0.01;
		j++;
	}
	fov[j] = '\0';
	draw_3d(data, fov);
}

int	key_hook(int keycode, t_data *data)
{
	data->player_map_x = data->player_x / data->block_size_x;
	data->player_map_y = data->player_y / data->block_size_y;
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
	if (keycode == 53)
	{
		mlx_destroy_image(data->mlx, data->img);
		mlx_destroy_window(data->mlx, data->win);
		full_free(data);
		exit(0);
	}
	draw_map(data, rgb(0, 0, 0), rgb(114, 114, 127));
	draw_player(data, data->player_x, data->player_y, rgb(255, 0, 0));
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
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
	{
		if (data->map[i][0] == '0' || \
		data->map[i][ft_strlen(data->map[i])] == '0')
			error("Map not closed");
		printf("%s\n", data->map[i++]);
	}
	data->block_size_x = W / data->max_map_x;
	data->block_size_y = H / data->max_map_y;
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
		draw_map(&data, rgb(0, 0, 0), rgb(114, 114, 127));
		data.player_delta_x = cos(data.player_angle);
		data.player_delta_y = sin(data.player_angle);
		draw_player(&data, data.player_x, data.player_y, rgb(255, 0, 0));
		mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
		mlx_key_hook(data.win, key_hook, &data);
		mlx_loop(data.mlx);
		full_free(&data);
	}
	else
		printf("Error\nArgument number invalid\n");
	return (0);
}
