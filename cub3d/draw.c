#include "cub3d.h"

void	draw_element(t_data *data, int pos_x, int pos_y, t_rgb color)
{
	int x;
	int	y;

	x = 0;
	while (++x < data->block_size_x)
	{
		y = 0;
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
			pixel_put(data, x, y, rgb(0, 0, 128));
		x += data->block_size_x;
	}
	x = -1;
	while (++x < W)
	{
		y = 0;
		while (y < H)
		{
			pixel_put(data, x, y, rgb(0, 0, 128));
			y += data->block_size_y;
		}
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}
