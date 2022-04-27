#include "mlx/mlx.h"

int main()
{
	void *mlx;
	void *mlx_win;
	int	x = 0;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 500, 500, "cub3d");
	while (x++ < 500)
		mlx_pixel_put(mlx, mlx_win, x, x, 0x0025FDE9);
	mlx_loop(mlx);
	return (0);
}
