#include "cub3d.h"

void	draw_square(t_data *data, int width, int height, t_rgb rgb)
{
	int x;
	int	y;

	x = -1;
	while (++x < width)
	{
		y = -1;
		while (++y < height)
			pixel_put(data, x + data->x, y + data->y, rgb);
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

int	key_hook(int keycode, t_data *data)
{
	if (keycode == 13)
		data->y -= 50;
	if (keycode == 0)
		data->x -= 50;
	if (keycode == 1)
		data->y += 50;
	if (keycode == 2)
		data->x += 50;
	if (keycode == 53)
	{
		mlx_destroy_image(data->mlx, data->img);
		mlx_destroy_window(data->mlx, data->win);
		exit(0);
	}
	draw_square(data, W, H, rgb(114, 114, 114));
	draw_square(data, 100, 100, rgb(data->x, data->y, data->x + data->y));
	return (0);
}

int main(int ac, char **av)
{
	t_data	data;

	if (ac == 2)
	{
		check_map(av);
		data = init(av);
		draw_square(&data, W, H, rgb(114, 114, 114));
		mlx_key_hook(data.win, key_hook, &data);
		mlx_loop(data.mlx);
	}
	if (data.map)
		free(data.map);
	return (0);
}
