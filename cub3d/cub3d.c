#include "cub3d.h"

void	draw_element(t_data *data, int pos_x, int pos_y, t_rgb color)
{
	int x;
	int	y;

	x = -1;
	while (++x < data->block_size_x)
	{
		y = -1;
		while (++y < data->block_size_y)
			pixel_put(data, x + pos_x, y + pos_y, color);
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

void	draw_grill(t_data *data, t_rgb color)
{
	int x;
	int	y;

	x = -1;
	while (++x < W)
	{
		y = -1;
		while (++y < H)
			pixel_put(data, x, y, color);
	}
	x = 0;
	while (x < W)
	{
		y = -1;
		while (++y < H)
			pixel_put(data, x, y, rgb(0, 0, 0));
		x += data->block_size_x;
	}
	x = -1;
	while (++x < W)
	{
		y = 0;
		while (y < H)
		{
			pixel_put(data, x, y, rgb(0, 0, 0));
			y += data->block_size_y;
		}
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

void	draw_map(t_data *data, t_rgb color, char *file)
{
	int	i = 0;
	int j = 0;
	int x = 0;
	int	y = 0;

	while (i < ft_strlen(file))
	{
		if (file[i] == '0')
			x += data->block_size_x;
		else if (file[i] == '1' || file[i] == ' ')
		{
			draw_element(data, x, y, color);
			x += data->block_size_x;
		}
		else if (file[i] == '\t')
		{
			while (j++ < 4)
			{
				draw_element(data, x, y, color);
				x += data->block_size_x;
			}
			j = 0;
		}
		else if (file[i] == '\n')
		{
			x = 0;
			y += data->block_size_y;
		}
		else if (file[i] == 'N')
		{
			if (!data->player_x && !data->player_y)
			{
				data->player_x = x;
				data->player_y = y;
			}
			x += data->block_size_x;
		}
		i++;
	}
}

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
	if (data->player_x + data->block_size_x > W)
		data->player_x -= data->block_size_x;
	if (data->player_y + data->block_size_y > H)
		data->player_y -= data->block_size_y;
	if (data->player_x < 0)
		data->player_x += data->block_size_x;
	if (data->player_y < 0)
		data->player_y += data->block_size_y;
	draw_grill(data, rgb(114, 114, 114));
	//draw_map(data, rgb(0, 0, 0), file);
	draw_element(data, data->player_x, data->player_y, rgb(255, 255, 255));
	return (0);
}

int main(int ac, char **av)
{
	t_data	data;
	char	*file;

	if (ac == 2)
	{
		data = init();
		file = file_copy(file_read(av), file_size(file_read(av)));
		check_file(&data, file);
		draw_grill(&data, rgb(114, 114, 114));
		draw_map(&data, rgb(0, 0, 0), file);
		draw_element(&data, data.player_x, data.player_y, rgb(255, 255, 255));
		mlx_key_hook(data.win, key_hook, &data);
		mlx_loop(data.mlx);
		free(file);
	}
	else
		printf("Error\nArgument number invalid\n");
	return (0);
}
