#include <stdlib.h>
#include <stdio.h>
#include "mlx/mlx.h"

void *mlx_initialisation()
{
    void    *mlx;

    mlx = mlx_init();
    if (!mlx)
        return (NULL);
    return (mlx);
}

void *window_init(void *mlx, int x_max, int y_max)
{
    void    *win;

    win = mlx_new_window(mlx, x_max, y_max, "fractol");
    printf("%ix%i\n", x_max, y_max);
    if (!win)
        return (NULL);
    return (win);
}

void *julia(void *mlx, int iterations, int zoom)
{
    void    *win;
    float   x1;
    float   x2;
    float   y1;
    float   y2;
    float   x_max;
    float   y_max;
    float   x;
    float   y;
    float   c_r;
    float   c_i;
    float   z_r;
    float   z_i;
    float   tmp;
    int     i;

    x1 = -1;
    x2 = 1;
    y1 = -1.2;
    y2 = 1.2;
    x_max = (x2 - x1) * zoom;
    y_max = (y2 - y1) * zoom;
    win = window_init(mlx, x_max, y_max);
    for (x = 0 ; x < x_max ; x++)
        for (y = 0 ; y < y_max ; y++)
        {
            c_r = 0.285;
            c_i = 0.01;
            z_r = x / zoom + x1;
            z_i = y / zoom + y1 ;
            i = 0;
            do
            {
                tmp = z_r;
                z_r = z_r * z_r - z_i * z_i + c_r;
                z_i = 2 * z_i * tmp + c_i;
                i++;
            }
            while (z_r * z_r + z_i * z_i < 4 && i < iterations);
            if (i == iterations)
                mlx_pixel_put(mlx, win, x, y, 0x000000);
            else
                mlx_pixel_put(mlx, win, x, y, i * 255 / iterations);
        }
    return (win);  
}

void *mandelbrot(void *mlx, int iterations, int zoom)
{
    void    *win;
    float   x1;
    float   x2;
    float   y1;
    float   y2;
    float   x_max;
    float   y_max;
    float   x;
    float   y;
    float   c_r;
    float   c_i;
    float   z_r;
    float   z_i;
    float   tmp;
    int     i;

    x1 = -2.1;
    x2 = 0.6;
    y1 = -1.2;
    y2 = 1.2;
    x_max = (x2 - x1) * zoom;
    y_max = (y2 - y1) * zoom;
    win = window_init(mlx, x_max, y_max);
    for (x = 0 ; x < x_max ; x++)
        for (y = 0 ; y < y_max ; y++)
        {
            c_r = x / zoom + x1;
            c_i = y / zoom + y1;
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
            while (z_r * z_r + z_i * z_i < 4 && i < iterations);
            if (i == iterations)
                mlx_pixel_put(mlx, win, x, y, 0x000000);
            else
                mlx_pixel_put(mlx, win, x, y, i * 255 / iterations);
        }
    return (win);  
}

int main(int ac, char **av)
{
    void    *mlx;
    void    *win;
    int     iterations;
    int     zoom;

    zoom = 350;
    mlx = mlx_initialisation();
    if (ac == 2 && *av[1] == 'j')
    {
        iterations = 150;
        win = julia(mlx, iterations, zoom);
        mlx_loop(mlx);
    }
    else if (ac == 2 && *av[1] == 'm')
    {
        iterations = 50;
        win = mandelbrot(mlx, iterations, zoom);
        mlx_loop(mlx);
    }
    else
        printf("------------------------\nParamètres :\nj -> Ensemble Julia\nm -> Ensemble Mandelbrot\n");
    return (0);
}
