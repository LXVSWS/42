#include "cub3d.h"

void	draw(t_data *data)
{
	int x;
	int	y;

	x = -1;
	while (++x < W)
	{
		y = -1;
		while (++y < H)
			pixel_put(data, x, y, rgb(114, 114, 114));
	}
	x = -1;
	while (++x < 50)
	{
		y = -1;
		while (++y < 50)
			pixel_put(data, data->x + x, data->y + y, rgb(0, 0, 0));
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
	draw(data);
	return (0);
}

int main(int ac, char **av)
{
	t_data	data;
	int		map_fd;
	int		bytes_read;
	char	buf;

	if (ac == 2)
	{
		data = init();
		map_fd = open(av[1], O_RDONLY);
		if (map_fd == -1)
			write(2, "Error\nCannot open map\n", 22);
		bytes_read = 1;
		while (bytes_read)
		{
			bytes_read = read(map_fd, &buf, 1);
			if (bytes_read == -1)
				write(2, "Error\nProblem while reading\n", 28);
			if (buf == ' ')
				continue;
			else if (buf == '1')
				printf("1");
			else if (buf == '0')
				printf("0");
			else if (buf == '\n')
				printf("\n");
		}
		draw(&data);
		mlx_key_hook(data.win, key_hook, &data);
		mlx_loop(data.mlx);
		close(map_fd);
	}
	return (0);
}
