#include "cub3d.h"

t_data	init(void)
{
	t_data data;

	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, W, H, "cub3d");
	data.img = mlx_new_image(data.mlx, W, H);
	data.addr = mlx_get_data_addr(data.img, &data.bpp, &data.ll, &data.endian);
	data.no = NULL;
	data.so = NULL;
	data.we = NULL;
	data.ea = NULL;
	data.f = NULL;
	data.c = NULL;
	data.map = NULL;
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

int	ft_strlen(char *s)
{
	int i = 0;

	if (s)
	{
		while (s[i])
			i++;
	}
	return (i);
}
