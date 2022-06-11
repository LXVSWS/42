#include "cub3d.h"

void	draw_grill(t_data *data, int width, int height, t_rgb color)
{
	int x;
	int	y;

	x = -1;
	while (++x < width)
	{
		y = -1;
		while (++y < height)
			pixel_put(data, x, y, color);
	}
	x = 0;
	while (x < width)
	{
		y = -1;
		while (++y < height)
			pixel_put(data, x, y, rgb(0, 0, 0));
		x += width / 10;
	}
	x = -1;
	while (++x < width)
	{
		y = 0;
		while (y < height)
		{
			pixel_put(data, x, y, rgb(0, 0, 0));
			y += height / 10;
		}
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

void	draw_player(t_data *data, int size)
{
	int x;
	int	y;

	x = -1;
	while (++x < size)
	{
		y = -1;
		while (++y < size)
			pixel_put(data, x + data->player_x, y + data->player_y, rgb(x, y, x + y));
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

int	key_hook(int keycode, t_data *data)
{
	if (keycode == 13)
		data->player_y -= data->block_size;
	if (keycode == 0)
		data->player_x -= data->block_size;
	if (keycode == 1)
		data->player_y += data->block_size;
	if (keycode == 2)
		data->player_x += data->block_size;
	if (keycode == 53)
	{
		mlx_destroy_image(data->mlx, data->img);
		mlx_destroy_window(data->mlx, data->win);
		exit(0);
	}
	draw_grill(data, W, H, rgb(114, 114, 114));
	draw_player(data, data->block_size);
	return (0);
}

int main(int ac, char **av)
{
	t_data	data;

	if (ac == 2)
	{
		check_map(av);
		data = init(av);
		draw_grill(&data, W, H, rgb(114, 114, 114));
		draw_player(&data, data.block_size);
		mlx_key_hook(data.win, key_hook, &data);
		mlx_loop(data.mlx);
	}
	if (data.map)
		free(data.map);
	return (0);
}
