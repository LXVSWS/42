#include "cub3d.h"

int main(int ac, char **av)
{
	t_data	data;
	int		map_fd;
	int		bytes_read;
	char	buf;

	(void)ac;
	data = init();
	map_fd = open(av[1], O_RDONLY);
	if (map_fd == -1)
		write(2, "Error\nCannot open map\n", 22);
	else
	{
		bytes_read = 1;
		while (bytes_read)
		{
			bytes_read = read(map_fd, &buf, 1);
			if (bytes_read == -1)
				write(2, "Error\nProblem while reading\n", 28);
			write(1, &buf, 1);
		}
		if (!bytes_read)
			write(1, "EOF\n", 4);
		pixel_put(&data, 250, 250, rgb(33, 253, 233));
		mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
		mlx_loop(data.mlx);
		close(map_fd);
	}
	return (0);
}
