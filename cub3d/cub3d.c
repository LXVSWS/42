#include "cub3d.h"

int main()
{
	t_data	data;
	int		x = 0;

	data = init();
	while (x++ < 500)
		pixel_put(&data, x, x, rgb(37, 253, 233));
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	mlx_loop(data.mlx);
	return (0);
}
