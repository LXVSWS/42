#include "fractol.h"

void    *mlx_initialisation()
{
    void    *mlx;

    mlx = mlx_init();
    if (!mlx)
        return (NULL);
    return (mlx);
}

void    *window_init(void *mlx, int width, int height)
{
    void    *win;

    win = mlx_new_window(mlx, width, height, "fractol");
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
                mlx_pixel_put(lx->mlx, lx->win, x, y, 0x000000); // mlx image a implémenter
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
                mlx_pixel_put(lx->mlx, lx->win, x, y, 0x000000); // mlx image a implémenter
            else
                mlx_pixel_put(lx->mlx, lx->win, x, y, i * 255 / lx->iterations);
        }
    mlx_string_put(lx->mlx, lx->win, 10, 10, 0xFFFFFF, "Ensemble de Mandelbrot");
}

int	redraw_julia(int keycode, t_struct *lx)
{
    printf("%i\n", keycode); // touches 1 2 3 4 5 6 7 8 9 0 ) - par défaut
    if (keycode == 18)
        alchemy(lx, lx->iterations, lx->zoom, lx->x1 + 0.5, lx->x2, lx->y1, lx->y2);
    if (keycode == 19)
        alchemy(lx, lx->iterations, lx->zoom, lx->x1, lx->x2 + 0.5, lx->y1, lx->y2);
    if (keycode == 20)
        alchemy(lx, lx->iterations, lx->zoom, lx->x1, lx->x2, lx->y1 + 0.5, lx->y2);
    if (keycode == 21)
        alchemy(lx, lx->iterations, lx->zoom, lx->x1, lx->x2, lx->y1, lx->y2 + 0.5);
    if (keycode == 23)
        alchemy(lx, lx->iterations, lx->zoom, lx->x1 - 0.5, lx->x2, lx->y1, lx->y2);
    if (keycode == 22)
        alchemy(lx, lx->iterations, lx->zoom, lx->x1, lx->x2 - 0.5, lx->y1, lx->y2);
    if (keycode == 26)
        alchemy(lx, lx->iterations, lx->zoom, lx->x1, lx->x2, lx->y1 - 0.5, lx->y2);
    if (keycode == 28)
        alchemy(lx, lx->iterations, lx->zoom, lx->x1, lx->x2, lx->y1, lx->y2 - 0.5);
    if (keycode == 25)
        alchemy(lx, lx->iterations + 5, lx->zoom, lx->x1, lx->x2, lx->y1, lx->y2);
    if (keycode == 29)
        alchemy(lx, lx->iterations, lx->zoom + 5, lx->x1, lx->x2, lx->y1, lx->y2);
    if (keycode == 27)
        alchemy(lx, lx->iterations - 5, lx->zoom, lx->x1, lx->x2, lx->y1, lx->y2);
    if (keycode == 24)
        alchemy(lx, lx->iterations, lx->zoom - 5, lx->x1, lx->x2, lx->y1, lx->y2);
    if (keycode >= 18 && keycode <= 29)
    {
        mlx_clear_window(lx->mlx, lx->win);
        julia(lx);
    }
    if (keycode == 53) // echap
    {
        mlx_destroy_window(lx->mlx, lx->win);
        exit(0);
    }
    return (0);
}

int	redraw_mandelbrot(int keycode, t_struct *lx)
{
    printf("%i\n", keycode); // touches 1 2 3 4 5 6 7 8 9 0 ) - par défaut
    if (keycode == 18)
        alchemy(lx, lx->iterations, lx->zoom, lx->x1 + 0.5, lx->x2, lx->y1, lx->y2);
    if (keycode == 19)
        alchemy(lx, lx->iterations, lx->zoom, lx->x1, lx->x2 + 0.5, lx->y1, lx->y2);
    if (keycode == 20)
        alchemy(lx, lx->iterations, lx->zoom, lx->x1, lx->x2, lx->y1 + 0.5, lx->y2);
    if (keycode == 21)
        alchemy(lx, lx->iterations, lx->zoom, lx->x1, lx->x2, lx->y1, lx->y2 + 0.5);
    if (keycode == 23)
        alchemy(lx, lx->iterations, lx->zoom, lx->x1 - 0.5, lx->x2, lx->y1, lx->y2);
    if (keycode == 22)
        alchemy(lx, lx->iterations, lx->zoom, lx->x1, lx->x2 - 0.5, lx->y1, lx->y2);
    if (keycode == 26)
        alchemy(lx, lx->iterations, lx->zoom, lx->x1, lx->x2, lx->y1 - 0.5, lx->y2);
    if (keycode == 28)
        alchemy(lx, lx->iterations, lx->zoom, lx->x1, lx->x2, lx->y1, lx->y2 - 0.5);
    if (keycode == 25)
        alchemy(lx, lx->iterations + 5, lx->zoom, lx->x1, lx->x2, lx->y1, lx->y2);
    if (keycode == 29)
        alchemy(lx, lx->iterations, lx->zoom + 5, lx->x1, lx->x2, lx->y1, lx->y2);
    if (keycode == 27)
        alchemy(lx, lx->iterations - 5, lx->zoom, lx->x1, lx->x2, lx->y1, lx->y2);
    if (keycode == 24)
        alchemy(lx, lx->iterations, lx->zoom - 5, lx->x1, lx->x2, lx->y1, lx->y2);
    if (keycode >= 18 && keycode <= 29)
    {
        mlx_clear_window(lx->mlx, lx->win);
        mandelbrot(lx);
    }
    if (keycode == 53) // echap
    {
        mlx_destroy_window(lx->mlx, lx->win);
        exit(0);
    }
    return (0);
}

int main(int ac, char **av)
{
    t_struct    lx;

    lx.mlx = mlx_initialisation();
    lx.win = window_init(lx.mlx, 1000, 800); // Dimensions fenêtre (résolution écran)
    if (ac == 2 && *av[1] == 'j')
    {
        alchemy(&lx, 150, 300, -1.5, 1.5, -1.5, 1.5); // paramètres de base
        julia(&lx);
        mlx_key_hook(lx.win, redraw_julia, &lx); // changement paramètres selon touche pressée
        mlx_loop(lx.mlx);
    }
    else if (ac == 2 && *av[1] == 'm')
    {
        alchemy(&lx, 50, 300, -2.1, 0.6, -1.2, 1.2); // paramètres de base
        mandelbrot(&lx);
        mlx_key_hook(lx.win, redraw_mandelbrot, &lx); // changement paramètres selon touche pressée
        mlx_loop(lx.mlx);
    }
    else
        printf("------------------------\nParamètres :\nj -> Ensemble de Julia\nm -> Ensemble de Mandelbrot\n");
    return (0);
}
