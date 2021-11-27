#include "fractol.h"

void    alchemy(t_data *lx, int iterations, int zoom, double x1, double x2, double y1, double y2)
{
    lx->iterations = iterations;
    lx->zoom = zoom;
    lx->x1 = x1;
    lx->x2 = x2;
    lx->y1 = y1;
    lx->y2 = y2;
}

void	pixel_put(t_data *lx, int x, int y, int color)
{
	char	*dst;

	dst = lx->addr + (y * lx->ll + x * (lx->bpp / 8));
	*(unsigned int*)dst = color;
}

int julia(t_data *lx)
{
    double   x;
    double   y;
    double   c_r;
    double   c_i;
    double   z_r;
    double   z_i;
    double   tmp;
    int      i;

	x = -1;
    while (++x < W)
	{
		y = -1;
		while (++y < H)
        {
            c_r = 0.285;
            c_i = 0.01;
            z_r = x / lx->zoom + lx->x1;
            z_i = y / lx->zoom + lx->y1;
            i = 0;
            while (z_r * z_r + z_i * z_i < 4 && i < lx->iterations)
            {
                tmp = z_r;
                z_r = z_r * z_r - z_i * z_i + c_r;
                z_i = 2 * z_i * tmp + c_i;
                i++;
            }
            if (i == lx->iterations)
                pixel_put(lx, x, y, 0x000000);
            else
                pixel_put(lx, x, y, i * 255 / lx->iterations);
        }
	}
    mlx_put_image_to_window(lx->mlx, lx->win, lx->img, 0, 0);
    mlx_string_put(lx->mlx, lx->win, 10, 10, 0xFFFFFF, "Ensemble de Julia");
    return (0);
}

int mandelbrot(t_data *lx)
{
    double   x;
    double   y;
    double   c_r;
    double   c_i;
    double   z_r;
    double   z_i;
    double   tmp;
    int      i;

	x = -1;
    while (++x < W)
	{
		y = -1;
		while (++y < H)
        {
            c_r = x / lx->zoom + lx->x1;
            c_i = y / lx->zoom + lx->y1;
            z_r = 0;
            z_i = 0;
            i = 0;
            while (z_r * z_r + z_i * z_i < 4 && i < lx->iterations)
            {
                tmp = z_r;
                z_r = z_r * z_r - z_i * z_i + c_r;
                z_i = 2 * z_i * tmp + c_i;
                i++;
            }
            if (i == lx->iterations)
				pixel_put(lx, x, y, 0x000000);
            else
				pixel_put(lx, x, y, i * 255 / lx->iterations);
        }
	}
    mlx_put_image_to_window(lx->mlx, lx->win, lx->img, 0, 0);
    mlx_string_put(lx->mlx, lx->win, 10, 10, 0xFFFFFF, "Ensemble de Mandelbrot");
    return (0);
}

int	key_hook(int keycode, t_data *lx)
{
    if (keycode == 123)
        alchemy(lx, lx->iterations, lx->zoom, lx->x1 - 0.01, lx->x2, lx->y1, lx->y2);
    if (keycode == 126)
        alchemy(lx, lx->iterations, lx->zoom, lx->x1, lx->x2, lx->y1 - 0.01, lx->y2);
    if (keycode == 124)
        alchemy(lx, lx->iterations, lx->zoom, lx->x1 + 0.01, lx->x2, lx->y1, lx->y2);
    if (keycode == 125)
        alchemy(lx, lx->iterations, lx->zoom, lx->x1, lx->x2, lx->y1 + 0.01, lx->y2);
    if (keycode == 53)
    {
        mlx_destroy_image(lx->mlx, lx->img);
        mlx_destroy_window(lx->mlx, lx->win);
        exit(0);
    }
    return (0);
}

int	mouse_hook(int button, int x, int y, t_data *lx)
{
    if (button == 4)
        alchemy(lx, lx->iterations + 5, lx->zoom * 1.25, \
        (x / lx->zoom + lx->x1) - (x / (lx->zoom * 1.25)), lx->x2, (y / lx->zoom + lx->y1) - (y / (lx->zoom * 1.25)), lx->y2);
    if (button == 5 && lx->iterations > 5)
        alchemy(lx, lx->iterations - 5, lx->zoom / 1.25, \
        (x / lx->zoom + lx->x1) - (x / (lx->zoom / 1.25)), lx->x2, (y / lx->zoom + lx->y1) - (y / (lx->zoom / 1.25)), lx->y2);
	return (0);
}

int main(int ac, char **av)
{
    t_data   lx;

    lx.mlx = mlx_init();
    lx.win = mlx_new_window(lx.mlx, W, H, "fractol");
    lx.img = mlx_new_image(lx.mlx, W, H);
	lx.addr = mlx_get_data_addr(lx.img, &lx.bpp, &lx.ll, &lx.endian);
    if (ac == 2 && *av[1] == 'j')
    {
        alchemy(&lx, 150, 300, -1.5, 1.5, -1.5, 1.5);
        mlx_loop_hook(lx.mlx, julia, &lx);
        mlx_key_hook(lx.win, key_hook, &lx);
        mlx_mouse_hook(lx.win, mouse_hook, &lx);
        mlx_loop(lx.mlx);
    }
    else if (ac == 2 && *av[1] == 'm')
    {
        alchemy(&lx, 50, 300, -2.1, 0.6, -1.2, 1.2);
        mlx_loop_hook(lx.mlx, mandelbrot, &lx);
        mlx_key_hook(lx.win, key_hook, &lx);
		mlx_mouse_hook(lx.win, mouse_hook, &lx);
        mlx_loop(lx.mlx);
    }
    else
        printf("------------------------\nParamètres :\nj -> Ensemble de Julia\nm -> Ensemble de Mandelbrot\n");
    return (0);
}
