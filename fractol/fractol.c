#include "fractol.h"

void    alchemy(t_data *lx, int iterations, long double zoom, long double x1, long double x2, long double y1, long double y2)
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
	*(unsigned int *)dst = color;
}

long double precision(int n)
{
	long double	tmp;

	tmp = n * 2;
	return (tmp);
}

unsigned int	rgb2int(t_rgb rgb)
{
	return (rgb.r << 16 | rgb.g << 8 | rgb.b);
}

int julia(t_data *lx)
{
    long double		x;
    long double		y;
    long double		c_r;
    long double		c_i;
    long double		z_r;
    long double		z_i;
	long double		z_r2;
	long double		z_i2;
	int				i;
	t_rgb			rgb;

	mlx_mouse_get_pos(lx->win, &lx->mouse_x, &lx->mouse_y);
	x = -1;
    while (++x < W)
	{
		y = -1;
		while (++y < H)
        {
            c_r = precision(lx->mouse_x) / W - 1.5;
            c_i = precision(lx->mouse_y) / H - 1.5;
            z_r = x / lx->zoom + lx->x1;
            z_i = y / lx->zoom + lx->y1;
            i = 0;
			z_r2 = z_r * z_r;
			z_i2 = z_i * z_i;
            while (z_r2 + z_i2 < 4 && i < lx->iterations)
            {
				z_i = z_r * z_i;
				z_i += z_i;
				z_i += c_i;
				z_r = z_r2 - z_i2 + c_r;
				z_r2 = z_r * z_r;
				z_i2 = z_i * z_i;
                i++;
            }
            if (i == lx->iterations)
                pixel_put(lx, x, y, 0x000000);
            else
			{
				rgb.r = sin(0.4 * i) * 127 + 128;
				rgb.g = sin(0.2 * i) * 127 + 128;
				rgb.b = sin(0.2 * i) * 127 + 128;
				pixel_put(lx, x, y, rgb2int(rgb));
			}
        }
	}
    mlx_put_image_to_window(lx->mlx, lx->win, lx->img, 0, 0);
    mlx_string_put(lx->mlx, lx->win, 10, 10, 0xFFFFFF, "Ensemble de Julia");
	return (0);
}

int mandelbrot(t_data *lx)
{
    long double		x;
    long double		y;
    long double		c_r;
    long double		c_i;
    long double		z_r;
    long double		z_i;
	long double		z_r2;
	long double		z_i2;
    int				i;
	t_rgb			rgb;

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
			z_r2 = z_r * z_r;
			z_i2 = z_i * z_i;
            while (z_r2 + z_i2 < 4 && i < lx->iterations)
            {
				z_i = z_r * z_i;
				z_i += z_i;
				z_i += c_i;
				z_r = z_r2 - z_i2 + c_r;
				z_r2 = z_r * z_r;
				z_i2 = z_i * z_i;
                i++;
            }
            if (i == lx->iterations)
				pixel_put(lx, x, y, 0x000000);
            else
			{
				rgb.r = sin(0.4 * i) * 127 + 128;
				rgb.g = sin(0.2 * i) * 127 + 128;
				rgb.b = sin(0.2 * i) * 127 + 128;
				pixel_put(lx, x, y, rgb2int(rgb));
			}
        }
	}
    mlx_put_image_to_window(lx->mlx, lx->win, lx->img, 0, 0);
    mlx_string_put(lx->mlx, lx->win, 10, 10, 0xFFFFFF, "Ensemble de Mandelbrot");
	return (0);
}

int	key_hook(int keycode, t_data *lx)
{
	if (keycode == 9)
		lx->julia_move = !lx->julia_move;
    if (keycode == 123)
        alchemy(lx, lx->iterations, lx->zoom, lx->x1 - 0.001, lx->x2, lx->y1, lx->y2);
    if (keycode == 126)
        alchemy(lx, lx->iterations, lx->zoom, lx->x1, lx->x2, lx->y1 - 0.001, lx->y2);
    if (keycode == 124)
        alchemy(lx, lx->iterations, lx->zoom, lx->x1 + 0.001, lx->x2, lx->y1, lx->y2);
    if (keycode == 125)
        alchemy(lx, lx->iterations, lx->zoom, lx->x1, lx->x2, lx->y1 + 0.001, lx->y2);
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
        alchemy(lx, lx->iterations + 7, lx->zoom * 1.25, \
        (x / lx->zoom + lx->x1) - (x / (lx->zoom * 1.25)), lx->x2, (y / lx->zoom + lx->y1) - (y / (lx->zoom * 1.25)), lx->y2);
    if (button == 5 && lx->iterations > 5)
        alchemy(lx, lx->iterations - 7, lx->zoom * 0.75, \
        (x / lx->zoom + lx->x1) - (x / (lx->zoom * 0.75)), lx->x2, (y / lx->zoom + lx->y1) - (y / (lx->zoom * 0.75)), lx->y2);
	return (0);
}

int	mouse_motion_hook(int x, int y, t_data *lx)
{
	printf("here\n");
	if (lx->julia_move)
	{
		lx->mouse_x = x;
		lx->mouse_y = y;
		printf("(%d, %d)\n", lx->mouse_x, lx->mouse_y);
	}
	return (1);
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
		lx.julia_move = 0;
        alchemy(&lx, 150, 300, -1.5, 1.5, -1.5, 1.5);
		julia(&lx);
        mlx_key_hook(lx.win, key_hook, &lx);
        mlx_mouse_hook(lx.win, mouse_hook, &lx);
		mlx_hook(lx.win, MotionNotify, 0, mouse_motion_hook, &lx);
        mlx_loop(lx.mlx);
    }
    else if (ac == 2 && *av[1] == 'm')
    {
        alchemy(&lx, 50, 300, -2.1, 0.6, -1.2, 1.2);
		mandelbrot(&lx);
        mlx_key_hook(lx.win, key_hook, &lx);
		mlx_mouse_hook(lx.win, mouse_hook, &lx);
		mlx_loop_hook(lx.mlx, mandelbrot, &lx);
        mlx_loop(lx.mlx);
    }
    else
        printf("------------------------\nParamètres :\nj -> Ensemble de Julia\nm -> Ensemble de Mandelbrot\n");
    return (0);
}
