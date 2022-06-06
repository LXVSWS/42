#include "cub3d.h"

t_data	init()
{
	t_data data;

	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, W, H, "cub3d");
	data.img = mlx_new_image(data.mlx, W, H);
	data.addr = mlx_get_data_addr(data.img, &data.bpp, &data.ll, &data.endian);
	data.x = 0;
	data.y = 0;
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

	dst = data->addr + (y * data->ll + x * (data->bpp / 8));
	*(unsigned int *)dst = rgb2int(rgb);
}
