/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 02:54:44 by lwyss             #+#    #+#             */
/*   Updated: 2022/06/19 06:39:50 by lwyss            ###   ########.fr       */
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
		exit(0);
	}
	check_movement(data);
	draw_bg(data, rgb(114, 114, 127));
	draw_grill(data, rgb(0, 0, 127));
	draw_element(data, data->player_x, data->player_y, rgb(255, 255, 255));
	return (0);
}

char	*strdupmod(char *s)
{
	int		i;
	int		size;
	char	*str;

	i = 0;
	size = 0;
	while (s[i] && s[i] != '\n')
	{
		if (s[i] != ' ' && s[i] != '\t')
			size++;
		i++;
	}
	str = malloc(sizeof(char) * size + 1);
	str[size] = 0;
	i = 0;
	size = 0;
	while (s[i] && s[i] != '\n')
	{
		if (s[i] == ' ' || s[i] == '\t')
			i++;
		else
			str[size++] = s[i++];
	}
	return (str);
}

int	check_file(t_data *data, char *file)
{
	int	i;

	i = 0;
	while (file[i])
	{
		if (file[i] == 'N' && file[i + 1] == 'O')
			data->no = strdupmod(&file[i + 2]);
		else if (file[i] == 'S' && file[i + 1] == 'O')
			data->so = strdupmod(&file[i + 2]);
		else if (file[i] == 'W' && file[i + 1] == 'E')
			data->we = strdupmod(&file[i + 2]);
		else if (file[i] == 'E' && file[i + 1] == 'A')
			data->ea = strdupmod(&file[i + 2]);
		else if (file[i] == 'F')
			data->f = strdupmod(&file[i + 1]);
		else if (file[i] == 'C')
			data->c = strdupmod(&file[i + 1]);
		if (data->no && data->so && data->we && data->ea && data->f && data->c)
			break ;
		i++;
	}
	if (!data->no || !data->so || !data->we \
	|| !data->ea || !data->f || !data->c)
		error("Missing data in file");
	return (i);
}

int	detect_map(char *file, int i)
{
	while (file[i] && file[i] != '\n')
		i++;
	while (file[i] && file[i] == '\n')
		i++;
	if (!file[i])
		error("No map detected");
	return (i);
}

void	copy_map(t_data *data, char *file)
{
	char	**map;
	int		i;
	int		j;
	int		k;

	map = malloc(sizeof(char *) * data->max_map_y + 1);
	if (!map)
		error("Malloc failed");
	map[data->max_map_y] = NULL;
	i = 0;
	while (i < data->max_map_y)
	{
		map[i] = malloc(sizeof(char) * data->max_map_x + 1);
		if (!map[i])
			error("Malloc failed");
		map[i++][data->max_map_x] = 0;
	}
	i = 0;
	j = 0;
	k = 0;
	while (file[i])
	{
		if (file[i] == '\n')
		{
			j++;
			k = 0;
		}
		else
			map[j][k++] = file[i];
		i++;
	}
	data->map = map;
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
		if (!data.starting_pos)
			error("Map has no player");
		copy_map(&data, &file[i]);
		printf("%s", data->map[0]);
		data.block_size_x = W / data.max_map_x;
		data.block_size_y = H / data.max_map_y;
		free(file);
		printf("%s\n%s\n%s\n%s\n%s\n%s\nx=%i\ny=%i\nx1=%i\ny2=%i\n", \
		data.no, data.so, data.we, data.ea, data.f, data.c, data.max_map_x, \
		data.max_map_y, data.block_size_x, data.block_size_y);
		draw_bg(&data, rgb(114, 114, 127));
		draw_grill(&data, rgb(0, 0, 127));
		draw_element(&data, data.player_x, data.player_y, rgb(255, 255, 255));
		mlx_key_hook(data.win, key_hook, &data);
		mlx_loop(data.mlx);
	}
	else
		printf("Error\nArgument number invalid\n");
	return (0);
}
