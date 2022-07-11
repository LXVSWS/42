/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 02:54:44 by lwyss             #+#    #+#             */
/*   Updated: 2022/07/11 15:24:44 by lwyss            ###   ########.fr       */
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
	float	fish_eye;

	rx = data->player_x;
	ry = data->player_y;
	mx = rx / data->block_size_x;
	my = ry / data->block_size_y;
	while (data->map[my][mx] == '0')
	{
		mx = (rx += cos(angle)) / data->block_size_x;
		my = (ry += sin(angle)) / data->block_size_y;
	}
	hptn = sqrt((rx - data->player_x) * (rx - data->player_x) + \
	(ry - data->player_y) * (ry - data->player_y));
	fish_eye = data->player_angle - angle;
	hptn *= cos(fish_eye);
	rx = sqrt(data->block_size_y * data->block_size_y) * H / hptn;
	if (rx > H)
		rx = H;
	return (rx);
}

void	draw(t_data *data)
{
	int		i;
	float	ray_angle;
	float	fov[60];

	ray_angle = data->player_angle - DR * 30;
	i = -1;
	while (++i < 60)
	{
		fov[i] = raycasting(data, ray_angle);
		ray_angle += DR;
	}
	fov[i] = '\0';
	if (data->print_map)
		draw_map(data);
	else
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

void	init_player(t_data *data, int x, int y)
{
	data->player_x = x;
	data->player_y = y;
	data->player_delta_x = cos(data->player_angle);
	data->player_delta_y = sin(data->player_angle);
}

void	detect_player(t_data *data)
{
	int	i;
	int	j;
	int	x;
	int	y;

	i = -1;
	j = -1;
	x = 0;
	y = 0;
	while (data->map[++i])
	{
		while (data->map[i][++j])
		{
			if (!data->player_x && &data->map[i][j] == data->starting_pos)
				init_player(data, x, y);
			x += data->block_size_x;
		}
		j = -1;
		x = 0;
		y += data->block_size_y;
	}
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
		full_free(&data);
	}
	else
		printf("Error\nArgument number invalid\n");
	return (0);
}
