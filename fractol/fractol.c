#include "fractol.h"

void    *mlx_initialisation()
{
    void    *mlx;

    mlx = mlx_init();
    if (!mlx)
        return (NULL);
    return (mlx);
}

void    *window_init(void *mlx, int x_max, int y_max)
{
    void    *win;

    win = mlx_new_window(mlx, x_max, y_max, "fractol");
    printf("%ix%i\n", x_max, y_max);
    if (!win)
        return (NULL);
    return (win);
}

void    alchemy(t_struct *lx, int iterations, int zoom, float x1, float x2, float y1, float y2)
{
    lx->iterations = iterations;
    lx->zoom = zoom;
    lx->x1 = x1;
    lx->x2 = x2;
    lx->y1 = y1;
    lx->y2 = y2;
    lx->x_max = (x2 - x1) * zoom;
    lx->y_max = (y2 - y1) * zoom;
    if (lx->win)
        mlx_destroy_window(lx->mlx, lx->win);
    lx->win = window_init(lx->mlx, lx->x_max, lx->y_max);
}

void    julia(t_struct *lx)
{
    float   x;
    float   y;
    float   c_r;
    float   c_i;
    float   z_r;
    float   z_i;
    float   tmp;
    int     i;

    for (x = 0 ; x < lx->x_max ; x++)
        for (y = 0 ; y < lx->y_max ; y++)
        {
            c_r = 0.285;
            c_i = 0.01;
            z_r = x / lx->zoom + lx->x1;
            z_i = y / lx->zoom + lx->y1 ;
            i = 0;
            do
            {
                tmp = z_r;
                z_r = z_r * z_r - z_i * z_i + c_r;
                z_i = 2 * z_i * tmp + c_i;
                i++;
            }
            while (z_r * z_r + z_i * z_i < 4 && i < lx->iterations);
            if (i == lx->iterations)
                mlx_pixel_put(lx->mlx, lx->win, x, y, 0x000000);
            else
                mlx_pixel_put(lx->mlx, lx->win, x, y, i * 255 / lx->iterations);
        }
    mlx_string_put(lx->mlx, lx->win, 10, 10, 0xFFFFFF, "Ensemble de Julia");   
}

void    mandelbrot(t_struct *lx)
{
    float   x;
    float   y;
    float   c_r;
    float   c_i;
    float   z_r;
    float   z_i;
    float   tmp;
    int     i;

    for (x = 0 ; x < lx->x_max ; x++)
        for (y = 0 ; y < lx->y_max ; y++)
        {
            c_r = x / lx->zoom + lx->x1;
            c_i = y / lx->zoom + lx->y1;
            z_r = 0;
            z_i = 0;
            i = 0;
            do
            {
                tmp = z_r;
                z_r = z_r * z_r - z_i * z_i + c_r;
                z_i = 2 * z_i * tmp + c_i;
                i++;
            }
            while (z_r * z_r + z_i * z_i < 4 && i < lx->iterations);
            if (i == lx->iterations)
                mlx_pixel_put(lx->mlx, lx->win, x, y, 0x000000);
            else
                mlx_pixel_put(lx->mlx, lx->win, x, y, i * 255 / lx->iterations);
        }
    mlx_string_put(lx->mlx, lx->win, 10, 10, 0xFFFFFF, "Ensemble de Mandelbrot");
}

int	redraw_julia(int keycode, t_struct *lx)
{
    printf("%i\n", keycode);
    mlx_clear_window(lx->mlx, lx->win);
    lx->zoom += 100;
    lx->iterations += 25;
    julia(lx);
    return (0);
}

int	redraw_mandelbrot(int keycode, t_struct *lx)
{
    printf("%i\n", keycode);
    mlx_clear_window(lx->mlx, lx->win);
    lx->zoom += 100;
    lx->iterations += 25;
    mandelbrot(lx);
    return (0);
}

int main(int ac, char **av)
{
    t_struct    lx;

    lx.mlx = mlx_initialisation();
    if (ac == 2 && *av[1] == 'j')
    {
        alchemy(&lx, 150, 350, -1, 1, -1.2, 1.2);
        julia(&lx);
        mlx_key_hook(lx.win, redraw_julia, &lx);
        mlx_loop(lx.mlx);
    }
    else if (ac == 2 && *av[1] == 'm')
    {
        alchemy(&lx, 50, 350, -2.1, 0.6, -1.2, 1.2);
        mandelbrot(&lx);
        mlx_key_hook(lx.win, redraw_mandelbrot, &lx);
        mlx_loop(lx.mlx);
    }
    else
        printf("------------------------\nParamètres :\nj -> Ensemble de Julia\nm -> Ensemble de Mandelbrot\n");
    return (0);
}
