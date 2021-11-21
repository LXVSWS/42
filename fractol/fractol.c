#include <stdlib.h>
#include "mlx/mlx.h"
#define ITER_MAX 50
#define ZOOM 300
#define X1 -2.1
#define X2 0.6
#define Y1 -1.2
#define Y2 1.2

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
    if (!win)
        return (NULL);
    return (win);
}

int main()
{
    void    *mlx;
    void    *win;
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

    mlx = mlx_initialisation();
    x_max = (X2 - X1) * ZOOM;
    y_max = (Y2 - Y1) * ZOOM;
    win = window_init(mlx, x_max, y_max);

    for (x = 0 ; x < x_max ; x++)
        for (y = 0 ; y < y_max ; y++)
        {
            c_r = x / ZOOM + X1;
            c_i = y / ZOOM + Y1;
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
            while (z_r * z_r + z_i * z_i < 4 && i < ITER_MAX);
            if (i == ITER_MAX)
                mlx_pixel_put(mlx, win, x, y, 0x000000);
            else
                mlx_pixel_put(mlx, win, x, y, i * 255 / ITER_MAX);
        }
    mlx_loop(mlx);
    return (0);
}