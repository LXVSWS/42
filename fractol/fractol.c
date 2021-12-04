#include "fractol.h"

void    initialisation(t_data *lx)
{
    lx->mlx = mlx_init();
    lx->win = mlx_new_window(lx->mlx, W, H, "fractol");
    lx->img = mlx_new_image(lx->mlx, W, H);
	lx->addr = mlx_get_data_addr(lx->img, &lx->bpp, &lx->ll, &lx->endian);
}

void    alchemy(t_data *lx)
{
    if (lx->toggle)
    {
        lx->iterations = 150;
        lx->zoom = 300;
        lx->x1 = -1.5;
        lx->x2 = 1.5;
        lx->y1 = -1.5;
        lx->y2 = 1.5;
    }
    else
    {
        lx->iterations = 50;
        lx->zoom = 300;
        lx->x1 = -2.1;
        lx->x2 = 0.6;
        lx->y1 = -1.2;
        lx->y2 = 1.2;
    }
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

void draw(t_data *lx, int i, int x, int y)
{
    t_rgb   rgb;
    char	*dst;

    if (i == lx->iterations)
    {
        dst = lx->addr + (y * lx->ll + x * (lx->bpp / 8));
	    *(unsigned int *)dst = 0x000000;
    }
    else
    {
        rgb.r = sin(0.4 * i) * 127 + 128;
        rgb.g = sin(0.2 * i) * 127 + 128;
        rgb.b = sin(0.2 * i) * 127 + 128;
        dst = lx->addr + (y * lx->ll + x * (lx->bpp / 8));
	    *(unsigned int *)dst = rgb2int(rgb);
    }
}

int fractal(t_data *lx)
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

	x = -1;
    while (++x < W)
	{
		y = -1;
		while (++y < H)
        {
            if (lx->toggle)
            {
                c_r = precision(lx->mouse_x) / W - 1.5;
                c_i = precision(lx->mouse_y) / H - 1.5;
                z_r = x / lx->zoom + lx->x1;
                z_i = y / lx->zoom + lx->y1;         
            }
            else
            {
                c_r = x / lx->zoom + lx->x1;
                c_i = y / lx->zoom + lx->y1;
                z_r = 0;
                z_i = 0;
            }
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
            draw(lx, i, x, y);
        }
	}
    mlx_put_image_to_window(lx->mlx, lx->win, lx->img, 0, 0);
    if (lx->toggle)
        mlx_string_put(lx->mlx, lx->win, 10, 10, 0xFFFFFF, "Ensemble de Julia");
    else
        mlx_string_put(lx->mlx, lx->win, 10, 10, 0xFFFFFF, "Ensemble de Mandelbrot");
	return (0);
}

int	key_hook(int keycode, t_data *lx)
{
    if (keycode == 123)
        lx->x1 -= 0.01;
    if (keycode == 126)
        lx->y1 -= 0.01;
    if (keycode == 124)
        lx->x1 += 0.01;
    if (keycode == 125)
        lx->y1 += 0.01;
    if (keycode == 53)
    {
        mlx_destroy_image(lx->mlx, lx->img);
        mlx_destroy_window(lx->mlx, lx->win);
        exit(0);
    }
    fractal(lx);
    return (0);
}

int	mouse_hook(int button, int x, int y, t_data *lx)
{
    if (button == 4)
    {
        lx->iterations += 7;
        lx->zoom *= 1.25;
        lx->x1 = (x / lx->zoom + lx->x1) - (x / (lx->zoom * 1.25));
        lx->y1 = (y / lx->zoom + lx->y1) - (y / (lx->zoom * 1.25));
    }
    if (button == 5 && lx->iterations > 5)
    {
        lx->iterations -= 7;
        lx->zoom *= 0.75;
        lx->x1 = (x / lx->zoom + lx->x1) - (x / (lx->zoom * 0.75));
        lx->y1 = (y / lx->zoom + lx->y1) - (y / (lx->zoom * 0.75));    
    }
    fractal(lx);
	return (0);
}

int	mouse_motion_hook(int x, int y, t_data *lx)
{
	lx->mouse_x = x;
	lx->mouse_y = y;
    fractal(lx);
	return (0);
}

int main(int ac, char **av)
{
    t_data   lx;

    initialisation(&lx);
    if (ac == 2 && *av[1] == 'j')
    {
        lx.toggle = 1;
        alchemy(&lx);
		fractal(&lx);
        mlx_key_hook(lx.win, key_hook, &lx);
        mlx_mouse_hook(lx.win, mouse_hook, &lx);
		mlx_hook(lx.win, 6, 0, mouse_motion_hook, &lx); // X11 MotionNotify
        mlx_loop(lx.mlx);
    }
    else if (ac == 2 && *av[1] == 'm')
    {
        alchemy(&lx);
		fractal(&lx);
        mlx_key_hook(lx.win, key_hook, &lx);
		mlx_mouse_hook(lx.win, mouse_hook, &lx);
        mlx_loop(lx.mlx);
    }
    else
        printf("------------------------\nParamètres :\nj -> Ensemble de Julia\nm -> Ensemble de Mandelbrot\n");
    return (0);
}
