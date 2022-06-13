#include "cub3d.h"

t_data	init(char **av)
{
	t_data data;

	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, W, H, "cub3d");
	data.img = mlx_new_image(data.mlx, W, H);
	data.addr = mlx_get_data_addr(data.img, &data.bpp, &data.ll, &data.endian);
	data.map = map_copy(map_read(av), map_size(map_read(av)));
	data.max_map_x = 0;
	data.max_map_y = 0;
	data.block_size_x = 0;
	data.block_size_y = 0;
	data.player_x = 0;
	data.player_y = 0;
	return (data);
}

unsigned int	rgb2int(t_rgb rgb)
{
	return (rgb.r << 16 | rgb.g << 8 | rgb.b);
}

t_rgb	rgb(unsigned char r, unsigned char g, unsigned char b)
{
	t_rgb	rgb;

	rgb.r = r;
	rgb.g = g;
	rgb.b = b;
	return (rgb);
}

void	pixel_put(t_data *data, int x, int y, t_rgb rgb)
{
	char	*dst;

	if (x < 0 || x >= W || y < 0 || y >= H)
		return ;
	dst = data->addr + (y * data->ll + x * (data->bpp / 8));
	*(unsigned int *)dst = rgb2int(rgb);
}

void	check_map_content(t_data *data)
{
	int i = 0;
	int x = 0;
	int x_max = 0;
	int y = 0;

	if (data->map)
	{
		while (data->map[i])
		{
			if (data->map[i] == '\n')
			{
				if (data->map[i + 1] && data->map[i + 1] == '\n' && data->map[i + 2])
				{
					printf("Error\nMultiple empty lines in map\n");
					exit(-1);
				}
				if (x > x_max)
					x_max = x;
				x = 0;
				if (!data->map[i + 1])
					break;
				y++;
			}
			else if (data->map[i] == '\t')
				x += 4;
			else if (data->map[i] == ' ' || data->map[i] == '0' || \
			data->map[i] == '1' || data->map[i] == 'N')
				x++;
			i++;
		}
		data->max_map_x = x_max;
		data->max_map_y = y;
		data->block_size_x = W / data->max_map_x;
		data->block_size_y = H / data->max_map_y;
	}
}
